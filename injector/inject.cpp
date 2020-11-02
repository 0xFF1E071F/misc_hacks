#include <stdio.h>
#include <windows.h>

int main(int argc, char **argv) {
	int len;
	void *page;
	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi = {0};
	HANDLE hThread;
	if (argc < 2) {
		return 1;
	}
	si.cb = sizeof(STARTUPINFO);
	CreateProcess(NULL, argv[1], NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi);
	page = VirtualAllocEx(pi.hProcess, NULL, MAX_PATH, MEM_COMMIT|MEM_RESERVE, PAGE_READWRITE);
	if (page == NULL) {
		return 1;
	}
	len = lstrlen(argv[2]) + 1;
	if (len > MAX_PATH) {
		return 1;
	}
	WriteProcessMemory(pi.hProcess, page, argv[2], len, NULL);
	hThread = CreateRemoteThread(pi.hProcess, NULL, 0, (LPTHREAD_START_ROUTINE) LoadLibraryA, page, 0, NULL);
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	ResumeThread(pi.hThread);
	CloseHandle(pi.hProcess);
	VirtualFreeEx(pi.hProcess, page, MAX_PATH, MEM_RELEASE);
	return 0;
}