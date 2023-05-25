#define _CRT_SECURE_NO_WARNINGS //6
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "kontakt.h"

int main(void) {

	int pocetak = 1;

	while (pocetak) {

		pocetak = izbornik(datoteka);
	}

	return 0;
}
