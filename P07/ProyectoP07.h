//.h com�n a todo el proyecto
#pragma once

#define _CRT_SECURE_NO_WARNINGS

//#include "rafballop-P06\Proyecto.h"

#include <stdio.h>
#include <locale.h>

#include <windows.h>

#include "opencv/cv.h"
#include "opencv/highgui.h"

// este tambien est� en $(AAComm)\inc
#include "rafballop-LibSS.h"
#include "enumPatrones.h"
char* ImagenAVentana(IplImage*, char*, char*, bool, int*);
IplImage* GeneraBMP24cv(DWORD maxX, DWORD maxY, DWORD tipodepatron);

// Ejemplo de uso de par�metros opcionales en C++. 
// Si no se ponen, el compilador les da autom�ticamente el valor que
// aparece en la inicializaci�n
void ProcesaImagen(IplImage*, IplImage*, double = 0.0, double = 0.0);
void TrasMalla(IplImage* imgO, IplImage* imgR, double sinUso1, double sinUso2);
void TrasMalla_2x(IplImage* imgO, IplImage* imgR);

DWORD WINAPI TrasMalla_h(LPVOID parametroVoid);


void TrasMalla_Nx(IplImage* imgO, IplImage* imgR, int numeroDeHilos);

#define NRO_HILOS 2

typedef struct {
	HANDLE h;
	DWORD id;
	IplImage* img0;
	IplImage* imgR;
	int nroHilo;
	int totalHilos;
} di_InvierteFilas_t, * pdi_InvierteFilas_t;
//di_trasMalla_t infoHilos[NRO_HILOS];

void Ejercicio6_4(char* argv[]);
IplImage* InvierteFila_2x(IplImage* imgO, IplImage* imgR);
DWORD WINAPI InvierteFilas_h(LPVOID parametroVoid);
void InvierteFilas(IplImage* imgOrg, IplImage* imgSal);
void InvierteFilas_Nx(IplImage* imgO, IplImage* imgR, int numeroDeHilos);