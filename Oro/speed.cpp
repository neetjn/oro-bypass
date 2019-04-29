#include "speed.h"

namespace speed {

	float acceleration = 1;
	int sleep_time = 10;
	bool initialized = false;
	double tick_count;
	long long performance_count, performance_frequency;

}

void MakePageWritable(unsigned long Address, unsigned long ulSize)
{

	MEMORY_BASIC_INFORMATION *mbi = new MEMORY_BASIC_INFORMATION;
	VirtualQuery((void *)Address, mbi, ulSize);
	if (mbi->Protect != PAGE_EXECUTE_READWRITE)
	{
		unsigned long *ulProtect = new unsigned long;
		VirtualProtect((void *)Address, ulSize, PAGE_EXECUTE_READWRITE, ulProtect);
		delete ulProtect;
	}
	delete mbi;

}

bool Jump(unsigned long Address, void *Function)
{

	__try
	{
		MakePageWritable(Address, 5);
		*(unsigned char *)Address = 0xE9;
		*(unsigned long *)(Address + 1) = ((int)Function - Address) - 5;
		return true;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return false;
	}

}

void speed::tick()
{

	timeBeginPeriod(1);
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

	float performance_sleep_time = (sleep_time * performance_frequency / 1000.0f);

	while (true)
	{
		Sleep(sleep_time);
		tick_count += sleep_time * acceleration;
		performance_count += (long long)(performance_sleep_time * acceleration);
	}
}

int WINAPI speed::new_tick_count()
{
	return (int)tick_count;
}

BOOL WINAPI speed::new_query_performance_counter(LARGE_INTEGER *Count)
{
	Count->QuadPart = performance_count;
	return TRUE;
}

void speed::set_speed(float speed)
{

	acceleration = speed;

	tick_count = GetTickCount();

	LARGE_INTEGER Ref;
	QueryPerformanceFrequency(&Ref);
	performance_frequency = Ref.QuadPart;

	QueryPerformanceCounter(&Ref);
	performance_count = Ref.QuadPart;

	if (initialized == false)
	{
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&tick, NULL, 0, NULL);
		initialized = true;
	}

	DWORD get_tick_count = (DWORD)GetProcAddress(LoadLibrary("kernel32.dll"), "GetTickCount");
	Jump(get_tick_count, new_tick_count);
	DWORD time_get_time = (DWORD)GetProcAddress(LoadLibrary("winmm.dll"), "timeGetTime");
	Jump(time_get_time, new_tick_count);
	DWORD query_peformance_counter = (DWORD)GetProcAddress(LoadLibrary("kernel32.dll"), "QueryPerformanceCounter");
	Jump(query_peformance_counter, new_query_performance_counter);

}
