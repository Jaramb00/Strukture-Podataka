#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 50



typedef struct _stablo Tree;
struct _stablo {
	char* ime;

	Tree* child;
	Tree* sibling;
};

typedef struct _stog Stog;
struct _stog {
	Tree* directory;

	Stog* next;
	Stog* prev;
};

int NapraviDir(Tree*);
int Menu(Tree*, Stog*);
int Dir(Tree*);
Tree* cd(Tree*, Stog*);
Tree* Back(Tree*, Stog*);
Tree* PronadiPoImenu(char*, Tree*);
int PushStog(Stog*, Tree*);
Tree* PopStog(Stog*);
int Linija(Stog*, Tree*, Tree*);
Stog* PronadiZadnji(Stog*);

int main()
{
	Tree* root;
	root = (Tree*)malloc(sizeof(Tree));
	root->child = NULL;
	root->sibling = NULL;
	Stog* head;
	head = (Stog*)malloc(sizeof(Stog));
	head->next = NULL;
	head->prev = NULL;
	int status = 0;
	root->ime = (char*)malloc(MAX * sizeof(char));
	

	do {
		status = Menu(root, head);
	} while (!status);

	return 0;
}

int Linija(Stog* head, Tree* root, Tree* currentFile)
{
	Stog* s;

	s = PronadiZadnji(head);

	printf("\n");
	if (head->next == NULL) {
		printf("%s>", root->ime);
		return 0;
	}

	while (s->prev != NULL) {
		printf("%s>", s->directory->ime);
		s = s->prev;
	}

	printf("%s>", currentFile->ime);

	return 0;
}

Stog* PronadiZadnji(Stog* head)
{
	Stog* s;
	s = head->next;

	if (s == NULL) {
		return NULL;
	}

	while (s->next != NULL) {
		s = s->next;
	}

	return s;
}

int Menu(Tree* root, Stog* head) {
	Tree* CurrentFile = root;
	char command[MAX] = { 0 };

	printf("******************************************\n");
	printf("------------------MENU------------------\n\n");
	printf("   md <imedatoteke> - Dodaj novi direktorij\n");
	printf("   cd <imedatoteke> - Otvori direktorij\n");
	printf("   cd.. - Zatvoriti direktorij\n");
	printf("   dir - Ispisi listu direktorija u trenutnome direktoriju\n");
	printf("   refresh - Ponovo ispisi izbornik\n");
	printf("   exit - Izlaz\n\n");
	printf("******************************************\n\n");

	while (1) {

		

		Linija(head, root, CurrentFile);
		scanf("%s", command);

		if (!strcmp(command, "md")) {
			NapraviDir(CurrentFile);
		}

		else if (!strcmp(command, "cd")) {
			CurrentFile = cd(CurrentFile, head);
		}

		else if (!strcmp(command, "cd..")) {
			CurrentFile = Back(CurrentFile, head);
		}

		else if (!strcmp(command, "dir")) {
			Dir(CurrentFile);
		}

		else if (!strcmp(command, "exit")) {
			return 1;
		}

		else if (!strcmp(command, "refresh")) {
			return 0;
		}

		else
			printf("Naredba nije pronadena!\n");
	}

	return 0;
}

int NapraviDir(Tree* currentFile) {
	Tree* directory;
	directory = (Tree*)malloc(sizeof(Tree));
	directory->ime = (char*)malloc(MAX * sizeof(char));

	if (!directory)
		printf("Memorija nije uspjesno alocirana");

	if (currentFile->child != NULL) {
		currentFile = currentFile->child;
		while (currentFile->sibling != NULL) {
			currentFile = currentFile->sibling;
		}
		currentFile->sibling = directory;
	}

	else
		currentFile->child = directory;


	scanf(" %s", directory->ime);

	directory->sibling = NULL;
	directory->child = NULL;

	return 0;
}

int Dir(Tree* currentFile) {
	if (currentFile->child == NULL) {
		printf("Prazan direktorij!\n");
		return 0;
	}

	currentFile = currentFile->child;

	printf("DIRECTORIES: \n");
	printf("\t- %s\n", currentFile->ime);

	while (currentFile->sibling != NULL) {
		printf("\t- %s\n", currentFile->sibling->ime);
		currentFile = currentFile->sibling;
	}

	return 0;
}

Tree* PronadiPoImenu(char* name, Tree* currentFile) {
	if (currentFile->child == NULL) {
		printf("Direktorij je prazan!");
		return 0;
	}

	currentFile = currentFile->child;

	while (strcmp(name, currentFile->ime) != 0 && currentFile->sibling != NULL) {
		currentFile = currentFile->sibling;
	}

	if (currentFile->sibling == NULL) {
		if (strcmp(name, currentFile->ime) != 0)
			return 0;
		else
			return currentFile;
	}

	else
		return currentFile;
}

int PushStog(Stog* head, Tree* directory) {
	Stog* q = (Stog*)malloc(sizeof(Stog));

	q->next = head->next;
	q->prev = head;
	if (head->next != NULL) {
		head->next->prev = q;
	}
	head->next = q;
	q->directory = directory;

	return 0;
}

Tree* PopStog(Stog* head) {
	Stog* q = (Stog*)malloc(sizeof(Stog));
	Tree* p;

	if (head->next == NULL)
		return NULL;

	q = head->next;
	p = q->directory;
	head->next = head->next->next;
	if (head->next != NULL)
		head->next->prev = head;
	free(q);

	return p;
}

Tree* Back(Tree* currentFile, Stog* head)
{
	Tree* SearchedFile;

	SearchedFile = PopStog(head);

	if (SearchedFile == NULL) {
		printf("Ne moze se izaci iz root direktorija!\n");
		SearchedFile = currentFile;
	}

	return SearchedFile;
}

Tree* cd(Tree* currentFile, Stog* head)
{
	Tree* SearchedFile;
	char* imeDir;
	imeDir = (char*)malloc(MAX * sizeof(char));

	scanf("%s", imeDir);

	if (currentFile->child == NULL) {
		printf("Nema direktorija koji mozete otvoriti!\n");
		return currentFile;
	}

	SearchedFile = PronadiPoImenu(imeDir, currentFile);
	if (SearchedFile == 0) {
		printf("Direktorij nije pronaden\n");
		return currentFile;
	}

	PushStog(head, currentFile);

	return SearchedFile;
}
