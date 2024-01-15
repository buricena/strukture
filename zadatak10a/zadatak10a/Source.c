#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 50

struct city;
typedef struct city* posG;
typedef struct city {
    char city_name[50];
    int population;
    posG D;
    posG L;
}city;

struct country;
typedef struct country* posD;
typedef struct country {
    char country_name[50];
    posG City;
    posD next;
}country;

int addcountry(char* countryName, char* FileName, posD p);
int addcity(char* FileName, posG s);
posG newcity (char* cityName, int stanovnici, posG s);
int printcountry(posD p);
int printcity(posG s);
int deletecountry(posD p);
int deletecity(posG q);

int main()
{
    posD head = NULL;
    head = (posD)malloc(sizeof(struct country));
    head->next = NULL;
    if (head == NULL)
    {
        printf("Greska pri alokaciji\n");
        return EXIT_FAILURE;
    }

    char file_name[MAX];
    char country_name[MAX];
    char FileName[MAX];
    int pop = 0;

    printf("Unesi ime datoteke u kojoj su upisane drzave\n");
    scanf("%s", file_name);

    FILE* fp = NULL;
    fp = fopen(file_name, "r");
    if (fp == NULL)
    {
        printf("Datoteka se ne moze otvoriti\n");
        return EXIT_FAILURE;
    }

    while (!feof(fp))
    {
        fscanf(fp, "%s %s", country_name, FileName);
        addcountry(country_name, FileName, head);

    }
    fclose(fp);

    printcountry(head->next);

    deletecountry(head->next);

    return EXIT_SUCCESS;
}

int addcountry(char* countryName, char* FileName, posD p)
{
    posD q = NULL;
    q = (posD)malloc(sizeof(struct country));
    q->next = NULL;

    posG c = NULL;

    c = (posG)malloc(sizeof(struct city));
    if (c == NULL)
    {
        printf("Greska pri alokaciji");
        return EXIT_FAILURE;
    }

    if (q == NULL)
    {
        printf("Greska pri alokaciji");
        return EXIT_FAILURE;
    }

    strcpy(q->country_name, countryName);
   
    while (p->next != NULL && strcmp(p->next->country_name, q->country_name) < 0) {
        p = p->next;
    }
   
    q->next = p->next;
    p->next = q;


    strcpy(c->city_name, "");
    c->population = 0;
    c->D = NULL;
    c->L = NULL;
    q->City = c;

    addcity(FileName, q->City);


    return EXIT_SUCCESS;;
}

int addcity(char* FileName, posG s)
{

    FILE* dat = NULL;
    char cityName[50];
    int pop = 0;


    dat = fopen(FileName, "r");
    if (dat == NULL)
    {
        printf("Datoteka se ne moze otvoriti.\n");
        return EXIT_FAILURE;
    }
    while (!feof(dat))
    {
        fscanf(dat, "%s %d", cityName, &pop);
        s = newcity(cityName, pop, s);
    }
    fclose(dat);
    return EXIT_SUCCESS;
}

posG newcity(char* cityName, int stanovnici, posG s)
{
    posG q = NULL;
    if (s == NULL)
    {
        q = (posG)malloc(sizeof(struct city));
        if (q == NULL)
        {
            printf("Greska pri alokaciji\n");
            return 0;
        }
        strcpy(q->city_name, cityName);
        q->population = stanovnici;
        q->D = NULL;
        q->L = NULL;
        return q;
    }


    if (s->population < stanovnici)

        s->D = newcity(cityName, stanovnici, s->D);

    else if (s->population > stanovnici)

        s->L = newcity(cityName, stanovnici, s->L);

    else if (stanovnici == s->population)
    {
        if (strcmp(cityName, s->city_name) >= 0)

            s->D = newcity(cityName, stanovnici, s->D);

        else

            s->L = newcity(cityName, stanovnici, s->L);

    }

    return s;
}

int printcountry(posD p)
{

    while (p != NULL)
    {
        printf("\n%s\n", p->country_name);
        printcity(p->City);
        p = p->next;
    }
    return EXIT_SUCCESS;
}

int printcity(posG s)
{
    if (s != NULL)
    {
        printcity(s->L);
        printf("%s\n", s->city_name);
        printcity(s->D);
    }
    return EXIT_SUCCESS;;
}
int deletecountry(posD p)
{
    posD temp = NULL;
    while (p->next != NULL)
    {
        temp = p->next;
        p->next = temp->next;
        deletecity(temp->City);
        free(temp);
    }
    return EXIT_SUCCESS;
}
int deletecity(posG q)
{
    if (q != NULL)
    {
        deletecity(q->L);
        deletecity(q->D);
        free(q);
    }
    return EXIT_SUCCESS;
}