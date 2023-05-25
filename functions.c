#define _CRT_SECURE_NO_WARNINGS// 6
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "kontakt.h"


static int brKontakata = 0;//4 5
void kreiranjeDatoteke(const char* const ime) {
	FILE* fp = fopen(ime, "rb");
	if (fp == NULL) {
		fp = fopen(ime, "wb");
		fwrite(&brKontakata, sizeof(int), 1, fp);
		fclose(fp);
	}
	else {
		fclosse(fp);
	}
}


	void dodajKontakt(const char* const ime) {

		FILE* fp = fopen(ime, "rb+");
		if (fp == NULL) {
			perror("Dodavanje kontakta u datoteku kontakti.bin");//19
			exit(EXIT_FAILURE);
		}

		fread(&brKontakata, sizeof(int), 1, fp);
		printf("Broj kontakata: %d\n", brKontakata);

		KONTAKT temp = { 0 };
		temp.id = brKontakata + 1;
		getch();

		printf("Unesite ime kontakta: ");
		scanf("%19[^\n]", temp.ime);
		getch();

		printf("Unesite prezime kontakta: ");
		scanf("%19[^\n]", temp.prezime);
		getch();

		printf("Unesite godine kontakta: ");
		scanf("%d", temp.godine);
		getch();

		printf("Unesite broj mobitela kontakta: ");
		scanf("%10[^\n]", temp.brojMobitela);
		getch();

		printf("Unesite adresu kontakta: ");
		scanf("%29[^\n]", temp.adresa);
		getch();
	}
	fseek(fp, sizeof(KONTAKT)* brKontakata, SEEK_CUR);//17
	fwrite(&temp, sizeof(KONTAKT), 1, fp);
	printf("Novi kontakt uspjesno dodan.\n");

	rewind(fp);//17
	brKontakata++;

	fwrite(&brKontakata, sizeof(int), 1, fp);

	fclose(fp);
}

void* ucitajKontakte(const char* const ime) {

	FILE* fp = fopen(ime, "rb");

	if (fp == NULL) {
		perror("Ucitavanje kontakata iz datoteke kontakti.txt");//19
		return NULL;
		exit(EXIT_FAILURE);
	}

	fread(&brKontakata, sizeof(int), 1, fp);
	printf("Broj kontakata: %d\n");

	KONTAKT* poljeKontakata = ((KONTAKT*)calloc(brKontakata), sizeof(KONTAKT));//14

	if (poljeKontakata == NULL) {

		perror("Zauzimanje memorije kontakata");//19
		return NULL;
		exit(EXIT_FAILURE);
	}

	fread(poljeKontakata, sizeof(KONTAKT), brKontakata, fp);
	fclose(fp);

	printf("Kontakti uspjesno ucitani.\n");

	return poljeKontakata;
}