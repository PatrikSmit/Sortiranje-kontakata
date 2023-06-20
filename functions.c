#define _CRT_SECURE_NO_WARNINGS// 6
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "kontakt.h"


static int brKontakata = 0;//4 5

void kreiranjeDatoteke(const char* const ime) {
	FILE* fp = fopen("ime", "w+");
	if (fp == NULL) {
		perror("Greska prilikom kreiranja datoteke: ");
		exit(EXIT_FAILURE);
	}
	else {
		printf("Datoteka uspjesno kreirana!\n");
	}
}


void dodajKontakt(const char* const ime) {

	size_t velicinaDatoteke;
	FILE* fp = fopen(ime, "a+");
	if (fp == NULL) {
		perror("Greska prilikom otvaranja datoteke:");//19
		exit(EXIT_FAILURE);
	}
	 
	fseek(fp, 0, SEEK_END);
	velicinaDatoteke = ftell(fp);
	rewind(fp);
	brKontakata = velicinaDatoteke / sizeof(KONTAKT);

	KONTAKT temp = { 0 };
	temp.id = brKontakata + 1;

	printf("Unesite ime kontakta: ");
	scanf(" %19[^\n]", temp.ime);

	printf("Unesite prezime kontakta: ");
	scanf(" %19[^\n]", temp.prezime);

	printf("Unesite godine kontakta: ");
	scanf("%d", &temp.godine);

	printf("Unesite broj mobitela kontakta: ");
	scanf(" %10[^\n]", temp.brojMobitela);

	printf("Unesite adresu kontakta: ");
	scanf(" %29[^\n]", temp.adresa);

	fwrite(&temp, sizeof(KONTAKT), 1, fp);
	brKontakata++;

	printf("Novi kontakt uspjesno dodan.\n");
	fclose(fp);
}


void* ucitajKontakte(const char* const ime) {

	size_t velicinaDatoteke;
	FILE* fp = fopen(ime, "r");

	if (fp == NULL) {
		perror("Ucitavanje kontakata iz datoteke kontakti.txt");//19
		exit(EXIT_FAILURE);
	}

	fseek(fp, 0, SEEK_END);
	velicinaDatoteke = ftell(fp);
	rewind(fp);
	brKontakata = velicinaDatoteke / sizeof(KONTAKT);
	printf("Broj kontakata: %d\n", brKontakata);

	KONTAKT* poljeKontakata = (KONTAKT*)calloc(brKontakata, sizeof(KONTAKT));//14

	if (poljeKontakata == NULL) {
		perror("Zauzimanje memorije kontakata");//19
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

int funkcijaPretrazivanja(const void* a, const void* b) {

	KONTAKT* kotaktA = (KONTAKT*)a;
	KONTAKT* kotaktB = (KONTAKT*)b;

	if (kotaktA->id < kotaktB->id) return -1;
	else if (kotaktA->id > kotaktB->id) return 1;
	else return 0;

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

	KONTAKT trazeni_kontakt = { .id = trazeniId };

	return (KONTAKT*)bsearch(&trazeni_kontakt, polje, brKontakata, sizeof(KONTAKT), funkcijaPretrazivanja);

	return NULL;
}

void uredivanjeKontakta(KONTAKT* polje, const char* const ime) {

	if (brKontakata == 0) {
		printf("Polje kontakata prazno\n");
		return;
	}

	FILE* fp = fopen(ime, "r+");

	if (fp == NULL) {
		perror("Azuriranje kontakata");
		exit(EXIT_FAILURE);
	}

	int trazeniId;

	printf("Unesite ID kontakta kojeg zelite azurirati: ");

	do {
		fflush(stdin);
		scanf("%d", &trazeniId);

		if (trazeniId < 0 || trazeniId > brKontakata) {
			printf("Kontakt s unesenim ID-em ne postoji. Unesite ID koji postoji: ");
		}
	} while (trazeniId < 0 || trazeniId > brKontakata);

	KONTAKT temp = { 0 };

	temp.id = trazeniId;

	printf("Unesite ime kontakta (trenutno: %s): ", (polje + trazeniId - 1)->ime);
	scanf(" %19[^\n]", temp.ime);

	printf("Unesite prezime korisnika (trenutno %s): ", (polje + trazeniId - 1)->prezime);
	scanf(" %19[^\n]", temp.prezime);

	printf("Unesite godine korisnika (trenutno %d): ", (polje + trazeniId - 1)->godine);
	scanf(" %d", &temp.godine);

	printf("Unesite adresu korisnika (trenutno %s): ", (polje + trazeniId - 1)->adresa);
	scanf(" %29[^\n]", temp.adresa);

	printf("Unesite broj mobitela korisnika (trenutno %s): ", (polje + trazeniId - 1)->brojMobitela);
	scanf(" %10[^\n]", temp.brojMobitela);

	fseek(fp, sizeof(KONTAKT) * (trazeniId - 1), SEEK_SET);
	fwrite(&temp, sizeof(KONTAKT), 1, fp);

	printf("Kontakt uspjesno azuriran!\n");

	fclose(fp);
}

void brisanjeKontakta(KONTAKT* const polje, const char* const ime) {

	if (brKontakata == 0) {
		printf("Polje kontakata prazno\n");
		return;
	}
	size_t velicinaDatoteke;
	FILE* fp = fopen(ime, "r+");

	if (fp == NULL) {
		perror("Brisanje kontakata");
		exit(EXIT_FAILURE);
	}

	fseek(fp, 0, SEEK_END);
	velicinaDatoteke = ftell(fp);
	rewind(fp);
	brKontakata = velicinaDatoteke / sizeof(KONTAKT);
	printf("Broj kontakata: %d\n", brKontakata);

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

			c++;
		}
	}

	fclose(fp);
	fp = fopen(ime, "wb");
	fwrite(pomocnoPolje, sizeof(KONTAKT), brKontakata - 1, fp);

	free(pomocnoPolje);//15 14

	fclose(fp);

	printf("Kontakt je uspjesno obrisan\n");
}


int funkcijaUsporedbe(const void* a, const void* b) {

	KONTAKT* kotaktA = (KONTAKT*)a;
	KONTAKT* kotaktB = (KONTAKT*)b;

	return strcmp(kotaktA->prezime, kotaktB->prezime);
}

void ispisiAbecednimRedom(KONTAKT* const polje) {

	qsort(polje, brKontakata, sizeof(KONTAKT), funkcijaUsporedbe);

	printf("Sortirani kontakti:\n");
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


void izlazIzPrograma(KONTAKT* polje) {

	free(polje);
}
