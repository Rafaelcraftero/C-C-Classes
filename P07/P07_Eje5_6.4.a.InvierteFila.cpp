#include "proyectoP07.h"
// poner aquí todos los archivos de includes adicionales necesarios
extern double amplitudDistorsion;



#pragma region Ejercicio 6.5

// INICIO EJERCICIO 6.5
void InvierteFilas(IplImage* imgOrg, IplImage* imgSal)
{	
	//declaramos variables que necesitamos
	DWORD y, x;
	unsigned char* ppixel, ppixel2;
	int maxX = imgOrg->width;
	int maxY = imgOrg->height;
	double distorcion = ceil((double)(maxY * (amplitudDistorsion / 100))); 
	//la amplitud la tomamos como un porcentaje de la pantalla que vamos a parar y tomamos el techo del pixel que da al hacer el porcentaje


	for (y = 0; y < maxY; y++)
	{
		// Procesa pixels dentro de cada scanline
		if (y > distorcion) {//Si la y es mayor que distorcion no se para
			for (x = 0; x < maxX; x++)
			{
				/* Calcula pixeles de origen y de destino,
						imageData apunta al inicio de la imagen.
							   y* widthStep  es la distancia hasta el inicio del scanline y
							   x* nChannels es la distancia desde el inicio del scanline
									hasta la columna x.
				*/
				// Dirección del pixel de origen
				unsigned char* pO = (unsigned char*)&imgOrg->imageData[y * imgOrg->widthStep + x * imgOrg->nChannels];
				// Dirección del pixel de destino
				unsigned char* pD = (unsigned char*)&imgSal->imageData[(maxY - y - 1) * imgSal->widthStep + x * imgSal->nChannels];
				//El primer pixel de arriba es el de abajo del todo y se va restado y
				//Copia imagen destino
				memcpy(pD, pO, imgSal->nChannels);

			}
		}
	}
}
//No me funciona la función GeneraBMP24cv por algo de los símbolos de windows así que acabe haciendolo con el video de la práctica 3 de juego de tronos
//además que queda mejor.
int s;
void Ejercicio6_4(char* argv[]) {

	printf("0  - Salir\n<0 invertir filas\n>0 - normal\n¿Nuevo comando?\n");
	scanf("%d", &s);

	if (s != 0) {


		IplImage* newframe, * oldframe;
		char key = 0;
		int tecla;	// permite leer las teclas que pulsa el usuario en las ventanas openCV
		char* nombreVentana;
		CvCapture* g_capture = NULL;	// Para gestionar la captura de video
		// comprueba que el usuario ha puesto el ancho y alto de la imagen en línea de comandos

		// Para la imagen original usamos un patrón conocido
		IplImage* imgOriginal;
		g_capture = cvCreateFileCapture(argv[1]);	// Abre el archivo de video

		CheckError(NULL == g_capture, "\n\nERROR: No se pudo abrir el archivo de video\n\n", 1);
		imgOriginal = cvQueryFrame(g_capture); // Lee frame del archivo
		IplImage* imgResultado = cvCreateImage(CvSize(imgOriginal->width, imgOriginal->height),
			imgOriginal->depth, imgOriginal->nChannels);
		if (NULL == imgOriginal) {
			printf("\n\nERROR: No se pudo abrir el archivo de video\n\n");
		}	// crea imagen de resultado
		else
		{
			double antes = 0, gap, ahora;
			char buffer[20];
			// Bucle de proceso de frames
			newframe = cvQueryFrame(g_capture); // Lee frame del archivo

			double retrasoAcumulado = 0.0; // permite calcular la velocidad de proceso de las imágenes
			int nroImagenes = 0;

			while (newframe && (key != 13)) {
				oldframe = newframe;

				char mensaje[200];
				if (s < 0) {
					InvierteFilas(imgOriginal, imgResultado);
				}
				else {
					imgResultado = imgOriginal;
				}

				retrasoAcumulado += MideRetraso(0);
				nroImagenes++;
				snprintf(mensaje, sizeof(mensaje),
					"procesando %d imagenes en %.2f segs\n(%.2f imgs/s)\nPulsa ENTER para terminar",
					nroImagenes, retrasoAcumulado, nroImagenes / retrasoAcumulado);
				ImagenAVentana(imgResultado, "RESULTADO:", mensaje, true, &tecla);
				newframe = cvQueryFrame(g_capture);
				ahora = cvGetCaptureProperty(g_capture, CV_CAP_PROP_POS_MSEC);
				gap = ahora - antes;
				antes = ahora;
				key = cvWaitKey((int)gap);
			}

			cvReleaseCapture(&g_capture);
		}
		cvDestroyWindow((char*)"Ventana 1");

		//FIN EJERCICIO 6.5

	}


}
#pragma endregion