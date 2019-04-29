#pragma once
#include "includes.h"
#include "utils.h"

namespace memapi {

	#define ROUND_UP(p, align) (((DWORD)(p) + (align)-1) & ~((align)-1))
	#define ROUND_DOWN(p, align) ((DWORD)(p) & ~((align)-1))

	int __stdcall write(DWORD dw_address, std::string write_buffer);

	namespace pointer {

		bool valid(unsigned long base, unsigned long offset);
		int read_int(unsigned long base, unsigned long offset);
		void write_int(unsigned long base, unsigned long offset, int value);

		std::string read_str(unsigned long base, unsigned long offset);
		void write_str(unsigned long base, unsigned long offset, std::string value);

		float read_float(unsigned long base, unsigned long offset);
		void write_float(unsigned long base, unsigned long offset, float value);

	}

}
