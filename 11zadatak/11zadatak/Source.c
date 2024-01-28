#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define HASH_TABLE_SIZE 11

struct Grad;
typedef struct Grad* PositionGrad;
typedef struct Grad {
    char ime_grada[MAX_NAME_LENGTH];
    int br_st;
    PositionGrad D;
    PositionGrad L;
} Grad;

struct Drzava;
typedef struct Drzava* PositionDrzava;
typedef struct Drzava {
    char ime_drzave[MAX_NAME_LENGTH];
    PositionGrad Grad;
    PositionDrzava next;
} Drzava;

typedef struct HashNode {
    PositionDrzava drzava;
    struct HashNode* next;
} HashNode;

typedef struct {
    HashNode* table[HASH_TABLE_SIZE];
} HashTable;

int InitializeHashTable(HashTable* hashTable);
unsigned int HashFunction(char* key);
HashNode* CreateHashNode(PositionDrzava drzava);
int InsertIntoHashTable(HashTable* hashTable, PositionDrzava drzava);
PositionDrzava FindInHashTable(HashTable* hashTable, char* key);
int InitializeDrzavaList(PositionDrzava* drzavaList);
PositionDrzava CreateCountryNode(char* countryName);
PositionGrad CreateCityNode(char* cityName, int population);
int InsertCountryIntoList(HashTable* hashTable, char* countryName, char* fileName);
int InsertCitiesFromFile(PositionDrzava country, char* fileName);
void PrintHashTable(HashTable* hashTable);
void PrintDrzavaList(PositionDrzava drzavaList);
void PrintCities(PositionGrad root);
void ClearDrzavaList(PositionDrzava* drzavaList);
void ClearCities(PositionGrad root);

int main() {
    HashTable hashTable;
    InitializeHashTable(&hashTable);

    char fileName[MAX_NAME_LENGTH];
    printf("Unesite ime datoteke s popisom drzava i datotekama gradova: ");
    scanf("%s", fileName);

    FILE* file = fopen(fileName, "r");
    if (!file) {
        printf("Greska pri otvaranju datoteke.\n");
        return EXIT_FAILURE;
    }

    char countryName[MAX_NAME_LENGTH];
    char cityFileName[MAX_NAME_LENGTH];

    while (fscanf(file, "%s %s", countryName, cityFileName) == 2) {
        InsertCountryIntoList(&hashTable, countryName, cityFileName);
    }

    fclose(file);

    printf("Popis drzava i gradova:\n");
    PrintHashTable(&hashTable);

    // Oslobodi memoriju
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        HashNode* current = hashTable.table[i];
        while (current != NULL) {
            HashNode* temp = current;
            current = current->next;
            free(temp);
        }
    }

    return EXIT_SUCCESS;
}

int InitializeHashTable(HashTable* hashTable) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        hashTable->table[i] = NULL;
    }
    return EXIT_SUCCESS;
}

unsigned int HashFunction(char* key) {
    unsigned int hash = 0;
    int length = strlen(key);
    for (int i = 0; i < length; i++) {
        hash += key[i];
    }
    return hash % HASH_TABLE_SIZE;
}

HashNode* CreateHashNode(PositionDrzava drzava) {
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    if (!newNode) {
        printf("Neuspjesna alokacija memorije.\n");
        return NULL;
    }
    newNode->drzava = drzava;
    newNode->next = NULL;
    return newNode;
}

