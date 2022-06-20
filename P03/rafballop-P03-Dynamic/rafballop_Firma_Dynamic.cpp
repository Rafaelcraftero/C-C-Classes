#include <stdio.h>
#include <windows.h>
#include "rafballop-P03-Dynamic.h"

static char msg[100];
static int i = 0;

void Firma_rafballop_dll(CvArr* imagen) {
	CvPoint org;
	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_DUPLEX, 1.0f, 1.0f);

	cvPutText(imagen, "rafballop dinamico", CvPoint(org.x = 100, org.y = cvGetSize(imagen).height - 100), &font, cvScalar(255.0));


	OutputDebugString(msg);
}
