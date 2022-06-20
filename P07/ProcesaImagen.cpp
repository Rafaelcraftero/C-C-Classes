#include "ProyectoP07.h"
// poner aquí todos los archivos de includes adicionales necesarios

void ProcesaImagen(IplImage * imgO, IplImage * imgR, double sinUso1, double sinUso2)
{
	int bytesXpixel = imgO->nChannels;
	for (int y = 0; y < imgO->height; y++) { // Recorre scanlines
		for (int x = 0; x < imgO->width; x++) {
			/* Calcula pixeles de origen y de destino,
					imageData apunta al inicio de la imagen.
						   y* widthStep  es la distancia hasta el inicio del scanline y
						   x* nChannels es la distancia desde el inicio del scanline
								hasta la columna x.
			*/
			// Dirección del pixel de origen
			unsigned char * pO = (unsigned char *)&imgO->imageData[y*imgO->widthStep + x * bytesXpixel];
			// Dirección del pixel de destino
			unsigned char * pD = (unsigned char *)&imgR->imageData[y*imgR->widthStep + x * bytesXpixel];
			
			// Copia pixel de origen a pixel de destino.
			memcpy(pD, pO, bytesXpixel);
			/* Alternativas
			   Usando casting sobre los punteros:
				RGBTRIPLE 
				PDWORD ó int *
			*/
		}
	}
}
