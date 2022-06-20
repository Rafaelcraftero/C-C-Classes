#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include "rafballop-LibSS.h"

double MideRetraso(LPCTSTR pMensaje) {

	double segs = 0.5;
	static BOOL primeraLlamada = true;
	static LARGE_INTEGER frec, t_ini, t_fin, counter;
	char cad[100] = "";

	if (primeraLlamada) {
		primeraLlamada = false;
		segs = 0.0;
		BOOL compruebaFrec = QueryPerformanceFrequency(&frec);
		CheckError(compruebaFrec == false, "Error al ejecutar", 1);
		BOOL compruebaCounter = QueryPerformanceCounter(&t_ini);
		CheckError(compruebaCounter == false, "Error al contar", 1);
	}
	else {
		QueryPerformanceCounter(&t_fin);
		counter.QuadPart = t_fin.QuadPart - t_ini.QuadPart;
		t_ini = t_fin;
		segs = (double)counter.QuadPart / frec.QuadPart;
		_snprintf(cad, 100, "%s%f segs.", pMensaje, segs);
		OutputDebugString(cad);
	}
	return segs;
}