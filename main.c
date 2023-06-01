#define _CRT_SECURE_NO_WARNINGS //6
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "kontakt.h"

int main(void) {

	int pocetak = 1;
	char* datoteka = "kontakti.bin";//16


	while (pocetak) {

		pocetak = izbornik(datoteka);//8
	}

	return 0;
}
