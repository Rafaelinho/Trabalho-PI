#include <stdlib.h>

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
    int dia;
    int mês;
    int ano;
    char tipoRefeicao[20];
    int maxCal;
    int minCal;
} Plano;

int menu();

int main()
{
    int opcao;
    Pessoa pessoas[100];
    Dieta dietas[100];
    Plano planos[20]; 
    int numPessoas = 0;

    do
    {
        opcao = menu();
        switch (opcao)
        {
        case 1:
            
            
            break;
        case 2:
           
            
            break;
        case 3:
           
            break;
        case 4:
           
            break;
        
        case 5:
           
            break;
        case 6:
           
            break;
        case 7:
           
            break;
        case 8:
           
            break;
        }
    } while (opcao != 0);

    return 0;
}

int menu()
{
    int op;
    do
    {
        printf("M E N U\n");
        printf("1 - -\n");
        printf("2 - -\n");
        printf("3 - -\n");
        printf("4 - Numero de pessoas a exceder o plano\n");
        printf("5 - Pessoas que nao cumpriram o plano (ordem decrescente)\n");
        printf("6 - Lista plano nutricional\n");
        printf("7 - Calculos das medias de calorias\n");
        printf("8 - Gerar Tabela\n");
        printf("9 - Guardar\n");
        printf("0 - Sair\n");
        printf("Opcao?");
        scanf("%d", &op);
    } while ((op < 0) || (op > 10));
    return (op);
}
