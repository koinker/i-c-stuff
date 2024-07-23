#include <Windows.h>
#include <stdio.h>


int main() {
	//dynamic load of user32.dll
	HMODULE hModule = LoadLibraryA("User32.dll");

	//check if lib loaded success
	if (!hModule) {
		printf("Failed to load user32.dll");
		return 1;
	}

	//prototype message box function
	typedef int (WINAPI* MsgBoxFunc)(HWND, LPCSTR, LPCSTR, UINT);
	MsgBoxFunc OrdinalBoxA = (MsgBoxFunc)GetProcAddress(hModule, (LPCSTR)2151);

	//check if function is found by ord
	if (!OrdinalBoxA) {
		printf("Failed to locate function");
		FreeLibrary(hModule);
		return 1;
	}
	//message box call by ord
	OrdinalBoxA(NULL, "TEST", "1337", MB_OK | MB_ICONINFORMATION);

	FreeLibrary(hModule);
	return 0;

}
