#pragma once
#include "includes.h"

namespace scanner {

	#define INRANGE(x, a, b) (x >= a && x <= b)
	#define get_bits(x) (INRANGE((x & (~0x20)), 'A', 'F') ? ((x & (~0x20)) - 'A' + 0xa) : (INRANGE(x, '0', '9') ? x - '0' : 0))
	#define get_byte(x) (get_bits(x[0]) << 4 | get_bits(x[1]))

	DWORD find_pattern(DWORD dw_start, DWORD dw_end, const char *pattern, int result = 1);

}
