#pragma once
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include <windows.h>
VOID ReportError(LPCTSTR userMessage, DWORD exitCode, BOOL printErrorMessage);
BOOL CheckError(BOOL ErrorCondition, LPCTSTR userMessage, DWORD exitCode);
void Firma_rafballop(CvArr* imagen);
double MideRetraso(LPCTSTR pMensaje);