#include "includes.h"

extern void Main(void);

BOOL WINAPI DllWork(__in::HMODULE hModule)
{

	Main();
	return TRUE;

}

BOOL WINAPI DllMain(__in::HMODULE hModule, __in::DWORD dwReason, __in __reserved::LPVOID lpvReserved)
{

	HANDLE hThread = NULL;

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		if ((hThread = ::CreateThread(NULL, 0, (::LPTHREAD_START_ROUTINE)&DllWork, (::HMODULE)hModule, 0, NULL)) == NULL)
			return FALSE;
		CloseHandle(hThread);
	}

	return TRUE;

}
