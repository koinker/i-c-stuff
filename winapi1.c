#include <Windows.h>
#include <stdio.h>

// Worker threads
DWORD WINAPI Thread1(LPVOID param) {
    for (int counter = 0; counter < 5; counter++) {
        printf("Thread 1: %d\n", counter);
        Sleep(1000);
    }
    return 0;
}

DWORD WINAPI Thread2(LPVOID param) {
    for (int counter = 0; counter < 5; counter++) {
        printf("Thread 2: %d\n", counter);
        Sleep(1000);
    }
    return 0;
}

// main function that creates threads and waits for each to complete
int main() {
    // Create thread handles
    HANDLE hThread1 = CreateThread(NULL, 0, Thread1, NULL, 0, NULL);
    HANDLE hThread2 = CreateThread(NULL, 0, Thread2, NULL, 0, NULL);

    if (hThread1 == NULL || hThread2 == NULL) {
        printf("Error creating threads.\n");
        return 1;
    }

    // Wait for both threads to finish
    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);

    // Close thread handles
    CloseHandle(hThread1);
    CloseHandle(hThread2);

    printf("Both threads have finished.\n");
    return 0;
}