int InsertIntoHashTable(HashTable* hashTable, PositionDrzava drzava) {
    unsigned int index = HashFunction(drzava->ime_drzave);
    HashNode* newNode = CreateHashNode(drzava);
    if (!newNode) {
        return EXIT_FAILURE;
    }
    if (hashTable->table[index] == NULL) {
        hashTable->table[index] = newNode;
    }
    else {
        HashNode* current = hashTable->table[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    return EXIT_SUCCESS;
}

PositionDrzava FindInHashTable(HashTable* hashTable, char* key) {
    unsigned int index = HashFunction(key);
    HashNode* current = hashTable->table[index];
    while (current != NULL) {
        if (strcmp(current->drzava->ime_drzave, key) == 0) {
            return current->drzava;
        }
        current = current->next;
    }
    return NULL;
}

int InitializeDrzavaList(PositionDrzava* drzavaList) {
    *drzavaList = NULL;
    return EXIT_SUCCESS;
}

PositionDrzava CreateCountryNode(char* countryName) {
    PositionDrzava newCountry = (PositionDrzava)malloc(sizeof(Drzava));
    if (!newCountry) {
        printf("Neuspjesna alokacija memorije.\n");
        return NULL;
    }
    strcpy(newCountry->ime_drzave, countryName);
    newCountry->Grad = NULL;
    newCountry->next = NULL;
    return newCountry;
}

PositionGrad CreateCityNode(char* cityName, int population) {
    PositionGrad newCity = (PositionGrad)malloc(sizeof(Grad));
    if (!newCity) {
        printf("Neuspjesna alokacija memorije.\n");
        return NULL;
    }
    strcpy(newCity->ime_grada, cityName);
    newCity->br_st = population;
    newCity->D = NULL;
    newCity->L = NULL;
    return newCity;
}

int InsertCountryIntoList(HashTable* hashTable, char* countryName, char* fileName) {
    PositionDrzava country = FindInHashTable(hashTable, countryName);
    if (country == NULL) {
        country = CreateCountryNode(countryName);
        if (country == NULL) {
            return EXIT_FAILURE;
        }
        InsertIntoHashTable(hashTable, country);
    }
    InsertCitiesFromFile(country, fileName);
    return EXIT_SUCCESS;
}

int InsertCitiesFromFile(PositionDrzava country, char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (!file) {
        printf("Greska pri otvaranju datoteke.\n");
        return EXIT_FAILURE;
    }

    char cityName[MAX_NAME_LENGTH];
    int population;

    while (fscanf(file, "%s %d", cityName, &population) == 2) {
        PositionGrad newCity = CreateCityNode(cityName, population);
        if (!newCity) {
            fclose(file);
            return EXIT_FAILURE;
        }
        if (country->Grad == NULL) {
            country->Grad = newCity;
        }
        else {
            PositionGrad current = country->Grad;
            while (1) {
                if (population > current->br_st) {
                    if (current->D == NULL) {
                        current->D = newCity;
                        break;
                    }
                    current = current->D;
                }
                else if (population < current->br_st) {
                    if (current->L == NULL) {
                        current->L = newCity;
                        break;
                    }
                    current = current->L;
                }
                else {
                    if (strcmp(cityName, current->ime_grada) >= 0) {
                        if (current->D == NULL) {
                            current->D = newCity;
                            break;
                        }
                        current = current->D;
                    }
                    else {
                        if (current->L == NULL) {
                            current->L = newCity;
                            break;
                        }
                        current = current->L;
                    }
                }
            }
        }
    }

    fclose(file);
    return EXIT_SUCCESS;
}

void PrintHashTable(HashTable* hashTable) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        printf("Hash %d: ", i);
        HashNode* current = hashTable->table[i];
        while (current != NULL) {
            printf("%s -> ", current->drzava->ime_drzave);
            PrintDrzavaList(current->drzava);
            current = current->next;
        }
        printf("\n");
    }
}

void PrintDrzavaList(PositionDrzava drzavaList) {
    while (drzavaList != NULL) {
        printf("\n\tDrzava: %s\n", drzavaList->ime_drzave);
        printf("\tGradovi:\n");
        PrintCities(drzavaList->Grad);
        drzavaList = drzavaList->next;
    }
}

void PrintCities(PositionGrad root) {
    if (root != NULL) {
        PrintCities(root->L);
        printf("\t\t%s - %d stanovnika\n", root->ime_grada, root->br_st);
        PrintCities(root->D);
    }
}

