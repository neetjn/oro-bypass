#include "utils.h"

std::string utils::dword_to_string(DWORD input, int size)
{
  std::ostringstream oss;
  oss << std::hex << std::setw(size) << std::right << input;
  return oss.str();
}

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

HANDLE utils::get_process_by_name(PCSTR name)
{
  DWORD pid = 0;

  HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  PROCESSENTRY32 process;
  ZeroMemory(&process, sizeof(process));
  process.dwSize = sizeof(process);

  if (Process32First(snapshot, &process))
  {
    do
    {
      if (std::string(process.szExeFile) == std::string(name))
      {
        pid = process.th32ProcessID;
        break;
      }
    } while (Process32Next(snapshot, &process));
  }

  CloseHandle(snapshot);

  if (pid != 0)
  {
    return OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
  }

  return NULL;
}

DWORD utils::get_process_pid_by_name(PCSTR name)
{
  DWORD pid = 0;

  HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  PROCESSENTRY32 process;
  ZeroMemory(&process, sizeof(process));
  process.dwSize = sizeof(process);

  if (Process32First(snapshot, &process))
  {
    do
    {
      if (std::string(process.szExeFile) == std::string(name))
      {
        pid = process.th32ProcessID;
        break;
      }
    } while (Process32Next(snapshot, &process));
  }

  CloseHandle(snapshot);

  return pid;
}

bool utils::kill_process_by_name(const char* filename)
{
  HANDLE h2_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
  PROCESSENTRY32 entry;
  entry.dwSize = sizeof(entry);
  BOOL h_res = Process32First(h2_snapshot, &entry);
  while (h_res)
  {
    if (strcmp(entry.szExeFile, filename) == 0)
    {
      HANDLE process = OpenProcess(PROCESS_TERMINATE, 0, (DWORD)entry.th32ProcessID);
      if (process != NULL)
      {
        bool terminated = TerminateProcess(process, 9);
        CloseHandle(process);
        return terminated;
      }
    }
    h_res = Process32Next(h2_snapshot, &entry);
  }
  CloseHandle(h2_snapshot);
  return false;
}

void utils::update_privilege(void)
{
  HANDLE token;
  TOKEN_PRIVILEGES tp;
  LUID luid;

  if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token))
  {
    LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid);

    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = luid;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    AdjustTokenPrivileges(token, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL);
  }
}
