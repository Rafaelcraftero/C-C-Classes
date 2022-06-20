#include <windows.h>

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD ul_reason_for_call,
	LPVOID lpReserved)

{

	switch (ul_reason_for_call) // <-- esto es opcional

	{

	case DLL_PROCESS_ATTACH: // Posibles causas de entrada en DllMain

		OutputDebugString(">> Se ha cargado la DLL XXXXXX \n"); //<--opc

		break;

	case DLL_PROCESS_DETACH:

		OutputDebugString("<< Se ha descargado la DLL XXXXXX \n"); //<--opc

		break;

	case DLL_THREAD_ATTACH:

	case DLL_THREAD_DETACH:

		break;

	}

	return TRUE; // <--esto es lo único obligatorio.

}