//.h común a todo el proyecto
#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define NRO_HILOS 1
//#include "rafballop-P06\Proyecto.h"

#include <stdio.h>
#include <locale.h>

#include <windows.h>

#include "opencv/cv.h"
#include "opencv/highgui.h"

// este tambien está en $(AAComm)\inc
#include "rafballop-LibSS.h"
#include "enumPatrones.h"



DWORD WINAPI MuestraVideoN(LPVOID lpParameter);
void ProcesaImagen(IplImage*, IplImage*, double = 0.0, double = 0.0);
static HANDLE hEvento;


char* ImagenAVentana(IplImage*, char*, char*, bool, int*);
DWORD WINAPI MuestraVideoN(LPVOID lpParameter);

void miniMenu();


#define N 10
static double segundos = 0.0;
static HANDLE semMostrarCuenta;
DWORD WINAPI IncrAsync(LPVOID lpParameter);

static CRITICAL_SECTION cs;

