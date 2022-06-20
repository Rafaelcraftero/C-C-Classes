#include <stdio.h>

#include <locale.h>

#include <conio.h>

#include <windows.h>

#include "opencv/cv.h"
#include "opencv/highgui.h" 

#include "rafballop-P03-Static.h"
#include "rafballop-P03-Dynamic.h"
//extern char FuncionLib_rafballop26[];
//extern void VarGlobaLib_rafballop26(char*);
//C:\Users\Rafae\OneDrive\Escritorio\SSRoot\rafballop\P03\rafballop-SolP03\rafballop-P03-Static\rafballop-P03-Static.h
// $(SolutionDir)rafballop-P03-Static
//$(OutDir)

/*#ifdef __cplusplus
extern "C" {
#endif
	extern void VarGlobaLib_rafballop26(char*);
	extern char FuncionLib_rafballop26[];
#ifdef __cplusplus
}
#endif
*/
static void play(char*, char*);
int main(int argc, char* argv[], char* envp[])
{
	setlocale(LC_ALL, "Spanish");
	play((char*)"P01Eje1.mp4", (char*)"Ventana 1");

	_getch();
	return 0;
}

static void play(char* file_name, char* nombre_ventana)
{
	char key = 0;
	CvCapture* g_capture = NULL;	// Para gestionar la captura de video
	IplImage* newframe, * oldframe; // para gestionar cada frame

								   // Crea una ventana OpenCV para mostrar el video
	cvNamedWindow(nombre_ventana, CV_WINDOW_AUTOSIZE);
	g_capture = cvCreateFileCapture(file_name);	// Abre el archivo de video
	if (NULL == g_capture)
		printf("\n\nERROR: No se pudo abrir el archivo de video\n\n");
	else
	{
		CvFont font;
		CvPoint org;
		double antes = 0, gap, ahora;
		char buffer[20];
		// Bucle de proceso de frames
		newframe = cvQueryFrame(g_capture); // Lee frame del archivo
		while (newframe && (key != 27)) {
			oldframe = newframe;

			// Prueba de uso de una DLL sin biblioteca de importación

			{

				HMODULE HLibreriaDll; // Handle. Lo veremos en el tema siguiente.

				// Puntero a función. Comparar la definición con la definición de Firma_nusuario en el archivo .h

				void(*pFuncion)(CvArr*);

				HLibreriaDll = LoadLibrary("rafballop-P03-Dynamic.dll"); // “Carga” la dll donde está la func.

				if (HLibreriaDll != NULL)

				{

					pFuncion = (void(*)(CvArr*))GetProcAddress(HLibreriaDll,

						"?Firma_rafballop_dll@@YAXPAX@Z");

					if (pFuncion != NULL) // Usar el dato/función

						(*pFuncion)(oldframe);

					FreeLibrary(HLibreriaDll); // Libera la librería

				}

			}

			//Firma_rafballop_dll(oldframe);
			Firma_rafballop(oldframe);


			snprintf(buffer, 20, "%lf ", cvGetCaptureProperty(g_capture, CV_CAP_PROP_POS_MSEC) / 1000);//Ej. 1.20
			cvShowImage(nombre_ventana, oldframe);// Enseña la imagen antigua
			newframe = cvQueryFrame(g_capture);	// Carga la actual
			ahora = cvGetCaptureProperty(g_capture, CV_CAP_PROP_POS_MSEC);
			gap = ahora - antes;
			antes = ahora;              // Lee la posición de tiempo del frame
			key = cvWaitKey((int)gap); // Espera que se pulse una tecla con un timeout de 42 ms(aprox,velocidad normal)
			// Aquí podemos decodificar la tecla
		}  // end of:   while(newframe && (key != 27 ) ) {
		   // Cerrar archivo de video
		cvReleaseCapture(&g_capture);
	}
	cvDestroyWindow(nombre_ventana);
}