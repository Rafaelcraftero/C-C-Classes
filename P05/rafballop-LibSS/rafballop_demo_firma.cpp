#include <stdio.h>
#include <windows.h>

#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "rafballop-LibSS.h"
static char msg[100];
static int i = 0;
void Firma_rafballop(CvArr* imagen) {
	CvPoint org;
	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_DUPLEX, 1.0f, 1.0f);
	cvPutText(imagen, "rafballop", CvPoint(org.x = 100, org.y = cvGetSize(imagen).height - 30), &font, cvScalar(255.0));
	snprintf(msg, sizeof(msg), "Ejecutada Firma_nusuario #%d veces\n", i++);
	OutputDebugString(msg);
}
