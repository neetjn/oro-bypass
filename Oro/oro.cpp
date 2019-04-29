#include "oro.h"

Hack::Hack(DWORD address, std::string enabled, std::string disabled)
{

	this->active = false;
	this->address = address;
	this->enabled = enabled;
	this->disabled = disabled;

}

void Hack::toggle()
{

	if (this->active)
		memapi::write(this->address, this->disabled);
	else
		memapi::write(this->address, this->enabled);

	this->active = !this->active;

}

void Oro::init()
{

	while (FindWindow("Rumble Fighter", "Rumble Fighter") == NULL)
		Sleep(2500);

	DWORD dw_min = 0x400000;
	DWORD dw_max = 0x7FFFFF;

  this->gg_window_check = scanner::find_pattern(
    dw_min, dw_max, "3D 55 07 00 00 74 77 8B 15 ? ? ? 00 A1"
  ) + 0x5;

  DWORD gg_check_sub = scanner::find_pattern(
    dw_min, dw_max, "55 8B EC 81 EC 08 02 00 00 A1 ? ? 7C 00 33 C5"
  ); // # get base address for gameguard check subroutine

  this->gg_falsified = gg_check_sub + 0x110;
  this->gg_hack_detected = gg_check_sub + 0x109;
  this->gg_init = gg_check_sub + 0x9D;
  this->gg_speed_hack = gg_check_sub + 0xD1;
  this->gg_unhandeled_exception = gg_check_sub + 0x96;

  this->gg_access = scanner::find_pattern(
    dw_min, dw_max, "55 8B EC 6A FF 68 58 56"
  );

  this->initialized = true;

}

void Oro::bypass()
{

  if (this->initialized)
  {

    // # disable initial GG check
    memapi::write(this->gg_window_check, "EB");

    // # disable gg scan/check routine by detouring individual checks
    // # - disabling individual checks because it has proven safer
    // # - otherwise we need to disarm this subroutine at each ref. including in external threads
    // TODO: create jmp based off of end sub address
    // possibly try inline assembly?
    memapi::write(this->gg_falsified, "EB 24");  // # route to no errors detected
    memapi::write(this->gg_hack_detected, "EB 2B");  // # route to no errors detected
    memapi::write(this->gg_init, "E9 94 00 00 00 90 90");  // # route to no errors detected
    memapi::write(this->gg_speed_hack, "EB 63 90 90 90");
    memapi::write(this->gg_unhandeled_exception, "E9 9B 00 00 00 90 90");  // # route to no errors detected

    // # spoof status code from GG daemon
    // # - client sends a request to the GG daemon to check if client is ok
    // # - if client can't be contacted GG daemon will kill process
    // # - if daemon can't be contacted, client will kill itself
    // # - patch by simply returning the expected status code
    memapi::write(this->gg_access, "C2 00 00 00 00 90 90"); // # toggle good return status (code 0)

    // # kill gg daemon
    std::vector <std::string> processes{ "GameMon.des", "GameMon64.des" };

    for (std::string& i : processes) {
      if (!utils::kill_process_by_name(i.c_str())) {
        // # fallback to pstools @ https://docs.microsoft.com/en-us/sysinternals/downloads/pskill
        #if _WIN32 || _WIN64
          #if _WIN64
            std::string cmd = "pskill " + i;
          #else
            std::string cmd = "pskill64 " + i;
          #endif
        #endif
        system(cmd.c_str());
      }
    }
  }

}
