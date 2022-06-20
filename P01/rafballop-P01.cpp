//////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Based on example 2 page 18 of OReilly Learning OpenCV.pdf:

// Basada en práctica 1 de SPD.

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include <locale.h>

#include "opencv/cv.h"

#include "opencv/highgui.h"

void play(char*, char*);

int main(int argc, char* argv[]) {

	setlocale(LC_ALL, "Spanish"); // hace que printf "entienda" tildes, ñ, etc.

	printf("\nPulse tecla ESC para cerrar la ventana\n");

	// el archivo .mp4 está en _pub/_comm/eje del repositorio público

	play((char*)"P01Eje1.mp4", (char*) "Ventana 1");

	printf("\nPulse tecla RETORNO para terminar\n");

	getchar();

	return 0;

}

void play(char* file_name, char* nombre_ventana)

{

	char key = 0;

	// tipos de estructuras definidas en OpenCV

	CvCapture* g_capture = NULL; // Para gestionar la captura de video

	IplImage* newframe, * oldframe; // para gestionar cada frame

	IplImage img;

	// Crea una ventana OpenCV para mostrar el video

	cvNamedWindow(nombre_ventana, CV_WINDOW_AUTOSIZE);

	g_capture = cvCreateFileCapture(file_name); // Abre el archivo de video

	if (NULL == g_capture) {

		printf("\n\nERROR: No se pudo abrir el archivo de video\n\n");

		return;

	}

	// Bucle de proceso de frames

	newframe = cvQueryFrame(g_capture); // Lee frame del archivo
	CvPoint origen = {10,20};
	double antes = 0, gap, ahora;
	CvScalar colorTexto = {255.0, 255.0, 255.0, 0.0};
	CvFont fuenteTexto;
	char buffer[20];
	cvInitFont(&fuenteTexto, CV_FONT_HERSHEY_PLAIN, 1.0f, 1.0f);
	int exito=1;
	while (newframe && (key != 27)) {

		oldframe = newframe;
		ahora = cvGetCaptureProperty(g_capture, CV_CAP_PROP_POS_MSEC);
		exito = _snprintf(buffer, 20, "rafballop: %3.1lf ", ahora / 1000);
		cvPutText(oldframe, buffer, origen, &fuenteTexto, colorTexto);
		cvShowImage(nombre_ventana, oldframe); // Enseña la imagen antigua
		newframe = cvQueryFrame(g_capture); // Carga la actual
		origen.x = (origen.x + 1) % 640;
		origen.y = (origen.y + 10) % 360;
		gap = ahora - antes;
		antes = ahora;
		key = cvWaitKey((int)gap);

	} // end of: while(newframe && (key != 27 ) ) {

	// Cerrar archivo de video

	cvReleaseCapture(&g_capture);

	cvDestroyWindow(nombre_ventana);

}


void funcion(IplImage* img) {

	printf("altura= %d, anchura %d", img->height, img->width);
}