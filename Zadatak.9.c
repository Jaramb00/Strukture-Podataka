#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX_SIZE 128
#define MAX_LINE 1024
#define Down_l 10
#define Up_l 90

struct _cvor;
typedef struct _cvor* Position;
typedef struct _cvor
{
	int number;
	Position left;
	Position right;
}cvor;

struct _Stack;
typedef struct _Stack* s_position;
typedef struct _Stack
{
	int element;
	s_position next;

}stog;

Position Insert(Position curr, Position novi);
Position Create_new(int num, Position curr);
int Print_inorder(Position curr);
int Replace(Position curr);
int Delete(Position curr);
int Pop_stog(s_position head);
int Push_stog(s_position head, int element);
int Add_on_stog(s_position head, Position curr);
int Add_on_file(s_position head, Position root, char* name);

int main()
{
	Position root = NULL;
	srand((unsigned)time(NULL));
	int i = 0, n;
	stog head;
	head.element = 0;
	head.next = NULL;
	char name[MAX_SIZE] = { 0 };

	printf("Upisite ime file-a: ");
	scanf(" %s", name);

	int niz[10] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };

	for (i = 0; i < 10; i++)
	{
		root = Create_new(niz[i], root);
	}

	Print_inorder(root);
	printf("\n");

	Add_on_stog(&head, root);
	Add_on_file(&head, root, name);

	Replace(root);

	Print_inorder(root);
	printf("\n");

	Add_on_stog(&head, root);
	Add_on_file(&head, root, name);

	Delete(root);

	root = NULL;
	printf("\nBroj clanova: ");
	scanf(" %d", &n);

	for (i = 0; i < n; i++)
	{
		root = Create_new((rand() % (Up_l - Down_l - 1) + Down_l + 1), root);
	}

	Print_inorder(root);

	return 0;
}
Position Insert(Position curr, Position novi)
{
	if (NULL == curr)
	{
		return novi;
	}
	else if (novi->number < curr->number)
	{
		curr->right = Insert(curr->right, novi);
	}
	else
	{
		curr->left = Insert(curr->left, novi);
	}

	return curr;
}
Position Create_new(int num, Position curr)
{
	Position novi = NULL;

	novi = (Position)malloc(sizeof(cvor));

	if (!novi)
	{
		printf("Pogreska u alociranju!");
		return NULL;
	}

	novi->number = num;
	novi->left = NULL;
	novi->right = NULL;

	novi = Insert(curr, novi);

	return novi;
}
int Print_inorder(Position curr)
{
	if (!curr)
	{
		return 0;
	}

	Print_inorder(curr->left);
	printf("%d ", curr->number);
	Print_inorder(curr->right);

	return 0;
}
int Replace(Position curr)
{
	int sum = 0;
	int temp = 0;

	if (NULL != curr)
	{
		sum = Replace(curr->left);
		sum += Replace(curr->right);

		temp = curr->number;
		curr->number = sum;
		sum += temp;
	}
	return sum;

}
int Delete(Position curr)
{
	if (curr == NULL)
	{
		return 0;
	}

	Delete(curr->left);
	Delete(curr->right);

	free(curr);

	return 0;
}
int Pop_stog(s_position head)
{
	if (!head->next)
	{
		return 0;
	}

	s_position toDelete = head->next;
	head->next = toDelete->next;

	free(toDelete);

	return 0;
}
int Push_stog(s_position head, int element)
{
	s_position novi = NULL;

	novi = (s_position)malloc(sizeof(stog));

	if (!novi)
	{
		perror("Pogreska u alociranju!\n");
		return -1;
	}

	novi->element = element;
	novi->next = head->next;
	head->next = novi;

	return 0;
}
int Add_on_stog(s_position head, Position curr)
{
	if (NULL == curr)
	{
		return 0;
	}

	Add_on_stog(head, curr->right);

	Push_stog(head, curr->number);

	Add_on_stog(head, curr->left);


	return 0;
}
int Add_on_file(s_position head, Position root, char* ime)
{
	FILE* fp = NULL;

	fp = fopen(ime, "imedat");

	if (!fp)
	{
		perror("Pogreska u otvaranju!\n");
		return -1;
	}

	while (head->next)
	{
		fprintf(fp, "%d ", head->next->element);
		Pop_stog(head);
	}

	fprintf(fp, "\n");

	fclose(fp);

	return 0;
}

