#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

#pragma region Estruturas de Armazenamento

typedef struct 
{
    int id;
    char nome[15];
    long int telemovel;
} Pessoa;

typedef struct
{
    int id;
    int dia;
    int mes;
    int ano;
    char tipoRefeicao[30];
    char alimento[60];
    int calorias;
} Dieta;

typedef struct
{
    int id;
    int dia;
    int mes;
    int ano;
    char tipoRefeicao[20];
    int maxCal;
    int minCal;
} Plano;

#pragma endregion

int menu();
void listaPessoasExcederLimite(Dieta dietas[], Pessoa pessoas[], int numDietas, int numPessoas, int maxCalories, int startDia, int startMes, int startAno, int endDia, int endMes, int endAno);
int comparaData(int year1, int month1, int day1, int year2, int month2, int day2);



int main()
{
    setlocale(LC_ALL, "pt_BR.utf8");
    int opcao;
    Pessoa pessoas[100];
    Dieta dietas[100];
    Plano planos[100]; 
    int numPessoas = 0;
    int numDietas = 0;
    int numPlanos = 0;
    
    
    #pragma region Leitura de Ficheiros
     
    FILE *filePessoas = fopen("Registos1.txt", "r");
    if (filePessoas == NULL) {
        printf("Erro na abertura de Registos1!\n");
        return 1; 
    }

    while (fscanf(filePessoas, "%d;%14[^;];%ld", &pessoas[numPessoas].id, pessoas[numPessoas].nome, &pessoas[numPessoas].telemovel) == 3) {
        numPessoas++;
    }

    fclose(filePessoas);


    FILE *fileDietas = fopen("Registos2.txt", "r");
    if (fileDietas == NULL) {
        printf("Erro na abertura de Registos2!\n");
        return 1; // Return an error code
    }
    // Corrected loop for reading data into the dietas array
    while (fscanf(fileDietas, "%d;%d-%d-%d;%29[^;];%59[^;];%d", 
            &dietas[numDietas].id, &dietas[numDietas].ano, &dietas[numDietas].mes, &dietas[numDietas].dia, 
            dietas[numDietas].tipoRefeicao, dietas[numDietas].alimento, &dietas[numDietas].calorias) == 7) {
        numDietas++;
}

    fclose(fileDietas);


    FILE *filePlanos = fopen("Registos3.txt", "r");
    if (filePlanos == NULL) {
        printf("Error opening file.\n");
        return 1; // Return an error code
    }

    while (fscanf(filePlanos, "%d;%d-%d-%d;%19[^;];%d;%d", &planos[numPlanos].id, &planos[numPlanos].ano, &planos[numPlanos].mes, &planos[numPlanos].dia, planos[numPlanos].tipoRefeicao, &planos[numPlanos].maxCal, &planos[numPlanos].minCal) == 7) {
        numPlanos++;
    }

    fclose(filePlanos);

    #pragma endregion


    do
    {
        opcao = menu();
        switch (opcao)
        {
        case 1:
            {

                int startDia, startMes, startAno, endDia, endMes, endAno;
                int caloriasLimite;

                printf("Insira a data de Inicio (YYYY-MM-DD): ");
                scanf("%d-%d-%d", &startAno, &startMes, &startDia);

                printf("Insira a data de Fim (YYYY-MM-DD): ");
                scanf("%d-%d-%d", &endAno, &endMes, &endDia);

                printf("Insira o limite das calorias: ");
                scanf("%d", &caloriasLimite);

                listaPessoasExcederLimite(dietas, pessoas, numDietas, numPessoas, caloriasLimite, startDia, startMes, startAno, endDia, endMes, endAno);
                system("pause");
                break;

            }
            
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

//Funcao Menu 

int menu()
{
    int op;
    do
    {
        printf("M E N U\n");
        printf("1 - Numero de pessoas a exceder determinado numero de calorias\n");
        printf("2 - Pessoas que nao cumpriram o plano (ordem decrescente)\n");
        printf("3 - Lista plano nutricional\n");
        printf("4 - Calculos das medias de calorias\n");
        printf("5 - Gerar Tabela\n");
        printf("6 - -\n");
        printf("7 - -\n");
        printf("8 - -\n");
        printf("9 - Guardar tabela\n");
        printf("0 - Sair\n");
        printf("Opcao?");
        scanf("%d", &op);
    } while ((op < 0) || (op > 10));
    return (op);
}

//Funcao listar pessoas a exceder o plano



void listaPessoasExcederLimite(Dieta dietas[], Pessoa pessoas[], int numDietas, int numPessoas, int caloriasLimite, int startDia, int startMes, int startAno, int endDia, int endMes, int endAno) {
    int count = 0;

    printf("Pacientes a exceder %d calorias\n\n", caloriasLimite);

    for (int i = 0; i < numPessoas; ++i) {
        int totalCalorias = 0;

        for (int j = 0; j < numDietas; ++j) {
            if (pessoas[i].id == dietas[j].id && comparaData(startAno, startMes, startDia, dietas[j].ano, dietas[j].mes, dietas[j].dia) <= 0 
                && comparaData(dietas[j].ano, dietas[j].mes, dietas[j].dia, endAno, endMes, endDia) <= 0) {
                totalCalorias += dietas[j].calorias;
            }
        }

        if (totalCalorias > caloriasLimite) {
            printf("ID Paciente : %d\n - Nome: %s\n - Calorias ingeridas: %d\n\n", pessoas[i].id, pessoas[i].nome, totalCalorias);
            ++count;
        }
    }

    printf("Numero de pacientes que ingeriram mais de %d calorias: %d\n", caloriasLimite, count);
}



// Função para comparar datas 
int comparaData(int ano1, int mes1, int dia1, int ano2, int mes2, int dia2) {
    if (ano1 != ano2) {     // Se o ano não for igual retorna a diferença entre eles
        return ano1 - ano2; // Se for igual passa à próxima condição
    } else if (mes1 != mes2) {
        return mes1 - mes2; // Retorna a diferença se o mês não for igual
    } else {
        return dia1 - dia2; // retorna a diferença do dia
    }
}






