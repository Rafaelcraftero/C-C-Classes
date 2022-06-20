
#include "ProyectoP08.h"

char* ImagenAVentana(IplImage* img,	// imagen a mostrar
	char* preTituloVentana,	// con esto construimos el título de la ventana
	char* mensaje,		// Mensaje a mostrar sobre la imagen
	bool refrescar,		// si true, se refresca el contenido de la ventana
	int* tecla)			// sirve para devolver la tecla que ha pulsado el usuario
	// la función devuelve el nombre de la ventana. Este nombre se puede usar para cerrar la ventana, por ejemplo
{
	double relacionanchoalto;
	char tituloVentana[200];
	int alturaVentana = 200;	// Altura mínima de la ventana
	static char tituloUltimaVentanaCreada[200];
	CvFont font;
	char mensajeCompleto[200];
	int altoTexto = 0;
	CvScalar color = { 255.0, 255.0, 255.0, 255.0 };

	// Si la altura de la imagen es menor que la altura mínima, uso alturaVentana. Así evito que
	//	esas imagenes se muestren en ventanas demasiado pequeñas. 
	if (img->height > alturaVentana)
		alturaVentana = img->height;
	// Construimos el título de la ventana, añadiendo el tamaño de la imagen a la
	// cadena del título de la ventana
	snprintf(tituloVentana, sizeof(tituloVentana), "%s (%dx%d)", preTituloVentana, img->width, img->height);

	// Guardamos el nombre de la última ventana creada.
	// si detecta un cambio de nombre respecto a la última, vuelve a crear la ventana. 
	if (strncmp(tituloVentana, tituloUltimaVentanaCreada, sizeof(tituloVentana)) != 0 || refrescar)
	{
		strncpy(tituloUltimaVentanaCreada, tituloVentana, sizeof(tituloUltimaVentanaCreada));
		// Las nueva ventana no se llama igual que la última que se creo. 
		// Se crea una nueva
		cvNamedWindow(tituloVentana, CV_WINDOW_NORMAL);	// Crea ventana
		relacionanchoalto = (double)img->width / img->height;	// La relación de aspecto de la ventana es la de la imagen original
		cvResizeWindow(tituloVentana, (int)(alturaVentana * relacionanchoalto), alturaVentana); // Ajusta el tamaño de la ventana
																							  // inicia la fuente y calcula la altura de una línea de texto
		//Inicia fuente
		int tipoFuente = CV_FONT_HERSHEY_SIMPLEX;
		int grosorFuente = 2;
		cvInitFont(&font, tipoFuente, 1.0, 1.0, 0.0, grosorFuente);
		refrescar = true;
		CvSize tamTxt;
		cvGetTextSize("Solo me interesa el alto", &font, &tamTxt, 0);
		altoTexto = tamTxt.height * 2;
	}
	if (refrescar)
	{
		// Crea una nueva imagen para poder escribir encima antes de mostrarla
		IplImage* imgAMostrar = cvCreateImage(CvSize(img->width, img->height),
			img->depth, img->nChannels);
		cvCopy(img, imgAMostrar);	// copia la imagen original a la creada

		CvPoint puntoTexto(20, altoTexto);
		// Muestra el mensaje
		int tamMensaje = strlen(mensaje) + 1;
		int inicioParcial = 0; // inicio del texto que se imprime en la imagen

		/* OpenCV no soporta el carácter \n. Hay que implementarlo "a mano".
		   Para ello, cada vez que se detecta un \n en el mensaje se escribe
		   la línea desde el último \n detectado y se avanza una línea
		   */
		   // va copiando el contenido de mensaje a mensajeconpleto, pero 
		for (int i = 0; i < tamMensaje; i++)
		{
			// ...si detecta un caracter '\n' lo sustituye por '\0'
			if (mensaje[i] == '\n')
				mensajeCompleto[i] = '\0';
			else
				mensajeCompleto[i] = mensaje[i];
			// si detecta un '\0', pone en la imagen el 
			// texto copiado en mensajeCompleto desde inicioParcial
			if (mensajeCompleto[i] == '\0')
			{
				cvPutText(imgAMostrar, &mensajeCompleto[inicioParcial], puntoTexto, &font, color);
				inicioParcial = i + 1; // marca el inicio del texto que se imprimirá a continuación
				puntoTexto.y += altoTexto; // avanza una línea
			}
		}
		cvShowImage(tituloVentana, imgAMostrar);	// Enseña la imagen
		cvReleaseImage(&imgAMostrar);	// libera la imagen auxiliar
	}
	*tecla = cvWaitKey(1); // Si no se llama a cvWaitKey, OpenCV no muestra la ventana. 
	return (char*)tituloVentana;
}
