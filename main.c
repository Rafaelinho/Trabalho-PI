#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>

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
int comparaData(int year1, int month1, int day1, int year2, int month2, int day2);
void listaPessoasExcederLimite(Dieta dietas[], Pessoa pessoas[], int numDietas, int numPessoas, int maxCalories, int startDia, int startMes, int startAno, int endDia, int endMes, int endAno);
void listaNaoCumpridoresDecrescente(Dieta dietas[], Pessoa pessoas[], Plano planos[], int numDietas, int numPessoas, int numPlanos, int startDia, int startMes, int startAno, int endDia, int endMes, int endAno);
bool pessoaExcedeuPlano(Dieta dietas[], Plano planos[], Pessoa pessoas[], int pessoaID, int numDietas, int numPlanos, int startDia, int startMes, int startAno, int endDia, int endMes, int endAno);

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
            
            
        case 2:
            {
                int startDia, startMes, startAno, endDia, endMes, endAno;

                printf("Enter the start date (YYYY-MM-DD): ");
                scanf("%d-%d-%d", &startAno, &startMes, &startDia);

                printf("Enter the end date (YYYY-MM-DD): ");
                scanf("%d-%d-%d", &endAno, &endMes, &endDia);

                listaNaoCumpridoresDecrescente(dietas, pessoas, planos, numDietas, numPessoas, numPlanos, startDia, startMes, startAno, endDia, endMes, endAno);
                system("pause");
                break;
            }
          
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


//Funcao listar pessoas a exceder determinado limite de calorias em determinado período
void listaPessoasExcederLimite(Dieta dietas[], Pessoa pessoas[], int numDietas, int numPessoas, int caloriasLimite, int startDia, int startMes, int startAno, int endDia, int endMes, int endAno) {
    int countPessoas = 0;

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
            ++countPessoas;
        }
    }

    printf("Numero de pacientes que ingeriram mais de %d calorias: %d\n", caloriasLimite, countPessoas);
}



// Função que retorna verdadeiro ou falso se o paciente ultrapassou as calorias máxmimas em cada dia do plano, em determinado período de tempo, 
bool pessoaExcedeuPlano(Dieta dietas[], Plano planos[], Pessoa pessoas[], int pessoaID, int numDietas, int numPlanos, int startDia, int startMes, int startAno, int endDia, int endMes, int endAno) {
    bool pessoaExcedeu = false;

    for (int i = 0; i < numPlanos; ++i) {
        if (pessoaID == planos[i].id) {
            for (int j = 0; j < numDietas; ++j) {
                if (pessoaID == dietas[j].id && planos[i].dia == dietas[j].dia && dietas[j].calorias > planos[i].maxCal &&
                    comparaData(dietas[j].ano, dietas[j].mes, dietas[j].dia, startAno, startMes, startDia) >= 0 &&
                    comparaData(endAno, endMes, endDia, dietas[j].ano, dietas[j].mes, dietas[j].dia) >= 0 &&
                    strcmp(dietas[j].tipoRefeicao, planos[i].tipoRefeicao) == 0) {
                    printf("ID Paciente: %d\n - Nome: %s\n - Dia do Plano Excedido: %d\n - Tipo de Refeição: %s\n - Diferença de Calorias: %d\n\n",
                           pessoaID, pessoas[pessoaID-1].nome, dietas[j].dia, dietas[j].tipoRefeicao, dietas[j].calorias - planos[i].maxCal);
                    pessoaExcedeu = true;
                }
            }
        }
    }

    return pessoaExcedeu;
}




//Função listar pessoas que não cumpriram o plano em determinado período, por ordem decrescente (do id da pessoa)
void listaNaoCumpridoresDecrescente(Dieta dietas[], Pessoa pessoas[], Plano planos[], int numDietas, int numPessoas, int numPlanos, int startDia, int startMes, int startAno, int endDia, int endMes, int endAno) {
    printf("Pessoas que não cumpriram o plano no período especificado (ordem decrescente):\n");

    for (int i = 0; i < numPessoas; ++i) {
        pessoaExcedeuPlano(dietas, planos, pessoas, pessoas[i].id, numDietas, numPlanos, startDia, startMes, startAno, endDia, endMes, endAno);
    }
}








