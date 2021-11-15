#define CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

#define MaxDeg 10

struct Polynomial;

typedef struct Polynomial* Pol;

struct Polynomial
{
	int Koeficijent;
	int Exponent;
	Pol Next;
};


void ProcitajPolinomeIzdatoteke(Pol, char*);
void Ispis(Pol);
void ZbrojiPolinome(Pol, Pol, Pol);
void MnoziPolinome(Pol, Pol, Pol);


void main()
{
	struct Polynomial P1, P2, S, P;

	P1.Next = NULL;
	P2.Next = NULL;
	S.Next = NULL;
	P.Next = NULL;

	ProcitajPolinomeIzdatoteke(&P1, "Polinom_1.txt");
	Ispis(&P1);

	ProcitajPolinomeIzdatoteke(&P2, "Polinom_2.txt");
	Ispis(&P2);


	ZbrojiPolinome(P1.Next, P2.Next, &S);
	printf("\n\nSuma je:");
	Ispis(&S);

	MnoziPolinome(P1.Next, P2.Next, &P);
	printf("\n\nProdukt je:");
	Ispis(&P);

	printf("\n");
}


void ProcitajPolinomeIzdatoteke(Pol P, char* ime_dat)
{
	FILE* dat;
	Pol q, temp, prev;

	dat = fopen(ime_dat, "r");
	if (NULL == dat)
	{
		printf("Greska u otvaranju datoteke!!!");
		exit(1);
	}
	else
	{
		while (0 == feof(dat))
		{
			q = (Pol)malloc(sizeof(struct Polynomial));

			fscanf(dat, " %d %d", &q->Koeficijent, &q->Exponent);

			temp = P->Next;
			prev = P;
			while (temp != NULL && temp->Exponent > q->Exponent)
			{
				prev = temp;
				temp = temp->Next;
			}

			prev->Next = q;

			if (temp != NULL)
				q->Next = temp;
			else
				q->Next = NULL;
		}
	}


}

void Ispis(Pol P)
{

	printf("\n");

	P = P->Next;

	while (P != NULL)
	{
		if (P->Koeficijent > 0)
			printf("\t+%d*x^%d", P->Koeficijent, P->Exponent);
		else
			printf("\t%d*x^%d", P->Koeficijent, P->Exponent);
		P = P->Next;
	}


	printf("\n");

}

void ZbrojiPolinome(Pol P1, Pol P2, Pol S)
{
	Pol q, temp;

	while (P1 != NULL && P2 != NULL)
	{
		q = (Pol)malloc(sizeof(struct Polynomial));
		q->Next = NULL;


		if (P1->Exponent > P2->Exponent)
		{
			q->Exponent = P1->Exponent;
			q->Koeficijent = P1->Koeficijent;
			P1 = P1->Next;
		}
		else if (P1->Exponent < P2->Exponent)
		{
			q->Exponent = P2->Exponent;
			q->Koeficijent = P2->Koeficijent;
			P2 = P2->Next;
		}
		else  // P1->Exp == P2->Exp
		{
			q->Exponent = P1->Exponent;
			q->Koeficijent = P1->Koeficijent + P2->Koeficijent;
			P1 = P1->Next;
			P2 = P2->Next;
		}
		S->Next = q;
		S = q;
	}

	if (P1 != NULL)
		temp = P1;
	else
		temp = P2;

	while (temp != NULL)
	{
		q = (Pol)malloc(sizeof(struct Polynomial));
		q->Next = NULL;
		q->Exponent = temp->Exponent;
		q->Koeficijent = temp->Koeficijent;
		S->Next = q;
		S = q;
		temp = temp->Next;
	}

}


void MnoziPolinome(Pol P1, Pol P2, Pol P)
{
	Pol q, first = P1, second = P2, temp, prev;
	int n;

	while (first != NULL)
	{
		second = P2;
		while (second != NULL)
		{
			temp = P->Next;
			prev = P;

			n = first->Exponent + second->Exponent;

			while (temp != NULL && temp->Exponent > n)
			{
				prev = temp;
				temp = temp->Next;
			}

			if (temp != NULL && temp->Exponent == n)
				temp->Koeficijent += first->Koeficijent * second->Koeficijent;
			else
			{
				q = (Pol)malloc(sizeof(struct Polynomial));

				q->Exponent = n;
				q->Koeficijent = first->Koeficijent * second->Koeficijent;

				prev->Next = q;
				q->Next = temp;
			}

			second = second->Next;
		}
		first = first->Next;
	}

	while (P->Next != NULL)
	{
		if (P->Next->Koeficijent == 0)
		{
			temp = P->Next;
			P->Next = P->Next->Next;
			free(temp);
		}
		P = P->Next;
	}

}
