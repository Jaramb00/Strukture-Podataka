#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#define MAXs 128
#define MAXL 1024

typedef struct _student{
	char ime[MAXs];
	char prezime[MAXs];
	double bodovi;
}student;

int BrojStudenata(char*); //funkcija za brojanje redaka to jest studenata(vraca broj)
double relativan_brojbodova(double, double); //uzima regularne dijeli ih s maksimalnim i vraca relativni broj

//u mainu...
int main() {
	
	int n=0;
	int i;
	double max_bodovi;
	double rel_bodo=0;
	student* s=NULL;
	char* datoteka = NULL;

	scanf(" %s", &datoteka);

	FILE* f = NULL;
	f = fopen(datoteka, "r");

	n = BrojStudenata(datoteka);
	s = (student*)malloc(n * sizeof(student));

	
	for (i = 0; i < n; i++) {

		fscanf(f, "%s %s %lf", s[i].ime, s[i].prezime, &s[i].bodovi);

	}
	max_bodovi = 0;
	for (i = 0; i < n; i++)   {

		if (s[i].bodovi >= max_bodovi){

			max_bodovi = s[i].bodovi;
		}
	}
	for (i = 0; i < n; i++)
	{
		rel_bodo = relativan_brojbodova(s[i].bodovi, max_bodovi);// (x/y)*100
		printf("\n%-25s %-25s %-25.2lf %-25.2lf ", s[i].ime, s[i].prezime, s[i].bodovi, rel_bodo);
	}
	fclose(f);
	printf("\n\n");
	return 0;
}

	int BrojStudenata(char* datoteka) {

		int brojac = 0;
		FILE* f = NULL;
		char buffer[MAXL] = { 0 }; //inic 

		f = fopen(datoteka, "r");

		if (!f) {
			printf("Greska pri otvaranju datoteke\n");
			return -1;
		}

		while (!feof(f)) {
			fgets(buffer, MAXL, f);
			brojac++;
		}

		fclose(f);
		return brojac;
	}

	double relativan_brojbodova(double x, double y) {

		double rel_bod = 0.0;
		rel_bod = (x / y) * 100;
		return rel_bod;
	}