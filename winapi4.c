#include <windows.h>
#include <stdio.h>

int main() {
    CHAR* lpCommandLine = "C:\\Windows\\System32\\ping.exe localhost -n 4";
    PROCESS_INFORMATION pi;
    STARTUPINFOA si;
    SECURITY_ATTRIBUTES sa;
    HANDLE hReadPipe, hWritePipe;

    // Set up the security attributes for the pipe
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;

    // Create the pipe
    if (!CreatePipe(&hReadPipe, &hWritePipe, &sa, 0)) {
        printf("CreatePipe failed. Error: %d\n", GetLastError());
        return 1;
    }

    // Ensure the read handle to the pipe is not inherited
    if (!SetHandleInformation(hReadPipe, HANDLE_FLAG_INHERIT, 0)) {
        printf("SetHandleInformation failed. Error: %d\n", GetLastError());
        return 1;
    }

    // Set up the STARTUPINFO structure
    ZeroMemory(&si, sizeof(STARTUPINFOA));
    si.cb = sizeof(STARTUPINFOA);
    si.hStdError = hWritePipe;
    si.hStdOutput = hWritePipe;
    si.dwFlags |= STARTF_USESTDHANDLES;

    // Initialize PROCESS_INFORMATION structure
    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

    // Create the ping process
    if (!CreateProcessA(NULL, lpCommandLine, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        printf("CreateProcessA failed. Error: %d\n", GetLastError());
        CloseHandle(hReadPipe);
        CloseHandle(hWritePipe);
        return 1;
    }

    // Close the write end of the pipe, as it's no longer needed
    CloseHandle(hWritePipe);

    // Read the output from the ping process in real time
    CHAR buffer[256];
    DWORD bytesRead;
    BOOL success;

    while (TRUE) {
        success = ReadFile(hReadPipe, buffer, sizeof(buffer) - 1, &bytesRead, NULL);
        if (!success || bytesRead == 0) break;

        buffer[bytesRead] = '\0';  // Null-terminate the string
        printf("%s", buffer);  // Print the output
    }

    // Wait for the ping process to finish
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Clean up
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    CloseHandle(hReadPipe);

    printf("Ping Scan Complete...\n");
    return 0;
}
