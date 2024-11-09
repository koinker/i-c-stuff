#include <Windows.h>
#include <stdio.h>
#include <LM.h>


//function that returns the current account username using GetUserNameA
int main() {
	CHAR lpBuffer[UNLEN + 1];
	DWORD cbBuffer = UNLEN + 1;
	if (GetUserNameA(lpBuffer, &cbBuffer)) {
		printf("User: %s\n", lpBuffer);

	}
	else {
		printf("GetUsernameA failed with error code: %d", GetLastError());
	}

}