#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "kontakt.h"


static int brKontakata = 0;

int izbornik(const char* const ime) {

	printf("\t_____IZBORNIK:_____\n\n");


	printf("Opcija 1: Kreiraj Datoteku\n");
	printf("Opcija 2: Dodavanje kontakta\n");
	printf("Opcija 3: Ucitaj sve kontakte\n");
	printf("Opcija 4: Ispisi podatke o svim kontaktima\n");
	printf("Opcija 5: Pretrazivanje kontakata po ID-u\n");
	printf("Opcija 6: Uredivanje kontakta\n");
	printf("Opcija 7: Brisanje kontakta\n");
	printf("Opcija 8: Sortiraj abecednim redom\n");
	printf("Opcija 9: Izlaz iz programa\n");
	int pocetak = 0;

	/*static KONTAKT* pronadeniKontakt = NULL;
	static KONTAKT* poljeKontakata = NULL;

	scanf("%d", &pocetak);

	switch (pocetak) {

	case 1:

		kreiranjeDatoteke(ime);
		break;

	case 2:

		dodajKontakt(ime);
		break;

	case 3:

		if (poljeKontakata != NULL) {
			free(poljeKontakata);
			poljeKontakata = NULL;
		}

		poljeKontakata = (KONTAKT*)ucitajKontakte(ime);

		if (poljeKontakata == NULL) {
			exit(EXIT_FAILURE);
		}
		break;

	case 4:

		ispisiKontakte(poljeKontakata);
		break;

	case 5:

		pronadeniKontakt = (KONTAKT*)pretraziKontakte(poljeKontakata);

		if (pronadeniKontakt != NULL) {
			printf("ID: %d\n", pronadeniKontakt->id);
			printf("Ime: %s\n", pronadeniKontakt->ime);
			printf("Prezime: %s\n", pronadeniKontakt->prezime);
			printf("Godine: %d\n", pronadeniKontakt->godine);
			printf("Broj mobitela: %s\n", pronadeniKontakt->brojMobitela);
			printf("Adresa: %s\n", pronadeniKontakt->adresa);
		}
		else {
			printf("Clan sa tim ID-em ne postoji.\n");
		}

		break;

	case 6:

		if (poljeKontakata != NULL) {
			free(poljeKontakata);
			poljeKontakata = NULL;
		}

		poljeKontakata = (KONTAKT*)ucitajKontakte(ime);

		uredivanjeKontakta(poljeKontakata, ime);
		break;
	
	case 7:

		ispisiAbecednimRedom(poljeKontakata);
		break;

	case 8:

		if (poljeKontakata != NULL) {
			free(poljeKontakata);
			poljeKontakata = NULL;
		}

		poljeKontakata = (KONTAKT*)ucitajKontakte(ime);

		brisanjeKontakta(poljeKontakata, ime);
		break;
	
	case 9:

		pocetak = izlazIzPrograma(poljeKontakata);
		break;
	default:
		pocetak = 0;
	}

	return pocetak;*/
	return 0;
	
}