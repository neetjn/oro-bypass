#include "oro.h"

Hack::Hack(DWORD address, std::string enabled, std::string disabled)
{

	this->active = false;
	this->address = address;
	this->enabled = enabled;
	this ->disabled = disabled;

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

	while (FindWindow("Rumble Fighter", "Rumble Fighter") == NULL) {
		Sleep(2500);
	}

	DWORD dw_min = 0x400000;
	DWORD dw_max = 0x7FFFFF;

	this->gg_window_check = scanner::find_pattern(
		dw_min, dw_max, "74 77 8B 15 A8 BC 72 00"
	);

	DWORD gg_check_sub = scanner::find_pattern(
		dw_min, dw_max, "55 8B EC 81 EC 08 02 00 00 A1 30 2C 7C 00 33 C5"
	); // # get base address for gameguard check subroutine

	this->gg_falsified = gg_check_sub + 0x110;
	this->gg_hack_detected = gg_check_sub + 0x109;
	this->gg_init = gg_check_sub + 0x9D;
	this->gg_speed_hack = gg_check_sub + 0xD1;
	this->gg_unhandeled_exception = gg_check_sub + 0x96;

	this->initialized = true;

}

void Oro::bypass()
{

	if (this->initialized)
  {
		memapi::write(this->gg_window_check, "EB"); // # skip
		memapi::write(this->gg_falsified, "EB 3A"); // # route to no errors detected
		memapi::write(this->gg_hack_detected, "EB 41"); // # route to no errors detected
		memapi::write(this->gg_init, "E9 AA 00 00 00 90 90"); // # route to no errors detected
		memapi::write(this->gg_speed_hack, "EB 63 90 90 90 8D 8D FC FE");
		memapi::write(this->gg_unhandeled_exception, "E9 B1 00 00 00 90 90"); // # route to no errors detected
	}

}