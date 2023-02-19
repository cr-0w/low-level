#include <iostream>
#include <windows.h>

HANDLE process;

int main(int argc, char* argv[]) {

	if (argv[1] == NULL) {
		printf("[!] usage: processenumeration.exe <PID>");
		exit(1);
	}

	printf("\n[+] user supplied: %i", atoi(argv[1]));

	process = OpenProcess(
		PROCESS_ALL_ACCESS,
		FALSE,
		DWORD(atoi(argv[1]))
	);

	if (!process) {
		printf("\n[!] couldn't open process: PID (%i)", atoi(argv[1]));
		exit(1);
	}

	printf("\n[+] latched onto process!\n");
	printf("\n -==================================-");
	printf("\n | beginning process enumeration... |");
	printf("\n -==================================-");

	WCHAR procPath[MAX_PATH];
	DWORD procSize = MAX_PATH;

	if (QueryFullProcessImageNameW(
		process,
		0, // DON'T SET THIS TO PROCESS_NAME_NATIVE (0x00000001)
		procPath,
		&procSize)
		) {

		printf("\n\n[+] PROC_PATH = %ls", procPath);

		WCHAR* exeName = wcsrchr(procPath, L'\\');
		if (exeName == NULL) {
			printf("[!] unable to extract name from path");
			exeName = procPath;
		}

		else {
			exeName++;
		}

		printf("\n[+] PROC_NAME = %ls", exeName);
	}

	else {
		printf("\n[!] something went wrong. you're on your own. good luck.");
		exit(1);
	}

	DWORD arch;
	if (!GetBinaryTypeW(procPath, &arch)) {
		printf("[!] failed to get binary arch.");
	}

	switch (arch) {

	case SCS_32BIT_BINARY:
		printf("\n[+] PROC_ARCH = 32-bit");
		break;

	case SCS_64BIT_BINARY:
		printf("\n[+] PROC_ARCH = 64-bit");
		break;

	case SCS_WOW_BINARY:
		printf("\n[+] PROC_ARCH = 16-bit");
		break;

	default:
		printf("[!] PROC_ARCH = UNKNOWN.");
		break;
	}

	DWORD PROCID = GetProcessId(process);
	printf("\n[+] PROC_ID = %i", PROCID);

	DWORD PROCVERSION = GetProcessVersion(PROCID);
	printf("\n[+] PROC_VERSION = %lu", PROCVERSION);

	CloseHandle(process);
}
