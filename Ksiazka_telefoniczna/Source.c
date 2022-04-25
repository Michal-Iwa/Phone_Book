#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>


struct kontakt {
	char imie[100];
	char nazwisko[100];
	char numer[100];
	char grupa[100];
};


struct element {
	struct element* poprzedni;
	//int dane;
	struct kontakt Kontakt;
	struct element* nastepny;
};


void wstaw_na_koncu_listy(struct element** poczatek, struct element** koniec, struct kontakt* kontakcik) {
	struct element* nowy;
	nowy = (struct element*)malloc(sizeof(struct element));
	if ((*poczatek) == NULL && (*koniec) == NULL)
	{
		(*poczatek) = nowy;
		(*koniec) = nowy;
		nowy->poprzedni = NULL;
		nowy->nastepny = NULL;
	}
	else
	{
		nowy->poprzedni = koniec;
		(*koniec)->nastepny = nowy;
		(*koniec) = nowy;
		nowy->nastepny = NULL;

	}
	strcpy((nowy->Kontakt).imie, kontakcik->imie);
	strcpy((nowy->Kontakt).nazwisko, kontakcik->nazwisko);
	strcpy((nowy->Kontakt).numer, kontakcik->numer);
	strcpy((nowy->Kontakt).grupa, kontakcik->grupa);
}

void wypisz_kontakt(struct kontakt do_wypisania)
{
	printf("Kontakt: ");
	printf("Imie %s ", do_wypisania.imie);
	printf("Nazwisko %s ", do_wypisania.nazwisko);
	printf("Numer %s ", do_wypisania.numer);
	printf("Gr %s\n", do_wypisania.grupa);
}

void show(struct element* poczatek) {
	if (poczatek != NULL) {
		printf("Elementy w liscie: \n");
		struct element* temp;
		temp = poczatek;
		while (temp != NULL) {
			wypisz_kontakt(temp->Kontakt);
			temp = temp->nastepny;
		}
	}
	else
		printf("Nic do wyswietlenia \n");
}


int isEmpty(struct element* poczatek) {
	if (poczatek == NULL)
		return 1;
	else
		return 0;
}


int countElements(struct element* poczatek) {
	int i = 0;
	if (poczatek != NULL) {
		struct element* temp;
		temp = poczatek;
		while (temp != NULL) {
			i++;
			temp = temp->nastepny;
		}
		return i;
	}
	else
		return i;
}


void delete_element(struct element** top) {
	struct element* temp;
	if (*top == NULL) {
		//czyli nalezy cos z tym zrobic np.
		exit(1);
	}
	else {
		temp = *top;
		(*top) = (*(*top)).poprzedni;
		free(temp);
	}

}


void clear(struct element** poczatek) {
	struct element* temp;
	while (*poczatek != NULL) {
		temp = *poczatek;
		(*poczatek) = (*poczatek)->nastepny;
		free(temp);
	}
}

