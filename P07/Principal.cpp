#include "ProyectoP07.h"
// poner aquí todos los archivos de includes adicionales necesarios
void miniMenu();
DWORD WINAPI reproduce_h(LPVOID lpParameter);
HANDLE hReproduce;
BOOL parar = false;
int numeroDeHilos = 0;
int main(int argc, char* argv[])

{	// comprueba que el usuario ha puesto el ancho y alto de la imagen en línea de comandos
	setlocale(LC_ALL, "Spanish"); // Previo
	CheckError(argc != 2, "Debe haber al menos 2 argumentos (alto y ancho de la imagen)", 1);

	//Ejercicio6_4(argv);

	printf("Numero de hilos: ");
	scanf("%d", &numeroDeHilos);
	hReproduce = CreateThread(NULL, 0, reproduce_h, argv[1], 0, NULL);
	CheckError(NULL == hReproduce, "Error al crear el hilo de reproducción", 1);
	miniMenu();
	return 0;
}

DWORD WINAPI reproduce_h(LPVOID lpParameter) {
	int tecla;	// permite leer las teclas que pulsa el usuario en las ventanas openCV

	IplImage* imgOriginal;
	CvCapture* g_capture = cvCreateFileCapture((char*)lpParameter);	// Abre el archivo de video
	CheckError (NULL == g_capture, "\n\nERROR: No se pudo abrir el archivo de video\n\n", 1);
	imgOriginal = cvQueryFrame(g_capture); // Lee frame del archivo
	if (NULL == imgOriginal) {
		return 0;
	}
	
	IplImage* imgResultado = cvCreateImage(CvSize(imgOriginal->width, imgOriginal->height),
		imgOriginal->depth, imgOriginal->nChannels);

	double retrasoAcumulado = 0.0; // permite calcular la velocidad de proceso de las imágenes
	int nroImagenes = 0;
	do
	{
		if (!parar) {

			char mensaje[200];
			MideRetraso(0);	//<-- Solo medimos el tiempo de proceso de la imagen. Desde aquí
			//ProcesaImagen(imgOriginal, imgResultado);
			//InvierteFila_2x(imgOriginal, imgResultado);
			InvierteFilas_Nx(imgOriginal, imgResultado, numeroDeHilos);//Empieza a ir mas lento a partir del 5 hilo
			//Sleep(100);
			retrasoAcumulado += MideRetraso(0);	// --> hasta aquí
			nroImagenes++;
			// Construimos el mensaje

			snprintf(mensaje, sizeof(mensaje),
				"procesando %d imagenes en %.2f segs\n(%.2f imgs/s)\nPulsa ENTER para terminar",
				nroImagenes, retrasoAcumulado, nroImagenes / retrasoAcumulado);
			// Muestra el resultado

			ImagenAVentana(imgResultado, "RESULTADO:", mensaje, true, &tecla);
			imgOriginal = cvQueryFrame(g_capture); // Lee frame del archivo
		}

	} while (tecla != 13 && NULL != imgOriginal);	// salimos cuando el usuario pulsa la tecla Retorno


	return 0;
}

extern double amplitudDistorsion;
void miniMenu() {
	int nroCampos, cmd = 0;
	while (TRUE) {
		char ent[20] = "Ninguno";

		system("CLS");    // Ejecuta el comando CLS (clear screen) en el shell
		
		printf("Ultimo comando: %d\nY ahora?\n\n", cmd);
		printf("0  - Salir\n<0 - Parar/Continuar\n>0 - Modificar amplitud  distorsion\n¿Nuevo comando?\n");

		nroCampos = scanf("%d", &cmd); // Ojo, esto fall cuando no le pasamos una entrada correcta					   // Ver cómo se corrige en clase usando gets_s y sscanf
		if (nroCampos != 1) {
			// Corrección:
			while ('\n' != getchar());// vacía el buffer de entrada. 
							   // Si scanf tiene un error al convertir la entrada, no la "consume"

			Beep(1000, 500);  // Avisa que ha habido un error
			continue;
		}
		if (cmd == 0)
			ExitProcess(0); // Termina el programa
		else if (cmd > 0 && cmd < 100)
			amplitudDistorsion = cmd; //obtenemos amplituddistorsion
		else if (cmd < 0) {
			parar = parar ? false: true; //paramos lo que hace dentro del while do
		}
	}
}
