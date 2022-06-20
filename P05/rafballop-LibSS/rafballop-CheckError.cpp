// Original: #include "Everything.h"
// Modificado: pongo los .h que realmente usa
#include <stdio.h>
#include <Windows.h>
// Usa caracteres genéricos 
#include <tchar.h>

VOID ReportError(LPCTSTR userMessage, DWORD exitCode, BOOL printErrorMessage);

BOOL CheckError(BOOL ErrorCondition, LPCTSTR userMessage, DWORD exitCode) {
	if (ErrorCondition)
		ReportError(userMessage, exitCode, TRUE);
	return ErrorCondition;
}

VOID ReportError(LPCTSTR userMessage, DWORD exitCode, BOOL printErrorMessage)

/* General-purpose function for reporting system errors.
	Obtain the error number and convert it to the system error message.
	Display this information and the user-specified message to the standard error device.
	userMessage:		Message to be displayed to standard error device.
	exitCode:		0 - Return.
					> 0 - ExitProcess with this code.
	printErrorMessage:	Display the last system error message if this flag is set. */
{
	DWORD eMsgLen, errNum = GetLastError();
	LPTSTR lpvSysMsg;
	_ftprintf(stderr, _T("%s\n"), userMessage);
	OutputDebugString(userMessage);
	OutputDebugString("\n");
	if (printErrorMessage && errNum != 0) {
		eMsgLen = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL, errNum, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpvSysMsg, 0, NULL);
		if (eMsgLen > 0)
		{
			_ftprintf(stderr, _T("%s\n"), lpvSysMsg);
			OutputDebugString(lpvSysMsg);
			OutputDebugString("\n");
		}
		else
		{
			_ftprintf(stderr, _T("Last Error Number; %d.\n"), errNum);
		}

		if (lpvSysMsg != NULL) LocalFree(lpvSysMsg); /* Explained in Chapter 5. */
	}

	if (exitCode > 0) {
		MessageBeep(MB_ICONASTERISK);
		OutputDebugString("\n Error en el programa. Pulse tecla de RETORNO para terminar...");
		printf("\n !!! Programa terminó con error ¡¡¡ . Pulse tecla de RETORNO para terminar...");
		getchar();
		ExitProcess(exitCode);
	}

	return;
}

