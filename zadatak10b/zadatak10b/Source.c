#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define MAX 256
#define HASH 11

struct _tree;
typedef struct _tree* TPosition;
typedef struct _tree
{
	char city[MAX];
	int population;
	TPosition Left;
	TPosition Right;

}tree;

struct _list;
typedef struct _list* LPosition;
typedef struct _list
{
	char country[MAX];
	TPosition TreeRoot;
	LPosition next;
}list;

struct _table;
typedef struct _table* Hash;
typedef struct _table
{
	LPosition* HashList;

}table;


int ReadCountryFromFile(Hash H, char* FileName);
TPosition ReadCityFromFile(TPosition root, char* CountryName);
int InsertSortedIntoList(LPosition Head, char* CountryName);
TPosition CreateTreeElement(TPosition root, char* grad, int pop);
int PrintList(LPosition Head);
int PrintInOrder(TPosition root);
int Print(TPosition root, int num);
LPosition CreateListElement(LPosition position);
LPosition AllocateListElement();
LPosition FindCountry(Hash H, char* CountryName);
Hash Initialize();
int AddIntoHash(char* CountryName, Hash H);
int Copy(char* CountryName);


int main()
{
	LPosition  Head = NULL;
	Hash HashTab = NULL;
	char File[MAX] = "drzave.txt", Countryname[MAX] = { 0 };
	int num = 0;

	HashTab = Initialize();
	Head = CreateListElement(Head);

	ReadCountryFromFile(HashTab, File);

	printf("Countries: \n");
	PrintList(Head->next);

	printf("Choose a country: ");
	scanf(" %s", Countryname);
	strcat(Countryname, ".txt");
	Head = FindCountry(HashTab, Countryname);
	if (!Head)
	{
		printf("There is not such a country!");
		return EXIT_SUCCESS;
	}
	printf("\nEnter a number of populaion: ");
	scanf("%d", &num);
	Print(Head->TreeRoot, num);

	return EXIT_SUCCESS;
}

Hash Initialize()
{
	Hash H = NULL;
	int i = 0;

	H = (Hash)malloc(sizeof(table));
	if (H == NULL)
	{
		printf("Error initializing table!\n");
		return NULL;
	}

	H->HashList = (LPosition*)malloc(sizeof(LPosition) * HASH);
	if (H->HashList == NULL)
	{
		printf("Error initializing table!\n");
		return NULL;
	}

	for (i = 0; i < HASH; i++)
		H->HashList[i] = AllocateListElement();

	return H;
}

int AddIntoHash(char* CountryName, Hash H)
{
	int index = 0;
	index = Copy(CountryName);

	InsertSortedIntoList(H->HashList[index], CountryName);

	return EXIT_SUCCESS;
}

int Copy(char* CountryName)
{
	int length = 0, leftover = 0, sum = 0, i = 0;
	length = strlen(CountryName);

	for (i = 0; i < length || i < 5; i++)
		sum += CountryName[i];

	leftover = sum % HASH;

	return leftover;
}

LPosition CreateListElement(LPosition position)
{
	position = (LPosition)malloc(sizeof(list));
	if (position == NULL)
	{
		perror("Can't allocate memory!");
		return NULL;
	}
	strcpy(position->country, "");
	position->next = NULL;
	position->TreeRoot = NULL;

	return position;
}

LPosition AllocateListElement()
{
	LPosition NewEl = NULL;
	NewEl = (LPosition)malloc(sizeof(list));
	if (NewEl == NULL)
	{
		perror("Can't allocate memory!");
		return NULL;
	}
	strcpy(NewEl->country, "");
	NewEl->next = NULL;
	NewEl->TreeRoot = NULL;

	return NewEl;
}

