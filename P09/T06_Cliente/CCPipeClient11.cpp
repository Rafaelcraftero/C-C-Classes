#define _CRT_SECURE_NO_WARNINGS
#include "pLibSS.h"
#define TIEMPO_ESPERA_MAXIMO_MS (10*1000)

void UsaTuberia(char* NombreP)
{
	HANDLE hPipeC;	// Handle para una instancia del pipe (cliente). 
	//char BEntrada[1000];	// Reserva para buffer de entrada

	char BSalida[1000], BEntrada[1000];		// Reserva para buffer de 
	DWORD Leidos, Escritos, i;
	BOOL ResOperacion;

	// abre tuber�a...
	WaitNamedPipeA(NombreP, 30000);
	hPipeC = CreateFile(NombreP, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	CheckError(hPipeC == INVALID_HANDLE_VALUE, "Error conectando a tuber�a", 1);

	printf(" ............Cliente conectado\n");

	for (i = 0; i < 3; i++)
	{
		sprintf(BSalida, "Mensaje numero %d\n", i);

		ResOperacion = WriteFile(hPipeC, BSalida, strlen(BSalida) + 1, &Escritos, 0); // Escribe datos
		// Comprueba escritura correcta
		CheckError(FALSE == ResOperacion || Escritos != strlen(BSalida) + 1, "Error escribiendo tuber�a", 1);
		printf("Mensaje Enviado: %s", BSalida);
		ResOperacion = ReadFile(hPipeC, BEntrada, sizeof(BEntrada), &Leidos, 0);
		CheckError(FALSE == ResOperacion, "Error leyendo tuber�a", 1);
		BEntrada[Leidos] = '\0';
		printf("Mensaje Recibido:%s\n", BEntrada);
	}

	CloseHandle(hPipeC);	// Cierra tuber�a

	printf("\nCliente desconectado...\n");

}
// Funci�n de entrada del proyecto "T06_20_PipeClient1"
int main(int argc, char* argv[])
{
	int msegs = TIEMPO_ESPERA_MAXIMO_MS;
	setlocale(LC_ALL, "Spanish");	// Indica que debe usar espa�ol como idioma por defecto

	printf("\nCliente conectar� en %d segs...", msegs / 1000);
	Sleep(TIEMPO_ESPERA_MAXIMO_MS);  // Para dar tiempo a que el servidor arranque 

	UsaTuberia("\\\\.\\pipe\\Logger");
	//UsaTuberia("prueba.txt");

	printf("\nPulse tecla RETORNO para terminar\n");
	getchar();
	return 0;
}
