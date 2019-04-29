#include "scanner.h"

DWORD scanner::find_pattern(DWORD dw_start, DWORD dw_end, const char *pattern, int result)
{

	const char *pat = pattern;
	int results = 0;
	DWORD match = 0;

	for (DWORD dw_cur = dw_start; dw_cur < dw_end; dw_cur++)
	{
		_try
		{

			if (!*pat)
				return match;
			if (*(PBYTE)pat == '\?' || *(BYTE *)dw_cur == get_byte(pat))
			{
				if (!match)
					match = dw_cur;
				if (!pat[2])
				{
					if (results + 1 != result)
						results++;
					else
						return match;
				}
				if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
					pat += 3;
				else
					pat += 2;  // # one ?
			}
			else
			{
				pat = pattern;
				match = 0;
			}

		}
		_except(EXCEPTION_EXECUTE_HANDLER) {}
	}

	return dw_start;

}