int ReadCountryFromFile(Hash H, char* FileName)
{
	FILE* fp = NULL;
	char CountryName[MAX] = { 0 };

	fp = fopen(FileName, "r");
	if (fp == NULL)
	{
		printf("Error opening file!\n");
		return -1;
	}

	while (!feof(fp))
	{
		fscanf(fp, "%s\n", CountryName);
		AddIntoHash(CountryName, H);
	}

	fclose(fp);
	return EXIT_SUCCESS;
}

int InsertSortedIntoList(LPosition Head, char* CountryName)
{
	LPosition NewEl = NULL;
	char pom[MAX] = { 0 };

	LPosition temp = NULL;
	temp = Head;

	NewEl = (LPosition)malloc(sizeof(list));
	if (NewEl == NULL)
	{
		perror("Can't allocate memory!");
		return -2;
	}

	strcpy(NewEl->country, CountryName);
	NewEl->TreeRoot = NULL;
	NewEl->TreeRoot = ReadCityFromFile(NewEl->TreeRoot, CountryName);
	strcpy(pom, CountryName);

	while (temp != NULL)
	{
		if (temp->next == NULL)
		{
			temp->next = NewEl;
			NewEl->next = NULL;
			break;
		}
		else if (strcmp(pom, temp->next->country) < 0)
		{
			NewEl->next = temp->next;
			temp->next = NewEl;
			break;
		}
		temp = temp->next;
	}
	return EXIT_SUCCESS;
}
TPosition ReadCityFromFile(TPosition root, char* FileName)
{
	FILE* fp = NULL;
	char cty[MAX] = { 0 };
	int pop = 0;

	fp = fopen(FileName, "r");
	if (fp == NULL)
	{
		printf("Error opening file.");
		return NULL;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %s %d\n", cty, &pop);
		root = CreateTreeElement(root, cty, pop);
	}
	fclose(fp);
	return root;
}
TPosition CreateTreeElement(TPosition root, char* CityName, int pop)
{
	TPosition current = NULL;
	current = root;

	if (current == NULL)
	{
		current = (TPosition)malloc(sizeof(tree));
		if (current == NULL)
		{
			printf("Greska pri alokaciji memorije");
			return NULL;
		}
		strcpy(current->city, CityName);
		current->population = pop;
		current->Left = NULL;
		current->Right = NULL;
	}
	else if (pop == current->population)
	{
		if (strcmp(CityName, current->city) < 0)
			current->Left = CreateTreeElement(current->Left, CityName, pop);
		else if (strcmp(CityName, current->city) > 0)
			current->Right = CreateTreeElement(current->Right, CityName, pop);
	}
	else
	{
		if (pop < current->population)
			current->Left = CreateTreeElement(current->Left, CityName, pop);
		else if (pop > current->population)
			current->Right = CreateTreeElement(current->Right, CityName, pop);
	}
	return current;
}
int PrintList(LPosition Head)
{
	LPosition temp = NULL;
	temp = Head;

	while (temp != NULL)
	{
		printf("\n%s:\n", temp->country);
		PrintInOrder(temp->TreeRoot);
		temp = temp->next;
	}
	return EXIT_SUCCESS;
}
int PrintInOrder(TPosition root)
{
	TPosition current = NULL;
	current = root;
	if (current == NULL)
		return 0;

	PrintInOrder(current->Left);
	printf("%s -> %d\n", current->city, current->population);
	PrintInOrder(current->Right);

	return EXIT_SUCCESS;
}
LPosition FindCountry(Hash H, char* CountryName)
{
	int index = 0;
	index = Copy(CountryName);
	LPosition temp = H->HashList[index];

	while (temp->next != NULL)
	{
		if (strcmp(CountryName, temp->next->country) == 0)
			return temp->next;
		else
			temp = temp->next;
	}
	return NULL;
}
int Print(TPosition root, int num)
{
	TPosition current = NULL;
	current = root;

	if (current == NULL)
		return 0;

	Print(current->Left, num);

	if (num < current->population)
		printf("%s %d\n", current->city, current->population);

	Print(current->Right, num);

	return EXIT_SUCCESS;
}