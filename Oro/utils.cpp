#include "utils.h"

void utils::replace_string(std::string &subject, const std::string &search, const std::string &replace)
{

  size_t pos = 0;
  while ((pos = subject.find(search, pos)) != std::string::npos)
  {
    subject.replace(pos, search.length(), replace);
    pos += replace.length();
  }

}

std::vector<unsigned char> utils::hex_to_bytes(const std::string &hex)
{

  std::vector<unsigned char> bytes;

  for (unsigned int i = 0; i < hex.length(); i += 2)
  {
    std::string byteString = hex.substr(i, 2);
    unsigned char byte = (char)strtol(byteString.c_str(), NULL, 16);
    bytes.push_back(byte);
  }

  return bytes;

}
