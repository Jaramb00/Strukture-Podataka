#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<malloc.h>

#define MAX 1024

struct _stog {
	float element;
	struct _stog* next;
};

typedef struct _stog Stog;
typedef struct _stog* Pozicija;

int ProcitajIzDatoteke(Pozicija);
Pozicija Push(Pozicija, float);
float Pop(Pozicija);
int Izracunaj(Pozicija, char);

int main()
{
	Pozicija head;
	head = (Pozicija)malloc(sizeof(Stog));
	head->next = NULL;

	ProcitajIzDatoteke(head);
	printf("\n%f", head->next->element);

	return EXIT_SUCCESS;
}

Pozicija Push(Pozicija head, float broj)
{
	Pozicija q;
	q = (Pozicija)malloc(sizeof(Stog));

	q->next = head->next;
	head->next = q;
	q->element = broj;

	return q;
}

float Pop(Pozicija head)
{
	float broj = 0.0;
	Pozicija temp;
	temp = head->next;

	broj = temp->element;
	head->next = temp->next;
	free(temp);

	return broj;
}

int ProcitajIzDatoteke(Pozicija head)
{
	char* ime_dat;
	char buffer[MAX];
	char* pokbuf = buffer;
	ime_dat = (char*)malloc(sizeof(char) * MAX);

	printf("\nKako se zove datoteka iz koje citate izraz?\n");
	scanf("%s", ime_dat);
	if (strchr(ime_dat, '.') == NULL)
		strcat(ime_dat, ".txt");

	FILE* fp = NULL;
	fp = fopen(ime_dat, "r");

	if (fp == NULL) {
		printf("Greska u otvaranju datoteke!\n");
	}

	fgets(buffer, MAX, fp);

	fclose(fp);

	while (strlen(pokbuf) > 0) {
		char operacija = 0;
		float broj = 0;
		int pomak = 0;

		if (sscanf(pokbuf, " %f%n", &broj, &pomak) == 1) {
			Push(head, broj);
			pokbuf += pomak;
		}
		else {
			sscanf(pokbuf, " %c%n", &operacija, &pomak);
			Izracunaj(head, operacija);
			pokbuf += pomak;
		}
	}

	return EXIT_SUCCESS;
}

int Izracunaj(Pozicija head, char operacija)
{
	float br1;
	float br2;

	switch (operacija) {
	case '+':
		br1 = Pop(head);
		br2 = Pop(head);
		Push(head, br1 + br2);
		break;

	case '-':
		br1 = Pop(head);
		br2 = Pop(head);
		Push(head, br2 - br1);
		break;

	case '*':
		br1 = Pop(head);
		br2 = Pop(head);
		Push(head, br2 * br1);
		break;

	case '/':
		br1 = Pop(head);
		br2 = Pop(head);
		if (br1 == 0)
			printf("\nDijeljenje s 0 nije dozvoljeno!");
		else
			Push(head, br2 / br1);
		break;
	}

	return EXIT_SUCCESS;
}
