#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h> 
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include<ctype.h>
#define MAX_SIZE (50)

struct _lista;
typedef struct _lista* position;
typedef struct _lista
{
	int godinarodenja;
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	position next;			//pokazivač na sljedeći član liste
							//struct _lista* next;----position-isto sto i osoba*
}osoba;

//-----funkcije koje cemo koristiti
int Umetni(position p);
position PronadiPrethodni(position p, char*);
int DinUmetniNaPocetak(position head);
int IspisListe(position f);
position PronadiPoPrezimenu(position p, char* prezime); //--mozemo po imenu i godini isto
position PronadiPosljednji(position head);
int IzbrisiOdredeniElement(position p, char* BrisiOsobu); //---- po imenu,-prezimenu- ili godini rodenja
int DinUmetniNaKraj(position head);
void UnosPodataka(position p);
int DinUmetniNakonOdred(position p, char* prezime); // a) 
int DinUmetniPrijeOdred(position p, char* prezime); // b)
void Sort(position p); // c) sortiranje
void UcitajUDatoteku(position p); // d)
void ProcitajIzDatoteke(position p); // e)



int main() {


	char prezime_1[MAX_SIZE] = { 0 };
	char* IzabranoPrezime_1 = prezime_1;

	char prezime_2[MAX_SIZE] = { 0 };
	char* IzabranoPrezime_2 = prezime_2;

	char prezime_3[MAX_SIZE] = { 0 };
	char* IzabranoPrezime_3 = prezime_3;

	char brisanje[MAX_SIZE] = { 0 };
	char* BrisiOsobu = brisanje;


	position head = NULL;
	position IzabranaOsoba_1 = NULL;
	head = (position)malloc(sizeof(osoba));
	IzabranaOsoba_2 = (position)malloc(sizeof(osoba));
	IzabranaOsoba_1 = (position)malloc(sizeof(osoba));
	head->next = NULL;


	printf("Unesite osobu koju stavljate na pocetak liste:\n\n");
	DinUmetniNaPocetak(head);
	printf("\n");
	IspisListe(head->next);
	printf("\nUnesite osobu koju stavljate na kraj liste:\n\n");
	DinUmetniNaKraj(head);
	printf("IZGLED LISTE:\n");
	IspisListe(head->next);

	printf("\nUnesite prezime koje trazite:\n");      //TRAZENJE
	scanf(" %s", IzabranoPrezime_1);

	IzabranaOsoba_1 = PronadiPoPrezimenu(head->next, IzabranoPrezime_1);

	printf("\nIME: %s\nPREZIME: %s\nGODINA RODENJA: %d\n\n", IzabranaOsoba_1->ime, IzabranaOsoba_1->prezime, IzabranaOsoba_1->godinarodenja);       //ISPIS

	printf("\nUnesite prezime osobe koju zelite obrisati:\n");            //BRISANJE
	scanf(" %s", BrisiOsobu);

	IzbrisiOdredeniElement(head->next, BrisiOsobu);

	printf("\nPROVJERA BRISANJA\n");
	printf("\nUnesite prezime koje ste izbrisali:\n");
	scanf(" %s", IzabranoPrezime_1);

	IzabranaOsoba_1 = PronadiPoPrezimenu(head->next, IzabranoPrezime_1);

	printf("Unesite osobu nakon koje zelite unijeti novu osobu: \n");
	scanf(" %s", IzabranoPrezime_2);

	DinUmetniNakonOdred(head->next,IzabranoPrezime_2);

	IspisListe(head->next);

	printf("Unesite prezime osobe prije koje zelite unijeti novu osobu: \n");
	scanf(" %s", IzabranoPrezime_3);

	DinUmetniPrijeOdred(head->next, IzabranoPrezime_3);

	IspisListe(head->next);
	printf("\n");

	Sort(head);
	IspisListe(head->next);

	UcitajUDatoteku(head);
	ProcitajIzDatoteke(head);

	return EXIT_SUCCESS;
}

int DinUmetniNaPocetak(position head) {

	Umetni(head);

	return EXIT_SUCCESS;
}

int Umetni(position p)
{
	position q = NULL;
	q = (position)malloc(sizeof(osoba)); //alociramo prostor za novi element
	if (q == NULL) {
		perror("Greska u alokaciji memorije!\n");
		return -1;
	}

	UnosPodataka(q); //unosi podatke u novi element
	q->next = p->next; //neka q pokazuje na ono na što je pokazivao head element
	p->next = q; //neka head element pokazuje na taj dodani element
	if (q == 0) {
		perror("Greska u unosu podataka!\n");
		return -1;
	}
	return EXIT_SUCCESS;
}

