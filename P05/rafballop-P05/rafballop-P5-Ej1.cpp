#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <psapi.h>
#include <math.h>
#include <tchar.h>
#include <locale.h>
#include <fileapi.h>	
#include "rafballop-LibSS.h"
#define FILE_LIST_DIRECTORY

int EscribeK(int NroKBytes, char* NombreArchivo);
#define TAM_BUFFER 30000 //Definimos un tamaño grande para el buffer, así no nos dará error
void ejercicio9();
void ejercicio17();

int main(int argc, char* argv[], char* envp[]) {

	setlocale(LC_ALL, "Spanish");
	BOOL funciono = false;
	EscribeK(1024 * 200, (char*)"C://Users//Rafae//OneDrive//Escritorio//a.txt");
	//Sleep(500);
	double res = MideRetraso("Retraso en segs despues de ejecutar EscribeK: ");
	printf("Velocidad de escritura del disco duro en MBytes por segundo: %f MB por seg.\n", ((1024 * 200) / pow(2, 10)) / res);
	
	//Ejercicio 9
	ejercicio9();

	//Fin ejercicio 9

	//Ejercicio 17
	ejercicio17();	

	//Fin Ejercicio 17


	printf("Pulse RETORNO para finalizar...");
	_getch();
	return 0;

}
void ejercicio9() {
	//Ejercico 9 Inicio
	BOOL res = false;
	char cad[100] = "Ejercicio 9"; //creamos como se llama la ventana
	int sino = 6; //la id de el Si en MB_YESNO en el MessageBox es 6
	while (sino == 6) {//mientras clique en Si volvera a mostrarse la ventana
		sino = MessageBox(NULL, cad, "Ejercicio 9", MB_YESNO);//cuando clique No sino valdra 7 y se terminara el bucle
		res = false;
	}
	if (sino == 7) {
		res = true; //si sino devuelve 7, es decir, la id del NO devuelve true
	}
	CheckError(res == false, "No se usó el botón No", 1);
	//Fin Ejercicio 9

}

void ejercicio17() {
	//Inicio Ejercicio 17
	char cad[1024] = "";
	PULARGE_INTEGER espacioLibre = (PULARGE_INTEGER)malloc(100); //variable en la que calcularemos el espacio libre
	PULARGE_INTEGER total = (PULARGE_INTEGER)malloc(100); //variable con espacio total del disco

	int compruebafunciona = GetDiskFreeSpaceExA("C:\.", espacioLibre, total, NULL); //llama a la funcion, si la funcion da error devolvera 0
	CheckError(compruebafunciona == 0, "No se pudo comprobar el espacio de los discos", 1); //Comprobamos errores
	_snprintf(cad, 1024, "Total de espacio en el disco duro es: %llu Bytes\nEl espacio ocupado del disco es: %llu Bytes\nEl espacio libre del disco es: %llu Bytes", total->QuadPart, total->QuadPart - espacioLibre->QuadPart, espacioLibre->QuadPart); //(%llu ya que es LONG LONG INT)
	MessageBox(NULL, cad, "Ejercicio 17", 0x00000000L); //haciendo _snprintf podemos mostar en MessageBox el mensaje que pongamos en cad
	//Fin Ejercicio 17

}

int EscribeK(int NroKBytes, char* NombreArchivo)

{

	static char Buffer[1024];

	int counter;

	FILE* ptr_myfile;

	ptr_myfile = fopen(NombreArchivo, "wb");

	if (!ptr_myfile)

	{

		printf("Unable to open file!");

		return 1;

	}

	for (counter = 0; counter < NroKBytes; counter++)

	{

		fwrite(Buffer, sizeof(Buffer), 1, ptr_myfile);

	}

	fclose(ptr_myfile);

	return 0;

}