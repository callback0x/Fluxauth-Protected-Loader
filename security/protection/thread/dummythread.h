#include <Windows.h>


DWORD WINAPI DummyThread(LPVOID lpParam)
{
	while (true)
	{
		Sleep(0);
	}
}

void IfResumeDummy()
{
	HANDLE dummy = CreateThread(NULL, NULL, DummyThread, NULL, NULL, NULL);
	while (true)
	{
		if (ResumeThread(dummy) >= 1)
		{
			(exit)(0);
		}
		Sleep(1);
	}
}
