#include "ProyectoP08.h"
void incremento_H();
#define NRO_VENTANAS 2
#define NRO_VIDEOS 2
#define TAM_CAD 200
#include <iostream>
#include <thread>
#include <mutex>

static double mSecsTotal;
typedef struct {
	HANDLE h;
	DWORD id;
	int nroHilo;
	int totalHilos;

	char nombreArchivo[TAM_CAD];

	HANDLE evFin;

}di_reproduce_t, * pdi_reproduce_t;


pdi_reproduce_t infoHilos[NRO_VENTANAS];
HANDLE evMostrarCuenta;

bool parar;
HANDLE hThreads[NRO_HILOS];
std::mutex m;
std::mutex m2;
int main(int argc, char* argv[])
{

	setlocale(LC_ALL, "Spanish");	// Indica que debe usar español como idioma por defecto
	char* argv2[2] = {(char*) "P10Eje1_corto.mp4", (char*)"P10Eje2_Corto.mp4"};
	


	for (size_t i = 0; i < 2; i++)
	{
		pdi_reproduce_t p = new di_reproduce_t;

		p->nroHilo = i;
		p->totalHilos = NRO_VIDEOS;
		strncpy(p->nombreArchivo, argv2[i], sizeof(p->nombreArchivo));
		CheckError(NULL == p->evFin, "No se ha podido crear el evento de terminación", 1);

		p->h = CreateThread(NULL, 0, MuestraVideoN, p, 0, NULL);
		CheckError(p->h == NULL, "Error al crear el hilo", 1);
		infoHilos[i] = p;
	}

	while (TRUE) {



	}
	
	return 0;
}




DWORD WINAPI MuestraVideoN(LPVOID lpParameter) {
	m.lock();
	pdi_reproduce_t pdi = (pdi_reproduce_t)lpParameter;
	int tecla;	// permite leer las teclas que pulsa el usuario en las ventanas openCV

	IplImage* imgOriginal;
	CvCapture* g_capture = cvCreateFileCapture(pdi->nombreArchivo);	// Abre el archivo de video
	CheckError(NULL == g_capture, "\n\nERROR: No se pudo abrir el archivo de video\n\n", 1);
	imgOriginal = cvQueryFrame(g_capture); // Lee frame del archivo
	CheckError(NULL == imgOriginal, "\n\nNo se ha podido leer el frame\n\n", 1);


	double retrasoAcumulado = 0.0; // permite calcular la velocidad de proceso de las imágenes
	int nroImagenes = 0;
	int segsEnteros = 0;
	int recuento = 0;

	do
	{

		m2.lock();
		char mensaje[200];
		IplImage* imgResultado = cvQueryFrame(g_capture);
		if (0 == imgResultado)
			break;
		double ahora = cvGetCaptureProperty(g_capture, CV_CAP_PROP_POS_MSEC) / 1000;
		segundos = ahora;
		printf("%f", ahora);
		if (segsEnteros != (int)ahora && ahora - recuento > 0) {

			mSecsTotal = segundos + mSecsTotal;
			recuento = segundos + 5;
			m.unlock();

		}

		segsEnteros = (int)ahora;
		if (retrasoAcumulado < ahora)
			Sleep((DWORD)((ahora - retrasoAcumulado) * 1000));
		retrasoAcumulado = ahora;

		nroImagenes++;
		// Construimos el mensaje

		snprintf(mensaje, sizeof(mensaje),
			"rafballop %.2f \nPulsa ENTER para terminar", ahora);
		// Muestra el resultado
		ImagenAVentana(imgOriginal, (char*)"Ventana 1", mensaje, true, &tecla);
		m2.unlock();
	} while (tecla != 13 && NULL != imgOriginal);	// salimos cuando el usuario pulsa la tecla Retorno
	m.unlock();
	cvReleaseCapture(&g_capture);

	return 0;
}

void miniMenu() {
	int nroCampos, cmd = 0;
	while (TRUE) {
		char ent[20] = "Ninguno";

		system("CLS");    // Ejecuta el comando CLS (clear screen) en el shell

		printf("<0  - Salir\n0 - %d Cerrar ventana i\n", NRO_VENTANAS - 1);

		nroCampos = scanf("%d", &cmd); // Ojo, esto fall cuando no le pasamos una entrada correcta					   // Ver cómo se corrige en clase usando gets_s y sscanf
		if (nroCampos != 1) {
			// Corrección:
			while ('\n' != getchar());// vacía el buffer de entrada. 
							   // Si scanf tiene un error al convertir la entrada, no la "consume"

			Beep(1000, 500);  // Avisa que ha habido un error
			continue;
		}
		if (cmd < 0)
			ExitProcess(0); // Termina el programa
		else if (cmd >= 0 && cmd < NRO_VENTANAS) {
			SetEvent(infoHilos[cmd]->evFin);
			WaitForSingleObject(infoHilos[cmd]->h, INFINITE);
		}
	}
}




typedef struct {
	HANDLE ht;
} diInc, * pdiInc;

int contador = 0;



// Este valor se calcula correctamente: no da tiempo a cambios de hilo en mitad de los hilos
//#define NRO_INCREMENTOS (10*100) 
#define NRO_INCREMENTOS (10*1000)

//Cada hilo la incrementa en 1 NRO_INCREMENTOS veces 
DWORD WINAPI IncrAsync(LPVOID lpParameter) {
	pdiInc pdi[N];   // Matriz de punteros a datos de instancia de los hilos
	for (int i = 0; i < N; i++) {// dos iteraciones, una por hilo
		pdi[i] = new diInc;//Reservamos el espacio de memoria	
		pdi[i]->ht = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)incremento_H, pdi[i], 0, NULL);//creamos el hilo
		CheckError(NULL == pdi[i]->ht, "No se pudo crear el hilo", 1);//Comprobamos que se pudiese crear el hilo
	}
	for (int i = 0; i < N; i++) { //Espera a que terminen todos los hilos
		WaitForSingleObject(pdi[i]->ht, INFINITE); //Bloquea hasta que termine hilo i
	}
	printf("%d", contador);
	return 0;
}

void incremento_H() {

	for (int i = 0; i < NRO_INCREMENTOS; i++) {
		EnterCriticalSection(&cs);
		contador++;
		LeaveCriticalSection(&cs);
	}
}