#include "ProyectoP07.h"
#define Valorblanco 0xFFFFFFFF
#define Valornegro  0

// Devuelve un valor de del pixel en función de su posicion x, y, y el tipo de patro
static DWORD Calculapixelpatron(DWORD maxX, DWORD maxY, DWORD tipodepatron, int x, int y)
{
	DWORD Valor = Valornegro;
	int tamCuadrado = 20, despCuadrado = 5;
	switch (tipodepatron)
	{
	case Patron_10:
		// Patron arbitrario. Por ejemplo, algo parecido a un tartán escocés
		if (((y % tamCuadrado) == 0) ^ ((x % tamCuadrado) == 0))
			Valor = 0xff0000; // si fila xor columna es par, el pixel es valorblanco
		if ((((y + despCuadrado) % tamCuadrado) == 0) ^ (((x + despCuadrado) % tamCuadrado) == 0))
			Valor = 0x00ff00; // si fila xor columna es par, el pixel es valorblanco
		if ((((y + 2 * despCuadrado) % tamCuadrado) == 0) ^ (((x + 2 * despCuadrado) % tamCuadrado) == 0))
			Valor = 0x0000ff; // si fila xor columna es par, el pixel es valorblanco
		break;
	default:
		// Genera cudricula de pixeles valorblancos y valornegros
		if ((y % 2) ^ (x % 2))
			Valor = Valorblanco; // si fila xor columna es par, el pixel es valorblanco
		break;	// En otro caso, valornegro
		break;
	}
	return Valor;
}
IplImage* GeneraBMP24cv(DWORD maxWidth, DWORD maxHeight, DWORD tipodepatron)
{
	PBYTE ppix;
	DWORD y, x;

	CvSize tam = { (int)maxWidth, (int)maxHeight };   // Inicializa la estructura con los valores maxX y maxY
	IplImage* img;

	img = cvCreateImage(tam, IPL_DEPTH_8U, 3);  // Crea una imagen de 24 bits (3*8)
												// http://docs.opencv.org/2.4/modules/core/doc/old_basic_structures.html#createimage
												// Se han rellenado automáticamente los campos de la cabecera. La matriz de píxeles está
												// a partir de img->imageData
												// img->origin = 1;
	CheckError(NULL == img, "No se pudo crear la imagen", 1);
	// procesa scanlines (Y)
	for (y = 0; y < maxHeight; y++)
	{
		// Procesa pixels dentro de cada scanline
		for (x = 0; x < maxWidth; x++)
		{
			DWORD Valor;
			// Calcula la dirección del pixel actual
			ppix = (PBYTE)img->imageData + y * img->widthStep + x * img->nChannels;
			// Calcula el valor correspondiente a la posición x, y
			Valor = Calculapixelpatron(maxWidth, maxHeight, tipodepatron, x, y);
			memcpy(ppix, &Valor, img->nChannels);	// copia el valor al pixel correspondiente
		}
	}
	// Guarda la imagen.
	// MUY IMPORTANTE: el formato con que se escribe la imagen depende de la extensión del archivo
	return img;
	// http://docs.opencv.org/2.4/modules/highgui/doc/reading_and_writing_images_and_video.html#imwrite
}
