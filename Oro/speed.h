#pragma once
#include "includes.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

namespace speed
{

	void tick();
	int WINAPI new_tick_count();
	BOOL WINAPI new_query_performance_counter(LARGE_INTEGER *count);

	void set_speed(float speed);

}