void wczytaj_z_pliku(struct element** poczatek, struct element** koniec) {
	struct kontakt bufor;
	struct kontakt* wsk_na_bufor;
	wsk_na_bufor = &bufor;

	FILE* plik;
	plik = fopen("kontakty.csv", "r");
	if (plik == NULL)
	{
		printf("Error:nie uda³o siê otworzyæ pliku\n");
		exit(1);
	}
	char znak;
	bool first = true;
	int i = 0;
	while ((znak = getc(plik)) != EOF)
	{
		bufor.imie[0] = znak;
		for (i = 1; (znak = getc(plik)) != 59; i++) //59 to w tabeli ascii ;
		{
			bufor.imie[i] = znak;
		}
		bufor.imie[i] = '\0';
		for (i = 0; (znak = getc(plik)) != 59; i++)
		{
			bufor.nazwisko[i] = znak;
		}
		bufor.nazwisko[i] = '\0';
		for (i = 0; (znak = getc(plik)) != 59; i++)
		{
			bufor.numer[i] = znak;
		}
		bufor.numer[i] = '\0';
		for (i = 0; (znak = getc(plik)) != '\n'; i++)
		{
			bufor.grupa[i] = znak;
		}
		bufor.grupa[i] = '\0';
		wstaw_na_koncu_listy(poczatek, koniec, wsk_na_bufor);
		first = false;
	}
	fclose(plik);
}
int czy_zamiana(char naz1[], char naz2[])
{
	int i = 0;
	char temp1[100], temp2[100];
	strcpy(temp1, naz1);
	strcpy(temp2, naz2);
	for (i = 0; i < (int)strlen(naz1); i++)
	{
		if (naz1[i] > 96 && naz1[i] < 123) naz1[i] = naz1[i] - 32;
	}
	for (i = 0; i < (int)strlen(naz2); i++)
	{
		if (naz2[i] > 96 && naz2[i] < 123) naz2[i] = naz2[i] - 32;
	}
	if (strcmp(naz1, naz2) > 0)
	{
		strcpy(naz1, temp1);
		strcpy(naz2, temp2);
		return 1;
	}
	strcpy(naz1, temp1);
	strcpy(naz2, temp2);
	return 0;
}
void sortowanie_nazwisk(struct element** poczatek, int liczba_elementow)
{
	struct element* temp1;
	struct element* temp2;
	struct kontakt kon;
	int zamiana = 0;
	
	for (int i = 0; i < liczba_elementow-1; i++)
	{
		temp1 = *poczatek;
		temp2 = temp1->nastepny;
		for (int j = 0; j < liczba_elementow - i - 1; j++)
		{
			zamiana = czy_zamiana((temp1->Kontakt).nazwisko, (temp2->Kontakt).nazwisko);
			if (zamiana==1)
			{
				strcpy(kon.imie, (temp1->Kontakt).imie);
				strcpy(kon.nazwisko, (temp1->Kontakt).nazwisko);
				strcpy(kon.numer, (temp1->Kontakt).numer);
				strcpy(kon.grupa, (temp1->Kontakt).grupa);
				strcpy((temp1->Kontakt).imie, (temp2->Kontakt).imie);
				strcpy((temp1->Kontakt).nazwisko, (temp2->Kontakt).nazwisko);
				strcpy((temp1->Kontakt).numer, (temp2->Kontakt).numer);
				strcpy((temp1->Kontakt).grupa, (temp2->Kontakt).grupa);
				strcpy((temp2->Kontakt).imie, kon.imie);
				strcpy((temp2->Kontakt).nazwisko, kon.nazwisko);
				strcpy((temp2->Kontakt).numer, kon.numer);
				strcpy((temp2->Kontakt).grupa, kon.grupa);
			}
			temp1 = temp1->nastepny;
			temp2 = temp2->nastepny;
		}
	}
}
void dodaj_kontakt(struct element** poczatek, struct element** koniec, int liczba_ele)
{
	struct kontakt bufor;
	struct element* nowy;
	char znak='0';
	nowy = (struct element*)malloc(sizeof(struct element));
	struct element* temp;
	struct element* temp2;
	temp = *poczatek;
	temp2 = *poczatek;
	printf("Podaj imie nowego kontaktu:");
	(void)scanf("%s", &bufor.imie);
	printf("Podaj nazwisko nowego kontaktu:");
	(void)scanf("%s", &bufor.nazwisko);
	printf("Podaj numer telefonu nowego kontaktu:");
	(void)scanf("%s", &bufor.numer);
	printf("Podaj grupe nowego kontaktu:");
	(void)scanf("%s", &bufor.grupa);
	strcpy((nowy->Kontakt).imie, bufor.imie);
	strcpy((nowy->Kontakt).nazwisko, bufor.nazwisko);
	strcpy((nowy->Kontakt).numer, bufor.numer);
	strcpy((nowy->Kontakt).grupa, bufor.grupa);
	while (czy_zamiana((temp->Kontakt).nazwisko, bufor.nazwisko)==0 && temp2!=*koniec)
	{
		temp = temp->nastepny;
		if (czy_zamiana((temp->Kontakt).nazwisko, bufor.nazwisko) == 0) temp2 = temp2->nastepny;
	}
	if (temp == *poczatek)
	{
		(*poczatek) = nowy;
		nowy->poprzedni = NULL;
		nowy->nastepny = temp;
		temp->poprzedni = nowy;
	}
	else if (temp2==*koniec)
	{
		nowy->poprzedni = koniec;
		temp2->nastepny = nowy;
		(*koniec) = nowy;
		nowy->nastepny = NULL;
	}
	else
	{
		nowy->poprzedni = temp2;
		nowy->nastepny = temp;
		temp->poprzedni = nowy;
		temp2->nastepny = nowy;
	}
}
void znajdz_kontakt_imie_naz(struct element* poczatek, int liczba_ele)
{
	char szukany[100];
	int i = 0;
	printf("Podaj ci¹g znakow bez spacji, aby wyszukac kontakty po imieniu/nazwisku:");
	(void)scanf("%s", szukany);
	for (i = 0; i < strlen(szukany); i++)
	{
		if (szukany[i] > 96 && szukany[i] < 123) szukany[i] = szukany[i] - 32;
	}
	char imie_tmp[100];
	char nazw_tmp[100];
	struct element* temp;
	temp = poczatek;
	while (temp != NULL) 
	{
		for (i = 0; i < strlen(temp->Kontakt.imie); i++) {
			if (temp->Kontakt.imie[i] > 96 && temp->Kontakt.imie[i] < 123) imie_tmp[i] = temp->Kontakt.imie[i] - 32;
			else imie_tmp[i] = temp->Kontakt.imie[i];
		}
		imie_tmp[i] = '\0';
		for (i = 0; i < strlen(temp->Kontakt.nazwisko); i++) {
			if (temp->Kontakt.nazwisko[i] > 96 && temp->Kontakt.nazwisko[i] < 123) nazw_tmp[i] = temp->Kontakt.nazwisko[i] - 32;
			else nazw_tmp[i] = temp->Kontakt.nazwisko[i];
		}
		nazw_tmp[i] = '\0';
		if (strstr(imie_tmp, szukany) != NULL || strstr(nazw_tmp, szukany) != NULL) {
			wypisz_kontakt(temp->Kontakt);
		}
		temp = temp->nastepny;
	}
}
void znajdz_kontakt_grupa(struct element* poczatek, int liczba_ele)
{
	char szukany[100];
	int i = 0;
	printf("Podaj ci¹g znakow bez spacji, aby wyszukac kontakty z grupa:");
	(void)scanf("%s", szukany);
	for (i = 0; i < strlen(szukany); i++)
	{
		if (szukany[i] > 96 && szukany[i] < 123) szukany[i] = szukany[i] - 32;
	}
	char grupa_tmp[100];
	struct element* temp;
	temp = poczatek;
	while (temp != NULL)
	{
		for (i = 0; i < strlen(temp->Kontakt.grupa); i++) {
			if (temp->Kontakt.grupa[i] > 96 && temp->Kontakt.grupa[i] < 123) grupa_tmp[i] = temp->Kontakt.grupa[i] - 32;
			else grupa_tmp[i] = temp->Kontakt.grupa[i];
		}
		grupa_tmp[i] = '\0';
		
		if (strstr(grupa_tmp, szukany) != NULL) {
			wypisz_kontakt(temp->Kontakt);
		}
		temp = temp->nastepny;
	}
}
void usun_kontakty(struct element** poczatek, struct element** koniec, int liczba_ele)
{
	char szukany[100];
	int i = 0;
	printf("Podaj ci¹g znakow bez spacji, aby wyszukac i usunac kontakty po imieniu/nazwisku:");
	(void)scanf("%s", szukany);
	for (i = 0; i < strlen(szukany); i++)
	{
		if (szukany[i] > 96 && szukany[i] < 123) szukany[i] = szukany[i] - 32;
	}
	char imie_tmp[100];
	char nazw_tmp[100];
	struct element* temp,*temp1,*temp2;
	int nakierowanie = 0;
	temp2=*poczatek;
	temp2 = temp2->nastepny;
	temp = *poczatek;
	temp1 = *poczatek;
	while (temp != NULL)
	{
		for (i = 0; i < strlen(temp->Kontakt.imie); i++) {
			if (temp->Kontakt.imie[i] > 96 && temp->Kontakt.imie[i] < 123) imie_tmp[i] = temp->Kontakt.imie[i] - 32;
			else imie_tmp[i] = temp->Kontakt.imie[i];
		}
		imie_tmp[i] = '\0';
		for (i = 0; i < strlen(temp->Kontakt.nazwisko); i++) {
			if (temp->Kontakt.nazwisko[i] > 96 && temp->Kontakt.nazwisko[i] < 123) nazw_tmp[i] = temp->Kontakt.nazwisko[i] - 32;
			else nazw_tmp[i] = temp->Kontakt.nazwisko[i];
		}
		nazw_tmp[i] = '\0';
		if (strstr(imie_tmp, szukany) != NULL || strstr(nazw_tmp, szukany) != NULL) {
			printf("Usunieto kontakt:\n");
			wypisz_kontakt(temp->Kontakt);
			if (temp == *poczatek)
			{
				(*poczatek) = temp->nastepny;
				temp2->poprzedni = NULL;
				free(temp);
				temp = (*poczatek);
				temp1 = (*poczatek);
				nakierowanie = 1;

			}
			else if (temp == *koniec)
			{
				(*koniec) = temp1;
				temp1->nastepny = NULL;
				free(temp);
				temp = NULL;
			}
			else
			{
				temp1->nastepny = temp2;
				temp2->poprzedni = temp1;
				temp2 = temp2->nastepny;
				free(temp);
				temp = temp1->nastepny;
			}
		}
		if(temp2!=(*koniec)) temp2 = temp2->nastepny;
		if (temp != NULL && !nakierowanie) temp = temp->nastepny;
		if (temp!=temp1->nastepny && temp->poprzedni!=NULL) temp1=temp->poprzedni;
		nakierowanie = 0;
	}
}
int main()
{
	setlocale(LC_ALL, "polish_poland");
	//setlocale(LC_ALL, "C");

	struct element* poczatek = NULL;
	struct element* koniec = NULL;
	int liczba_elementow;


	struct kontakt bufor;
	struct kontakt* wsk_na_bufor;
	wsk_na_bufor = &bufor;

	int choice = 0;
	int wyjscie = 0;
	printf("MENU\n");
	while (!wyjscie) {
		printf("1.Wczytaj kontakty z pliku\n2.Posortuj liste wedlug nazwiska\n3.Wyswietl liczbe elementow\n4.Dodaj kontakt przez terminal\n5.Wyswietl liste\n");
		printf("6.Znajdz kontakt po imieniu/nazwisku\n7.Znajdz kontakty nalezace do grupy\n8.Usun kontakty\n9.Zakoncz program\n");
		(void)scanf("%d", &choice);
		if (choice == 1) {
			wczytaj_z_pliku(&poczatek, &koniec);
		}
		else if (choice == 2) {
			liczba_elementow = countElements(poczatek);
			sortowanie_nazwisk(&poczatek, liczba_elementow);
		}
		else if (choice == 3) {
			if (!isEmpty(poczatek))
				printf("Liczba elementow na stosie: %d\n", countElements(poczatek));
		}
		else if (choice == 4) {
			liczba_elementow = countElements(poczatek);
			dodaj_kontakt(&poczatek, &koniec, liczba_elementow);
		}
		else if (choice == 5) {
			show(poczatek);
		}
		else if (choice == 6) {
			liczba_elementow = countElements(poczatek);
			znajdz_kontakt_imie_naz(poczatek, liczba_elementow);
		}
		else if (choice == 7) {
			liczba_elementow = countElements(poczatek);
			znajdz_kontakt_grupa(poczatek, liczba_elementow);
		}
		else if (choice == 8) {
			liczba_elementow = countElements(poczatek);
			usun_kontakty(&poczatek,&koniec,liczba_elementow);
		}
		else if (choice == 9) { // wyjscie
			wyjscie = 1;
		}
	}

	clear(&poczatek);
	return 0;
}
