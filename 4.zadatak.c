#define CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

#define MAX 10

struct Polinom
{
	int Koeficijent[MAX + 1];
	int Exp;
};

typedef struct Polinom* Pos;

void NultiPolinom(Pos Poly);
void ProcitajIzDatoteke(Pos, char*);
void Ispis(struct Polinom);
void ZbrojiPolinome(Pos, Pos, Pos);
void MnoziPolinome(Pos, Pos, Pos);

int Max(int, int);


void main()
{
	struct Polinom P1, P2, S, P;

	NultiPolinom(&P1);
	ProcitajIzDatoteke(&P1, "Polinom_1.txt");
	Ispis(P1);

	NultiPolinom(&P2);
	ProcitajIzDatoteke(&P2, "Polinom_2.txt");
	Ispis(P2);



	NultiPolinom(&S);
	ZbrojiPolinome(&P1, &P2, &S);
	printf("\n\nSuma je:");
	Ispis(S);

	NultiPolinom(&P);
	MnoziPolinome(&P1, &P2, &P);
	printf("\n\nProdukt je:");
	Ispis(P);

	printf("\n");
}

void NultiPolinom(Pos Poly)
{
	int i;

	for (i = 0; i <= MAX; i++)
		Poly->Koeficijent[i] = 0;

	Poly->Exp = 0;
}

void ProcitajIzDatoteke(Pos P, char* ime_dat)
{
	FILE* dat;
	int i;

	dat = fopen(ime_dat, "r");
	if (NULL == dat)
	{
		printf("Greska u otvaranju datoteke!!!");
		exit(1);
	}
	else
	{
		i = 0;
		while (i <= MAX && 0 == feof(dat))
		{
			fscanf(dat, " %d", &P->Koeficijent[i]);
			i++;
		}
	}

	i = MAX;
	while (P->Koeficijent[i] == 0 && i != 0)
		i--;

	P->Exp = i;
	
	fclose(dat);
}

void Ispis(struct Polinom P)
{
	int i;

	printf("\n");

	for (i = P.Exp; i >= 0; i--)
		if (P.Koeficijent[i] > 0)
			printf("\t +%d*x^%d", P.Koeficijent[i], i);
		else if (P.Koeficijent[i] < 0)
			printf("\t %d*x^%d", P.Koeficijent[i], i);

	printf("\n");
}

void ZbrojiPolinome(Pos P1, Pos P2, Pos S)
{
	int i;

	S->Exp = Max(P1->Exp, P2->Exp);

	for (i = S->Exp; i >= 0; i--)
		S->Koeficijent[i] = P1->Koeficijent[i] + P2->Koeficijent[i];

}

int Max(int x, int y)
{
	if (x > y)
		return x;
	else
		return y;

}

void MnoziPolinome(Pos P1, Pos P2, Pos P)
{
	int i, j;

	P->Exp = P1->Exp + P2->Exp;

	if (P->Exp > MAX)
		printf("Produkt je nemoguce izracunati zbog prevelike dimenzije!");
	else
		for (i = P1->Exp; i >= 0; i--)
			for (j = P2->Exp; j >= 0; j--)
				P->Koeficijent[i + j] = P->Koeficijent[i + j] + P1->Koeficijent[i] * P2->Koeficijent[j];

}
