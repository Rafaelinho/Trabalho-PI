#include <stdlib.h>
#include <stdio.h>

// Function prototypes
typedef struct 
{
    int id;
    char nome[15];
    long int telemovel;
} Pessoa;

typedef struct
{
    int id;
    char data[11];
    char tipoRefeicao[20];
    char alimento[20];
    int calorias[20];
} Dieta;

typedef struct
{
    int id;
    int data[11];
    char tipoRefeicao[20];
    int maxCal;
    int minCal;
} Plano;
