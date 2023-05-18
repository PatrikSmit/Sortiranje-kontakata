#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "kontakt.h"

int main(void) {

	int pocetak = 1;

	char* datoteka = "kontakti.bin";

	while (pocetak) {

		pocetak = izbornik(datoteka);
	}

	printf("Kraj programa.");

	return 0;
}