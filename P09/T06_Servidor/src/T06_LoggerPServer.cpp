#define _CRT_SECURE_NO_WARNINGS
#include "pLibSS.h"
#define NRO_CONEXIONES_SIMULTANEAS 1
// Normalmente NRO_CONEXIONES_SIMULTANEAS y NRO_HILOS_SIRVIENDO son iguales? 
#define NRO_HILOS_SIRVIENDO 1

#define TAM_BUFFER_ENTRADA 1000

DWORD WINAPI GestionaTuberia2(char * pNombreTuberia)
{
	char BEntrada[TAM_BUFFER_ENTRADA];	// Reserva para buffer de entrada
	DWORD Leidos, Escritos;
	BOOL ResOperacion;
	HANDLE hPipe;	// Handle para una instancia del pipe. 

	hPipe = CreateNamedPipe(pNombreTuberia,	//Nomnbre
		PIPE_ACCESS_DUPLEX,				// Modo apertura
		PIPE_TYPE_MESSAGE | PIPE_WAIT,	// Cómo funciona
		NRO_CONEXIONES_SIMULTANEAS,								// Nro. máx. de conexiones
		0,		// Tamańo de buffers salida. 0= tam. por defecto
		0,		// Idem entrada.
		5000,   // Timeout en operacioes ReadFile, WriteFile
		0);		// Overlapped.
	CheckError(INVALID_HANDLE_VALUE == hPipe, "Error creando tubería", 1);

	// Espera conexión
	printf("Servidor: Esperando conexión entrante...\n");
	CheckError(FALSE == ConnectNamedPipe(hPipe, NULL), "Error esperando conexion tubería", 1);
	printf("Conectada tubería...\n");
	Beep(500, 200); // Aviso de que comienza a leer.
	//Sleep(5000);
	while (TRUE)
	{
		ResOperacion = ReadFile(hPipe, BEntrada, sizeof(BEntrada), &Leidos, 0);
		//Procesa condición cliente cierra tubería
		//if (FALSE == ResOperacion && ERROR_BROKEN_PIPE == GetLastError())
		//		break;
		CheckError(FALSE == ResOperacion, "Error leyendo tubería", 1);
		// Procesamos entrada
		// Forzamos \0 en la cadena de entrada
		BEntrada[Leidos] = '\0';
		printf("%s", BEntrada);

		Beep(1000, 200); // Aviso...
		// Si enviamos respuesta al cliente:
		//ResOperacion = WriteFile(hPipe, BEntrada, Leidos, &Escritos, 0);
		//CheckError(FALSE == ResOperacion || Leidos != Escritos,
		//	"Error escribiendo tubería", 1);
	}
	// Desconecta tubería
	CheckError(FALSE == DisconnectNamedPipe(hPipe), "Error desconectando conexion tubería", -1);
	CloseHandle(hPipe); // Cierra instancia de la tubería (y la tubería)
}


// Función de entrada del proyecto 
int main2(int argc, char *argv[])
{
	int i;
	HANDLE ht[NRO_HILOS_SIRVIENDO];
	char * pNombreTuberia = "\\\\.\\pipe\\Logger";
	
	setlocale(LC_ALL, "Spanish");	

	GestionaTuberia2(pNombreTuberia);
	////Crear NRO_HILOS_SIRVIENDO hilos 
	//for (i = 0; i< NRO_HILOS_SIRVIENDO; i++)
	//{
	//	ht[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)GestionaTuberia, hPipe, 0, NULL);
	//	CheckError(NULL == ht[i], "ERROR al crear hilo", 1);
	//}

	//for (i = 0; i< NRO_HILOS_SIRVIENDO; i++)
	//{
	//	CheckError(0 != WaitForSingleObject(ht[i], INFINITE), "ERROR al bloquear main", 1);
	//}

	printf("\nPulse tecla RETORNO para terminar\n");
	getchar();
	return 0;
}

