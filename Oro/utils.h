#pragma once
#include "includes.h"

namespace utils {

  std::string dword_to_string(DWORD input, int size = 8);
  void replace_string(std::string &subject, const std::string &search, const std::string &replace);
  std::vector<unsigned char> hex_to_bytes(const std::string &hex);
  HANDLE get_process_by_name(PCSTR name);
  DWORD get_process_pid_by_name(PCSTR name);
  bool kill_process_by_name(const char* filename);
  void update_privilege(void);

}
