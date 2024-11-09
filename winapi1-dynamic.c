#include <Windows.h>
#include <stdio.h>
#include <LM.h>

typedef BOOL(WINAPI* fnCreateThreadA)(
	LPSECURITY_ATTRIBUTES		lpThreadAttributes,
	SIZE_T						dwStackSize,
	LPTHREAD_START_ROUTINE		lpStartAddress,
	LPVOID						lpParameter,
	DWORD						dwCreationFlags,
	LPDWORD						lpThreadId
	);

DWORD WINAPI Thread1(LPVOID param) {
	for (int counter = 0; counter < 5; counter++) {
		printf("Thread 1: %d\n", counter);
		Sleep(1000);
	}
	return 0;
}

int main() {
	HMODULE hKernel32 = LoadLibraryA("kernel32.dll");
	fnCreateThreadA createThread = (fnCreateThreadA)GetProcAddress(hKernel32, "CreateThread");
	if (createThread != NULL) {
		printf("CreateThreadA Resolved...\n");

		HANDLE hThread1 = createThread(NULL, 0, Thread1, NULL, 0, NULL);

		if (hThread1 == NULL) {
			printf("Error creating threads.\n");
			return 1;
		}
		WaitForSingleObject(hThread1, INFINITE);

		CloseHandle(hThread1);

		printf("Thread finished.\n");
		return 0;
	}
}