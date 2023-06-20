#define _CRT_SECURE_NO_WARNINGS //6
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "kontakt.h"

int main(void) {
	char* datoteka = "kontakti.txt";//16

	printf("Pocetak programa!\n");
	izbornik(datoteka);//8

	printf("Program zavrsen!\n");

	return 0;
}
