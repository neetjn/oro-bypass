#pragma once
#include "includes.h"
#include "scanner.h"
#include "speed.h"
#include "memory.h"

class Hack
{
private:
	bool active;
	DWORD address;
	std::string enabled, disabled;

public:
	Hack(DWORD address, std::string enabled, std::string disabled);
	void toggle();
};

class Oro
{
private:
	bool initialized = false;
  DWORD gg_window_check, gg_falsified, gg_hack_detected, gg_init, gg_speed_hack, gg_unhandeled_exception, gg_access,
        gg_start;

public:
	void init();
	void bypass();
};
