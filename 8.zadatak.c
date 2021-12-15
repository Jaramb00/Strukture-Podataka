#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

struct _stablo;
typedef struct _stablo* Pozicija;
typedef struct _stablo
{
	int br;
	Pozicija left;
	Pozicija right;

}tree;

Pozicija UnesiNoviElement(int element, Pozicija root);
Pozicija StvoriNoviElement(int element);
int PrintInOrder(Pozicija root);
int PrintPreOrder(Pozicija root);
int PrintPostOrder(Pozicija root);
int PrintLevelOrder(Pozicija root);
int PrintCurrentLevel(Pozicija root, int level);
int TreeDepth(Pozicija current);
Pozicija PronadiEl(int element, Pozicija root);
Pozicija PronadiMin(Pozicija root);
Pozicija IzbrisiEl(int element, Pozicija root);



int main(int argc, char** argv)
{

	Pozicija root = NULL;
	Pozicija temp = NULL;

	int input = 0;
	int element = 0;

	printf("**********************\n");
	printf("---------MENU---------\n\n");
	printf("Izaberi komandu: \n");
	printf("  1 - Unesi Element\n");
	printf("  2 - Ispisi In Order\n");
	printf("  3 - Ispisi Pre Order\n");
	printf("  4 - Ispisi Post Order\n");
	printf("  5 - Pronadi Element\n");
	printf("  6 - Izbrisi Element\n");
	printf("  0 - Exit\n");
	



	scanf("%d", &input);

	while (input != 0) {

		switch (input)
		{
		case 1:
			printf("Koji element zelis unijeti: ");
			scanf("%d", &element);
			root = UnesiNoviElement(element, root);
			break;
		case 2:
			PrintInOrder(root);
			break;
		case 3:
			PrintPreOrder(root);
			break;
		case 4:
			PrintPostOrder(root);
			break;
		case 5:
			printf("Koji element zelis naci: ");
			scanf("%d", &element);
			temp = PronadiEl(element, root);
			if (!temp) {
				printf("Element nije naden\n");
			}
			else {
				printf("Element je naden\n");
			}
			break;
		case 6:
			printf("Koji element zelis izbrisati: ");
			scanf("%d", &element);
			
			root = IzbrisiEl(element, root);
		case 0:
			break;
		default:
			printf("Pogresan input!\n");
		}


		printf("Izaberi komandu: \n");
		printf("  1 - Unesi Element\n");
		printf("  2 - Ispisi In Order\n");
		printf("  3 - Ispisi Pre Order\n");
		printf("  4 - Ispisi Post Order\n");
		printf("  5 - Pronadi Element\n");
		printf("  6 - Izbrisi Element\n");
		printf("  0 - Exit\n");



		scanf("%d", &input);

	}





	return EXIT_SUCCESS;
}


Pozicija UnesiNoviElement(int element, Pozicija root)
{
	Pozicija current = NULL;
	current = root;
	Pozicija newEl = NULL;

	if (current == NULL)
	{
		newEl = StvoriNoviElement(element);
		return newEl;
	}
	else if (element < current->br)
		current->left = UnesiNoviElement(element, current->left);
	else if (element > current->br)
		current->right = UnesiNoviElement(element, current->right);
	else
		free(newEl);

	return current;


}

Pozicija StvoriNoviElement(int element)
{
	Pozicija newEl = NULL;
	newEl = (Pozicija)malloc(sizeof(tree));
	if (!newEl)
	{
		perror("Can't allocate memory!");
		return NULL;
	}

	newEl->br = element;
	newEl->left = NULL;
	newEl->right = NULL;

	return newEl;

}

int PrintInOrder(Pozicija root)
{
	Pozicija current = NULL;
	current = root;

	if (current != NULL)
	{
		PrintInOrder(current->left);
		printf("%d ", current->br);
		PrintInOrder(current->right);
	}

	return EXIT_SUCCESS;
}

int PrintPreOrder(Pozicija root)
{
	Pozicija current = NULL;
	current = root;

	if (current != NULL)
	{
		printf("%d ", current->br);
		PrintInOrder(current->left);
		PrintInOrder(current->right);
	}

	return EXIT_SUCCESS;
}




int PrintPostOrder(Pozicija root)
{
	Pozicija current = NULL;
	current = root;

	if (current != NULL)
	{
		PrintInOrder(current->left);
		PrintInOrder(current->right);
		printf("%d ", current->br);
	}

	return EXIT_SUCCESS;
}

int PrintLevelOrder(Pozicija root)
{
	int h = TreeDepth(root);
	int i = 1;
	while (i <= h)
	{
		PrintCurrentLevel(root, i);
		i++;
	}

	return EXIT_SUCCESS;
}


int PrintCurrentLevel(Pozicija root, int level)
{
	Pozicija current = NULL;
	current = root;

	if (root == NULL)
		return EXIT_SUCCESS;
	if (level == 1)
		printf("%d ", root->br);
	else if (level > 1) {
		PrintCurrentLevel(root->left, level - 1);
		PrintCurrentLevel(root->right, level - 1);
	}
}

int TreeDepth(Pozicija current)
{
	int LeftH = 0;
	int RightH = 0;

	if (current == NULL)
		return 0;
	else {
		LeftH = TreeDepth(current->left);
		RightH = LeftH = TreeDepth(current->left);
		(current->right);

		if (LeftH > RightH)
			return (LeftH + 1);
		else
			return (RightH + 1);
	}

	return EXIT_SUCCESS;
}

Pozicija PronadiEl(int element, Pozicija root)
{
	Pozicija current = NULL;
	current = root;

	if (current == NULL)
	{
		return NULL;
	}
	else if (element < current->br)
		return PronadiEl(element, current->left);

	else if (element > current->br)
		return PronadiEl(element, current->right);
	else
		return current;

}

Pozicija PronadiMin(Pozicija root)
{

	Pozicija current = NULL;
	current = root;

	while (current->left != NULL) {
		current = current->left;
	}

	return current;
}

Pozicija IzbrisiEl(int element, Pozicija root)
{
	Pozicija temp = NULL;
	Pozicija current = NULL;
	current = root;

	if (current == NULL)
		printf("Elementa nema unutar stabla!\n");

	else if (current->br > element)
		current->left = IzbrisiEl(element, current->left);

	else if (current->br < element)
		current->right = IzbrisiEl(element, current->right);

	else if (current->left != NULL && current->right != NULL) {

		temp = PronadiMin(current->right);
		current->br = temp->br;
		current->right = IzbrisiEl(current->br, current->right);
	}

	else {

		temp = current;

		if (current->left == NULL)
			current = current->right;

		else
			current = current->left;

		free(temp);
	}

	return current;
}
