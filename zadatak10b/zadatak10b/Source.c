#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX (60)

struct _list;
typedef struct _list* LPosition;
typedef struct _list
{
	char city[MAX];
	int population;
	LPosition next;
}list;

struct _tree;
typedef struct _tree* TPosition;
typedef struct _tree
{
	char country[MAX];
	LPosition ListHead;
	TPosition Left;
	TPosition Right;
}tree;


TPosition CreateTreeElement(TPosition root);
TPosition ReadCountryFromFile(TPosition root, char* FileName);
TPosition InsertInTree(TPosition root, char* CountryName);
TPosition FindCountry(TPosition root, char* CountryName);
int PrintInOrder(TPosition root);
int CreateListElement(LPosition Head, char* CityName, int pop);
LPosition ReadCityFromFile(LPosition Head, char* FileName);
int PrintList(LPosition Head);
LPosition CreateList(LPosition Head);
int PrintResult(LPosition Head, int num);


int main()
{
	TPosition root = NULL, current = NULL;
	char file[MAX] = "datoteka.txt", CountryName[MAX] = { 0 };
	int num = 0;

	root = CreateTreeElement(root);

	strcpy(root->country, "Countries:");

	root = ReadCountryFromFile(root, file);

	PrintInOrder(root);


	printf("\nChoose a country\n");

	scanf(" %s", CountryName);
	strcat(CountryName, ".txt");
	current = FindCountry(root, CountryName);
	if (current == NULL)
	{
		printf("There is no such a country in this file!");
		return -1;;
	}
	printf("\nEnter a number of population:");
	scanf("%d", &num);
	PrintResult(current->ListHead, num);




	return EXIT_SUCCESS;
}
LPosition CreateList(LPosition Head)
{
	Head = (LPosition)malloc(sizeof(list));
	if (Head == NULL) {
		perror("Can't allocate memory!");
		return NULL;
	}

	strcpy(Head->city, "");
	Head->population = 0;
	Head->next = NULL;

	return Head;
}

TPosition CreateTreeElement(TPosition root)
{
	root = (TPosition)malloc(sizeof(tree));

	if (root == NULL)
	{
		perror("Can't allocate memory!");
		return -1;
	}

	root->Left = NULL;
	root->Right = NULL;
	root->ListHead = NULL;
	strcpy(root->country, "");

	return root;
}
TPosition ReadCountryFromFile(TPosition Head, char* FileName)
{
	FILE* fp = NULL;
	char cnt[MAX] = { 0 };

	fp = fopen(FileName, "r");
	if (fp == NULL)
	{
		printf("Error opening file!\n");
		return -1;
	}

	while (!feof(fp))
	{
		fscanf(fp, "%s \n", cnt);
		Head = InsertInTree(Head, cnt);
	}

	fclose(fp);
	return Head;
}
TPosition InsertInTree(TPosition root, char* CountryName)
{
	if (root == NULL)
	{
		root = CreateTreeElement(root);
		strcpy(root->country, CountryName);
		root->ListHead = NULL;
		root->ListHead = ReadCityFromFile(root->ListHead, CountryName);
	}
	else if (strcmp(root->country, CountryName) > 0)
		root->Left = InsertInTree(root->Left, CountryName);
	else if (strcmp(root->country, CountryName) < 0)
		root->Right = InsertInTree(root->Right, CountryName);

	return root;
}
LPosition ReadCityFromFile(LPosition Head, char* FileName)
{
	FILE* fp = NULL;
	char cty[MAX] = { 0 };
	int pop = 0;

	Head = CreateList(Head);

	fp = fopen(FileName, "r");
	if (fp == NULL)
	{
		printf("Error opening file!");
		return NULL;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %s %d", cty, &pop);
		CreateListElement(Head, cty, pop);
	}

	fclose(fp);
	return Head;
}
int CreateListElement(LPosition Head, char* CityName, int pop)
{
	LPosition NewEl = NULL;
	NewEl = CreateList(NewEl);

	strcpy(NewEl->city, CityName);
	NewEl->population = pop;

	while (Head->next != NULL)
	{
		if (NewEl->population < Head->next->population)
			break;
		else if (NewEl->population == Head->next->population)
		{
			if (strcmp(NewEl->city, Head->next->city) < 0)
				break;
			else if (strcmp(NewEl->city, Head->next->city) > 0)
			{
				Head = Head->next;
				continue;
			}
		}
		Head = Head->next;
	}
	NewEl->next = Head->next;
	Head->next = NewEl;
	return EXIT_SUCCESS;

}



int PrintInOrder(TPosition root)
{

	if (root == NULL)
		return -1;
	else
	{
		PrintInOrder(root->Left);
		printf("\n%s\n", root->country);
		PrintList(root->ListHead);
		PrintInOrder(root->Right);
	}
	printf("\n");

	return EXIT_SUCCESS;
}
int PrintList(LPosition Head)
{
	if (Head == NULL)
		return -1;
	else
	{
		Head = Head->next;
		while (Head != NULL)
		{
			printf("%s -> %d\n", Head->city, Head->population);
			Head = Head->next;
		}
		return EXIT_SUCCESS;
	}
}

TPosition FindCountry(TPosition root, char* CountryName)
{
	if (root == NULL)
		return NULL;
	else if (strcmp(CountryName, root->country) == 0)
		return root;
	else if (strcmp(CountryName, root->country) > 0)
		return FindCountry(root->Right, CountryName);

	return FindCountry(root->Left, CountryName);
}
int PrintResult(LPosition Head, int num)
{
	while (Head != NULL)
	{
		if (num < Head->population)
			printf(" %s-%d", Head->city, Head->population);
		Head = Head->next;
	}
	return EXIT_SUCCESS;
}