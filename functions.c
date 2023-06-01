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
void ispisiSveKontakte(const KONTAKT* const polje) {

	if (polje == NULL) {
		printf("Polje kontakata prazno\n");
		return;
	}

	int i;

	for (i = 0; i < brKontakata; i++) {
		printf("Kontakt broj %d\nID: %d\nIme: %s\nPrezime: %s\nGodine: %d\nAdresa: %s\nMobitel: %s\n\n",
			i + 1,
			(polje + i)->id,
			(polje + i)->ime,
			(polje + i)->prezime,
			(polje + i)->godine,
			(polje + i)->adresa,
			(polje + i)->brojMobitela);
	}
}

KONTAKT* pretraziKontakte(KONTAKT* const polje) {

	if (polje == NULL) {
		printf("Polje kontakata prazno\n");
		return NULL;
	}

	int i;

	int trazeniId;

	printf("Unesite ID kontakta kojeg trazite: \n");

	do {
		scanf("%d", &trazeniId);

		if (trazeniId < 1 || trazeniId > brKontakata) {
			printf("Kontakt s unesenim ID-em ne postoji. Unesite ID koji postoji: ");
		}
	} while (trazeniId < 1 || trazeniId > brKontakata);

	for (i = 0; i < brKontakata; i++) {

		if (trazeniId == (polje + i)->id) {
			printf("Kontakt pronaden.\n");

			return (polje + i);
		}
	}

	return NULL;
}

void uredivanjeKontakta(KONTAKT* polje, const char* const ime) {

	if (brKontakata == 0) {
		printf("Polje kontakata prazno\n");
		return;
	}

	FILE* fp = fopen(ime, "rb+");

	if (fp == NULL) {
		perror("Azuriranje kontakata");
		exit(EXIT_FAILURE);
	}

	int trazeniId;

	printf("Unesite ID kontakta kojeg zelite azurirati: ");

	do {
		scanf("%d", &trazeniId);

		if (trazeniId < 0 || trazeniId > brKontakata) {
			printf("Kontakt s unesenim ID-em ne postoji. Unesite ID koji postoji: ");
		}
	} while (trazeniId < 0 || trazeniId > brKontakata);

	KONTAKT temp = { 0 };

	temp.id = trazeniId;

	getchar();
	printf("Unesite ime kontakta (trenutno: %s): ", (polje + trazeniId - 1)->ime);
	scanf("%24[^\n]", temp.ime);
	getchar();

	printf("Unesite prezime korisnika (trenutno %s): ", (polje + trazeniId - 1)->prezime);
	scanf("%24[^\n]", temp.prezime);
	getchar();

	printf("Unesite godine korisnika (trenutno %d): ", (polje + trazeniId - 1)->godine);
	scanf("%d", &temp.godine);
	getchar();

	printf("Unesite adresu korisnika (trenutno %s): ", (polje + trazeniId - 1)->adresa);
	scanf("%49[^\n]", temp.adresa);
	getchar();

	printf("Unesite broj mobitela korisnika (trenutno %s): ", (polje + trazeniId - 1)->brojMobitela);
	scanf("%10[^\n]", temp.brojMobitela);

	fseek(fp, sizeof(int), SEEK_SET);
	fseek(fp, sizeof(KONTAKT) * (trazeniId - 1), SEEK_CUR);
	fwrite(&temp, sizeof(KONTAKT), 1, fp);

	printf("Kontakt uspjesno azuriran\n");

	fclose(fp);
}

void brisanjeKontakta(KONTAKT* const polje, const char* const ime) {

	if (brKontakata == 0) {
		printf("Polje kontakata prazno\n");
		return;
	}

	FILE* fp = fopen(ime, "rb+");

	if (fp == NULL) {
		perror("Brisanje kontakata");
		exit(EXIT_FAILURE);
	}

	fseek(fp, sizeof(int), SEEK_CUR);

	int i, trazeniId;

	printf("Unesite ID kontakta kojeg zelite obrisati: ");

	do {
		scanf("%d", &trazeniId);

		if (trazeniId < 1 || trazeniId > brKontakata) {
			printf("Kontakt s unesenim ID-em ne postoji. Unesite ID koji postoji: ");
		}
	} while (trazeniId < 1 || trazeniId > brKontakata);

	KONTAKT* pomocnoPolje = (KONTAKT*)calloc(brKontakata - 1, sizeof(KONTAKT));

	if (polje == NULL) {
		perror("Neuspjelo dinamicko zauzimanje memorije");
		exit(EXIT_FAILURE);
	}

	int c = 0;

	for (i = 0; i < brKontakata; i++) {

		if (trazeniId != (polje + i)->id) {
			*(pomocnoPolje + c) = *(polje + i);

			if ((pomocnoPolje + c)->id > trazeniId) {
				(pomocnoPolje + c)->id -= 1;
			}

			fwrite((pomocnoPolje + c), sizeof(KONTAKT), 1, fp);
			c++;
		}
	}

	free(pomocnoPolje);//15 14
	pomocnoPolje = NULL;

	rewind(fp);

	fwrite(&c, sizeof(int), 1, fp);
	fclose(fp);

	printf("Kontakt je uspjesno obrisan\n");
}

void zamjena(KONTAKT* const veci, KONTAKT* const manji) {
	KONTAKT temp = { 0 };
	temp = *manji;
	*manji = *veci;
	*veci = temp;
}



int izlazIzPrograma(KONTAKT* polje) {

	free(polje);

	return 0;
}
