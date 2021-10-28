 #define _CRT_SECURE_NO_WARNINGS

#include<stdio.h> 
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#define MAX_SIZE (50)

struct _lista;
typedef struct _lista* position;
typedef struct _lista
{
	int godinarodenja;
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE]; 
	position next;  //pokazivač na sljedeći član liste
                    //struct _lista* next;----position-isto sto i osoba *
}osoba;

                    //-----funkcije koje cemo koristiti
int Umetni(position p);
position PronadiPrethodni(position p,char*);
int DinUmetniNaPocetak(position head);
int IspisListe(position f);
position PronadiPoPrezimenu(position p,char* prezime); //--mozemo po imenu i godini isto
position PronadiPosljednji(position head);
int IzbrisiOdredeniElement(position p,char* BrisiOsobu); //---- po imenu,-prezimenu- ili godini rodenja
int DinUmetniNaKraj(position head);
void UnosPodataka(position p);


int main() {
    
    int i;
    
	char prezime[MAX_SIZE]={0};
	char* IzabranoPrezime = prezime;
	
	char brisanje[MAX_SIZE]={0};
	char* BrisiOsobu = brisanje;

    
	position head = NULL;
	position IzabranaOsoba = NULL;
	head = (position)malloc(sizeof(osoba));
	IzabranaOsoba = (position)malloc(sizeof(osoba));
	head->next = NULL;

	printf("Unesite osobu koju stavljate na pocetak liste:\n\n");
	DinUmetniNaPocetak(head);
	printf("\n");
	IspisListe(head->next);
	printf("\nUnesite osobu koju stavljate na kraj liste:\n\n");
	for(i=0;i<3;i++)
	DinUmetniNaKraj(head);
	printf("IZGLED LISTE:\n");
	IspisListe(head->next);

	printf("\nUnesite prezime koje trazite:\n");      //TRAZENJE
	scanf(" %s", IzabranoPrezime);

	IzabranaOsoba = PronadiPoPrezimenu(head->next,IzabranoPrezime);

	printf("\nIME: %s\nPREZIME: %s\nGODINA RODENJA: %d\n\n", IzabranaOsoba->ime, IzabranaOsoba->prezime, IzabranaOsoba->godinarodenja);       //ISPIS

	printf("\nUnesite prezime osobe koju zelite obrisati:\n");            //BRISANJE
	scanf(" %s", BrisiOsobu);

	IzbrisiOdredeniElement(head->next, BrisiOsobu);

	printf("\nPROVJERA BRISANJA\n");                    
	printf("\nUnesite prezime koje ste izbrisali:\n");
	scanf(" %s", IzabranoPrezime);

	IzabranaOsoba = PronadiPoPrezimenu(head->next, IzabranoPrezime);


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
