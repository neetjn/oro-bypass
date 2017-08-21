#pragma once
#include "includes.h"

namespace utils {

  void replace_string(std::string &subject, const std::string &search, const std::string &replace);
  std::vector<unsigned char> hex_to_bytes(const std::string &hex);

}
