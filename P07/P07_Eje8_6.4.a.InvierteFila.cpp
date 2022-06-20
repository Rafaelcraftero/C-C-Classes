#include "proyectoP07.h"
// poner aquí todos los archivos de includes adicionales necesarios

extern double amplitudDistorsion;


pdi_InvierteFilas_t pInfoHilos2[NRO_HILOS];

// Crea un efecto de malla sobre la imagen
IplImage* InvierteFila_2x(IplImage* imgO, IplImage* imgR) {

	//creo 2 hilos
	for (size_t i = 0; i < NRO_HILOS; i++)
	{
		
		pInfoHilos2[i] = new di_InvierteFilas_t; // Reserva de memoria
		//Inicializamos valores del hilo
		pInfoHilos2[i]->img0 = imgO;
		pInfoHilos2[i]->imgR = imgR;
		pInfoHilos2[i]->nroHilo = i;
		pInfoHilos2[i]->totalHilos = NRO_HILOS;
		//lanzamos los hilos
		pInfoHilos2[i]->h = CreateThread(NULL, 0, InvierteFilas_h, pInfoHilos2[i], 0, &pInfoHilos2[i]->id);
		CheckError(NULL == pInfoHilos2[i]->h, "Error al crear el hilo InvierteFilas_h", 1);//Si hay algun error salta
	}

	for (size_t i = 0; i < NRO_HILOS; i++)//Cuando no se dejen de usar borra los hilos
	{
		DWORD res = WaitForSingleObject(pInfoHilos2[i]->h, INFINITE);
		CheckError(WAIT_OBJECT_0 != res, "Error al bloquear esperando al fin del hilo", 1);
		delete pInfoHilos2[i];
	}
	//Espero a que termine...
	return imgR;
}


DWORD WINAPI InvierteFilas_h(LPVOID parametroVoid) {
	IplImage* imgO, * imgR;
	pdi_InvierteFilas_t p = (pdi_InvierteFilas_t)parametroVoid;
	//creamos imagenes a partir del struct que se hizo anteriormente
	imgO = p->img0;
	imgR = p->imgR;
	//	CvSize TamOriginal = { imgO->width, imgO->height }; // para llamar a cvCreateImage
	//	imgR = cvCreateImage(TamOriginal, imgO->depth, imgO->nChannels);
	//	CheckError(imgR == NULL, "No se pudo crear la imagen para modificar", 1);
	int maxX = imgO->width;
	int maxY = imgO->height;
	double distorcion = ceil((double)(maxY * (amplitudDistorsion / 100)));
	unsigned char* pO;
	unsigned char* pD;
	DWORD y, x;
	for (y = 0; y < maxY; y++)
	{
		// Procesa pixels dentro de cada scanline
		if (y > distorcion) {
			for (x = 0; x < maxX; x++){
				/* Calcula pixeles de origen y de destino,
						imageData apunta al inicio de la imagen.
							   y* widthStep  es la distancia hasta el inicio del scanline y
							   x* nChannels es la distancia desde el inicio del scanline
									hasta la columna x.
				*/
				// Dirección del pixel de origen
								// Dirección del pixel de destino
				pO = (unsigned char*)&imgO->imageData[y * imgO->widthStep + x * imgO->nChannels];
				pD = (unsigned char*)&imgR->imageData[(maxY - y - 1) * imgR->widthStep + x * imgR->nChannels];
				//El primer pixel de arriba es el de abajo del todo y se va restado y
				//Copia imagen destino
				memcpy(pD, pO, imgR->nChannels);


			}

		}

	}
	return 0;
}