position PronadiPrethodni(position p, char* prezime)
{
	position prev = NULL, curr = NULL;
	prev = p;
	curr = prev->next;
	while (curr != NULL && strcmp(curr->prezime, prezime) != 0)
	{
		prev = curr;
		curr = prev->next;
	}
	if (curr == NULL) { //ako nije pronađen nijedan element
		printf("Nije pronaden takav element");
		return NULL;
	}
	return prev;
}
position PronadiPosljednji(position p)
{
	while (p->next != NULL) {
		p = p->next;

		return p;
	}
	return EXIT_SUCCESS;
}
int DinUmetniNaKraj(position head)
{
	position last = NULL;
	last = (position)malloc(sizeof(osoba));
	if (!last)
	{
		printf("Greska u alokaciji memorije\n");
		return -1;
	}
	last = PronadiPosljednji(head);
	if (last == NULL)
	{
		printf("Greska u pronalazenju posljednjeg\n");
		return -1;
	}

	Umetni(last);

	return EXIT_SUCCESS;
}

int IzbrisiOdredeniElement(position p, char* ObrisiOsobu)
{
	position prev = NULL;
	position curr = NULL;

	prev = PronadiPrethodni(p, ObrisiOsobu);

	if (prev == NULL)
		return -1;

	curr = prev->next;
	prev->next = prev->next->next;
	free(curr);

	return EXIT_SUCCESS;
}
position PronadiPoPrezimenu(position p, char* prezime)
{
	position temp = p;
	if (temp == NULL)
	{
		printf("Nije ucitana osoba");
	}
	while (temp != NULL && strcmp(temp->prezime, prezime) != NULL) {
		temp = temp->next;
	}
	if (temp == NULL) {

		printf("Takav element ne postoji\n");
	}
	return temp;
}
int IspisListe(position f)
{
	position temp = f;
	if (f == NULL)
	{
		printf("Nema elemenata, lista je prazna!\n");
		return -1;
	}
	else
	{
		while (temp != NULL)
		{
			printf("IME: %s\nPREZIME: %s\nGODINA RODENJA: %d\n", temp->ime, temp->prezime, temp->godinarodenja);
			temp = temp->next;
		}
	}
	return EXIT_SUCCESS;
}
void UnosPodataka(position p) {

	printf("Unesite ime osobe: ");
	scanf(" %s", p->ime);
	printf("Unesite prezime osobe: ");
	scanf(" %s", p->prezime);
	printf("Unesite godinu rodenja: ");
	scanf("%d", &(p->godinarodenja));


}
int DinUmetniNakonOdred(position p, char* prezime)
{
	position prev = NULL;
	prev = PronadiPoPrezimenu(p, prezime); 
		if (prev == NULL)
			return -1;
	Umetni(prev); 

	return EXIT_SUCCESS;
}
int DinUmetniPrijeOdred(position p, char* prezime)
{
	position prevp = NULL;
	prevp = PronadiPrethodni(p, prezime); 
	if (prevp == NULL) 
		return -1;

	Umetni(prevp); 

		return EXIT_SUCCESS;
}
void Sort(position p)
{
	position i, j, prosli_j, temp, end;

	end = NULL;

	i = p;

	while (i->next != end)
	{
		prosli_j = i;
		j = i->next;
		while (j->next != end)
		{
			if (strcmp(j->prezime, j->next->prezime) > 0)
			{
				temp = j->next;
				prosli_j->next = temp;
				j->next = temp->next;
				temp->next = j;

				j = temp;
			}

			prosli_j = j;
			j = j->next;
		}
		end = j;
	}

}
void UcitajUDatoteku(position p) //upisi u datoteku "w"
{
	
	FILE* datoteka;
	char ImeDatoteke[10];

	printf("\nUnesite ime datoteke u koju zelis spremiti listu: \n");

	scanf(" %s", ImeDatoteke);

	datoteka = fopen(ImeDatoteke, "w");

	if (NULL == datoteka)
		printf("\n Greska u otvaranju datoteke");
	else
	{
		while (p != NULL)
		{
			fprintf(datoteka, "\n %s %s %d", p->ime, p->prezime, p->godinarodenja);
			p = p->next;
		}

		fclose(datoteka);
	}
}
void ProcitajIzDatoteke(position p) // read "r"
{
	
	FILE* datoteka;
	char ImeDatoteke[10];
	position temp;

	printf("\nUnesite ime datoteke iz koje zelite procitati listu:");
	scanf(" %s", ImeDatoteke);

	datoteka = fopen(ImeDatoteke, "r");

	if (NULL == datoteka)
		printf("\n Ne postoji datoteke s tim imenom");
	else
	{
		while (feof(datoteka) == 0)
		{
			temp = (position)malloc(sizeof(osoba));

			fscanf(datoteka, " %s %s %d", temp->ime, temp->prezime, &temp->godinarodenja);

			temp->next = p->next;
			p->next = temp;
			p = temp;
		}


	}

		fclose(datoteka);
	
}
