#include <Windows.h>
#include <stdio.h>
#include <LM.h>

//Function that returns the current directory context
int main() {
	CHAR lpBuffer[MAX_PATH + 1];
	DWORD nBufferLength = MAX_PATH + 1;
	if ((GetCurrentDirectoryA(nBufferLength, lpBuffer)) != 0) {
		printf("Current Directory: %s\n", lpBuffer);
	}
	else {
		printf("GetCurrentDirectoryA failed with error: %s", GetLastError());

	}
}