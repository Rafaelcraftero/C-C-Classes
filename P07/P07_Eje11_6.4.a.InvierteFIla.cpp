#include "proyectoP07.h"
// poner aquí todos los archivos de includes adicionales necesarios
extern double amplitudDistorsion;
pdi_InvierteFilas_t* pInfoHilosN;
void InvierteFilas_Nx(IplImage* imgO, IplImage* imgR, int numeroDeHilos) {

	pInfoHilosN = new pdi_InvierteFilas_t[numeroDeHilos];
	//creo numeroDeHilos hilos
	for (size_t i = 0; i < numeroDeHilos; i++)
	{
		pInfoHilosN[i] = new di_InvierteFilas_t; // Reserva de memoria
		//Inicializamos el struct del hilo
		pInfoHilosN[i]->img0 = imgO;
		pInfoHilosN[i]->imgR = imgR;
		pInfoHilosN[i]->nroHilo = i;
		pInfoHilosN[i]->totalHilos = numeroDeHilos;
		//lanzamos los hilos
		pInfoHilosN[i]->h = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)InvierteFilas_h, pInfoHilosN[i], 0, &pInfoHilosN[i]->id);
		CheckError(NULL == pInfoHilosN[i]->h, "Error al crear el hilo InvierteFilas_h", 1);
	}

	for (size_t i = 0; i < numeroDeHilos; i++)
	{
		//Borramos los hilos que no se usan
		DWORD res = WaitForSingleObject(pInfoHilosN[i]->h, INFINITE);
		CheckError(WAIT_OBJECT_0 != res, "Error al bloquear esperando al fin del hilo", 1);
		delete pInfoHilosN[i];
	}
	//Espero a que termine...
}









