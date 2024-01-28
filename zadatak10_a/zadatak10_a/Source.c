#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 50

struct grad;
typedef struct grad* posG;
typedef struct grad {
    char ime_grada[50];
    int br_st;
    posG D;
    posG L;
}grad;

struct drzava;
typedef struct drzava* posD;
typedef struct drzava {
    char ime_drzave[50];
    posG Grad;
    posD next;
}drzava;

int DodajDrzavu(char* imeDrzave, char* imeDat, posD p);
int DodajGrad(char* imeDat, posG s);
posG NoviGrad(char* imeGrada, int stanovnici, posG s);
int IspisDrzava(posD p);
int IspisGrada(posG s);
int BrisiDrzave(posD p);
int BrisiGrad(posG q);

int main()
{
    posD head = NULL;
    head = (posD)malloc(sizeof(struct drzava));
    head->next = NULL;
    if (head == NULL)
    {
        printf("Greska pri alokaciji\n");
        return EXIT_FAILURE;
    }

    char ime_dat[MAX];
    char imeDrzave[MAX];
    char imeDat[MAX];
    int stanovnici = 0;

    printf("Unesi ime datoteke u kojoj su upisane drzave\n");
    scanf("%s", ime_dat);

    FILE* fp = NULL;
    fp = fopen(ime_dat, "r");
    if (fp == NULL)
    {
        printf("Datoteka se ne moze otvoriti\n");
        return EXIT_FAILURE;
    }

    while (!feof(fp))
    {
        fscanf(fp, "%s %s", imeDrzave, imeDat);
        DodajDrzavu(imeDrzave, imeDat, head);

    }
    fclose(fp);

    IspisDrzava(head->next);

    BrisiDrzave(head->next);

    return EXIT_SUCCESS;
}

int DodajDrzavu(char* imeDrzave, char* imeDat, posD p)
{
    posD q = NULL;
    q = (posD)malloc(sizeof(struct drzava));
    q->next = NULL;

    posG c = NULL;

    c = (posG)malloc(sizeof(struct grad));
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

    strcpy(q->ime_drzave, imeDrzave);

    while (p->next != NULL && strcmp(p->next->ime_drzave, q->ime_drzave) < 0)
    {
        p = p->next;
    }

    q->next = p->next;
    p->next = q;


    strcpy(c->ime_grada, "");
    c->br_st = 0;
    c->D = NULL;
    c->L = NULL;
    q->Grad = c;

    DodajGrad(imeDat, q->Grad);


    return EXIT_SUCCESS;;
}

int DodajGrad(char* imeDat, posG s)
{

    FILE* dat = NULL;
    char imeGr[50];
    int stanovnici = 0;


    dat = fopen(imeDat, "r");
    if (dat == NULL)
    {
        printf("Datoteka se ne moze otvoriti.\n");
        return EXIT_FAILURE;
    }
    while (!feof(dat))
    {
        fscanf(dat, "%s %d", imeGr, &stanovnici);
        s = NoviGrad(imeGr, stanovnici, s);
    }
    fclose(dat);
    return EXIT_SUCCESS;
}

posG NoviGrad(char* imeGrada, int stanovnici, posG s)
{
    posG q = NULL;
    if (s == NULL)
    {
        q = (posG)malloc(sizeof(struct grad));
        if (q == NULL)
        {
            printf("Greska pri alokaciji\n");
            return 0;
        }
        strcpy(q->ime_grada, imeGrada);
        q->br_st = stanovnici;
        q->D = NULL;
        q->L = NULL;
        return q;
    }


    if (s->br_st < stanovnici)

        s->D = NoviGrad(imeGrada, stanovnici, s->D);

    else if (s->br_st > stanovnici)

        s->L = NoviGrad(imeGrada, stanovnici, s->L);

    else if (stanovnici == s->br_st)
    {
        if (strcmp(imeGrada, s->ime_grada) >= 0)

            s->D = NoviGrad(imeGrada, stanovnici, s->D);

        else

            s->L = NoviGrad(imeGrada, stanovnici, s->L);

    }

    return s;
}

int IspisDrzava(posD p)
{

    while (p != NULL)
    {
        printf("\n%s\n", p->ime_drzave);
        IspisGrada(p->Grad);
        p = p->next;
    }
    return EXIT_SUCCESS;
}

int IspisGrada(posG s)
{
    if (s != NULL)
    {
        IspisGrada(s->L);
        printf("%s\n", s->ime_grada);
        IspisGrada(s->D);
    }
    return EXIT_SUCCESS;;
}
int BrisiDrzave(posD p)
{
    posD temp = NULL;
    while (p->next != NULL)
    {
        temp = p->next;
        p->next = temp->next;
        BrisiGrad(temp->Grad);
        free(temp);
    }
    return EXIT_SUCCESS;
}
int BrisiGrad(posG q)
{
    if (q != NULL)
    {
        BrisiGrad(q->L);
        BrisiGrad(q->D);
        free(q);
    }
    return EXIT_SUCCESS;
}
