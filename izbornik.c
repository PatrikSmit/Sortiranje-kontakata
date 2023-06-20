#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "kontakt.h"
#include "functions.h"

void izbornik(const char* const ime) {// 9
	int pocetak;
	do {
		printf("\t_____IZBORNIK:_____\n\n");//8


		printf("Opcija 1: Kreiraj Datoteku\n");
		printf("Opcija 2: Dodavanje kontakta\n");
		printf("Opcija 3: Ucitaj sve kontakte\n");
		printf("Opcija 4: Ispisi podatke o svim kontaktima\n");
		printf("Opcija 5: Pretrazivanje kontakata po ID-u\n");
		printf("Opcija 6: Uredivanje kontakta\n");
		printf("Opcija 7: Brisanje kontakta\n");
		printf("Opcija 8: Sortiraj kontakte abecednim redom\n");
		printf("Opcija 9: Izlaz iz programa\n");

		static KONTAKT* pronadeniKontakt = NULL;//4 9 10
		static KONTAKT* poljeKontakata = NULL;//4 9 10

		scanf("%d", &pocetak);

		switch (pocetak) {

		case 1:
			kreiranjeDatoteke(ime);//4 10
			break;

		case 2:
			dodajKontakt(ime);//4 10
			break;

		case 3:
			if (poljeKontakata != NULL) {
				free(poljeKontakata); //14
			}

			poljeKontakata = (KONTAKT*)ucitajKontakte(ime);//9

			if (poljeKontakata == NULL) {
				exit(EXIT_FAILURE);
			}
			break;

		case 4:
			if (poljeKontakata != NULL) {
				free(poljeKontakata);//14
			}

			poljeKontakata = (KONTAKT*)ucitajKontakte(ime);// 10 9
			ispisiSveKontakte(poljeKontakata);//10
			break;

		case 5:
			pronadeniKontakt = (KONTAKT*)pretraziKontakte(poljeKontakata);// 10 9

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
				free(poljeKontakata);//14
			}

			poljeKontakata = (KONTAKT*)ucitajKontakte(ime);// 10 9

			uredivanjeKontakta(poljeKontakata, ime); //10
			break;

		case 7:
			if (poljeKontakata != NULL) {
				free(poljeKontakata);//14
				poljeKontakata = NULL;
			}

			poljeKontakata = (KONTAKT*)ucitajKontakte(ime);// 10 9

			brisanjeKontakta(poljeKontakata, ime);//10
			break;

		case 8:
			ispisiAbecednimRedom(poljeKontakata);//10
			break;

		case 9:
			izlazIzPrograma(poljeKontakata);//10
			break;
		default:
			break;
		}
	} while (pocetak != 9);

}
