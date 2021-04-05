#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    char nome[30];
    char sobrenome[30];
    long int celular;
    long int cpf;
} REG;

int menu(int qtd);
int lerArquivo(REG *cad);
int inserir(REG *aux, REG *cad, int *qtd);
int excluir(long int cpf, REG *cad, int *qtd, char *name);
int buscaPorCPF(long int cpf, REG *cad, int qtd);
int buscaPorCELULAR(long int celular, REG *cad, int qtd);
int exibirInfo(int pos, REG *cad);
int saveCad(REG *cad, int qtd);
void bubbleSortCELULAR(REG *cad, int qtd);
void selectionSortCPF(REG *cad, int qtd);

int main()
{
    int opcao, qtd, code;
    REG cadastro[100], aux;
    char c, tempChar[30];
    long int tempNumeric;
    bool invalid = true;
    qtd = lerArquivo(cadastro);
    do
    {
        opcao = menu(qtd);
        switch (opcao)
        {
        case 1:
            puts("\nInserir Usuário\n");
            printf("Nome > ");
            scanf("%s", aux.nome);
            printf("Sobrenome > ");
            scanf("%s", aux.sobrenome);
            printf("Celular > ");
            scanf("%ld", &aux.celular);
            printf("CPF > ");
            scanf("%ld", &aux.cpf);
            inserir(&aux, cadastro, &qtd);
            break;
        case 2:
            puts("\nExcluir Usuário\n");
            puts("Insira o CPF do usuário à ser excluido:");
            printf("CPF > ");
            scanf("%ld", &tempNumeric);
            do
            {
                excluir(tempNumeric, cadastro, &qtd, tempChar);
                if (!tempChar[0])
                {
                    puts("CPF não encontrado!");
                    puts("Deseja tentar novamente?(y/n)");
                    getchar();
                    c = getchar();
                    if (!(c == 'y' || c == 'Y'))
                        break;
                    puts("Insira o CPF do usuário à ser excluido:");
                    printf("CPF > ");
                    scanf("%ld", &tempNumeric);
                }
                else
                {
                    printf("O usuário %s foi excluído!", tempChar);
                }

            } while (!tempChar[0]);
            break;
        case 3:
            puts("\nAlterar informações de usuário\n");
            puts("Insira o CPF do usuário à ser modificado:");
            printf("CPF > ");
            scanf("%ld", &tempNumeric);
            do
            {
                code = buscaPorCPF(tempNumeric, cadastro, qtd);
                if (code == -1)
                {
                    puts("CPF não encontrado!");
                    puts("Deseja tentar novamente?(y/n)");
                    getchar();
                    c = getchar();
                    if (!(c == 'y' || c == 'Y'))
                        break;
                    puts("Insira o CPF do usuário à ser modificado:");
                    printf("CPF > ");
                    scanf("%ld", &tempNumeric);
                }
                else
                {
                    printf("As informações do usuário \"%s %s\" serão modificadas.\n", cadastro[code].nome, cadastro[code].sobrenome);
                    printf("Novo nome > ");
                    scanf("%s", cadastro[code].nome);
                    printf("Novo sobrenome > ");
                    scanf("%s", cadastro[code].sobrenome);
                    printf("Novo celular > ");
                    scanf("%ld", &cadastro[code].celular);
                    printf("Novo cpf > ");
                    scanf("%ld", &cadastro[code].cpf);
                }

            } while (code == -1);
            puts("Modificações feitas!");
            break;
        case 4:
            puts("\nBusca por telefone\n");
            printf("Telefone > ");
            scanf("%ld", &tempNumeric);
            do
            {
                code = buscaPorCELULAR(tempNumeric, cadastro, qtd);
                if (code == -1)
                {
                    puts("Telefone não encontrado!");
                    puts("Deseja tentar novamente?(y/n)");
                    getchar();
                    c = getchar();
                    if (!(c == 'y' || c == 'Y'))
                        break;
                    puts("Insira o telefone do usuário novamente:");
                    printf("Telefone > ");
                    scanf("%ld", &tempNumeric);
                }
                else
                {
                    exibirInfo(code, cadastro);
                }
            } while (code == -1);
            break;
        case 5:
            puts("\nBusca por CPF\n");
            printf("CPF > ");
            scanf("%ld", &tempNumeric);

            do
            {
                code = buscaPorCPF(tempNumeric, cadastro, qtd);
                if (code == -1)
                {
                    puts("CPF não encontrado!");
                    puts("Deseja tentar novamente?(y/n)");
                    getchar();
                    c = getchar();
                    if (!(c == 'y' || c == 'Y'))
                        break;
                    puts("Insira o CPF do usuário novamente:");
                    printf("CPF > ");
                    scanf("%ld", &tempNumeric);
                }
                else
                {
                    exibirInfo(code, cadastro);
                }
            } while (code == -1);
            break;
        case 6:
            puts("Deseja salvar as modificações?(y/n)");
            getchar();
            c = getchar();
            if (c == 'y' || c == 'Y')
            {
                saveCad(cadastro, qtd);
                puts("Modificações salvas com sucesso!");
            }
            invalid = false;
            break;

        default:
            puts("Opção inválida!");
            break;
        }

    } while (invalid);
    puts("Obrigado por usar nosso serviço!");
    return 0;
}

int exibirInfo(int pos, REG *cad)
{
    for (int i = 0; i < 80; i++)
        printf("-");
    puts("\n");
    printf("Nome......: %s\n", (cad + pos)->nome);
    printf("Sobrenome.: %s\n", (cad + pos)->sobrenome);
    printf("Celular...: %ld\n", (cad + pos)->celular);
    printf("CPF.......: %ld", (cad + pos)->cpf);
    puts("\n");
    for (int i = 0; i < 80; i++)
        printf("-");
    getchar();
    getchar();
    return 0;
}

int buscaPorCELULAR(long int celular, REG *cad, int qtd)
{
    int i;
    bubbleSortCELULAR(cad, qtd);
    for (i = 0; i < qtd && (cad + i)->celular < celular; i++)
        ;
    if ((cad + i)->celular == celular)
    {
        return i;
    }
    return -1;
}

int buscaPorCPF(long int cpf, REG *cad, int qtd)
{
    int i;
    selectionSortCPF(cad, qtd);
    for (i = 0; i < qtd && (cad + i)->cpf < cpf; i++)
        ;
    if ((cad + i)->cpf == cpf)
    {
        return i;
    }
    return -1;
}

int excluir(long int cpf, REG *cad, int *qtd, char *name)
{
    bool find = false;
    for (int i = 0; i < *qtd; i++)
    {
        if (cpf == (cad + i)->cpf)
        {
            --(*qtd);
            find = true;
            strcpy(name, (cad + i)->nome);
        }
        if (!find)
        {
            continue;
        }
        else
        {
            *(cad + i) = *(cad + (i + 1));
        }
    }
    return 0;
}
void bubbleSortCELULAR(REG *cad, int qtd)
{
    int i, j;
    REG aux;
    for (i = qtd - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if ((cad + j)->celular > (cad + j + 1)->celular)
            {
                aux = *(cad + j);
                *(cad + j) = *(cad + j + 1);
                *(cad + j + 1) = aux;
            }
        }
    }
}
void selectionSortCPF(REG *cad, int qtd)
{
    int i, j, min;
    REG auxCad;
    for (i = 0; i < qtd - 1; i++)
    {
        auxCad = *(cad + i);
        min = i;
        for (j = i + 1; j < qtd; j++)
        {
            if ((cad + j)->cpf < auxCad.cpf)
            {
                min = j;
                auxCad = *(cad + j);
            }
        }
        *(cad + min) = *(cad + i);
        *(cad + i) = auxCad;
    }
}
int saveCad(REG *cad, int qtd)
{
    FILE *arq;
    arq = fopen("./arquivo de clientes.txt", "w+");
    fprintf(arq, "%d", qtd);
    fputs("\n", arq);
    for (int i = 0; i < qtd; i++)
    {
        fprintf(arq, "%s ", (cad + i)->nome);
        fprintf(arq, "%s ", (cad + i)->sobrenome);
        fprintf(arq, "%ld ", (cad + i)->celular);
        fprintf(arq, "%ld ", (cad + i)->cpf);
        fputs("\n", arq);
    }
    fclose(arq);
}

int inserir(REG *aux, REG *cad, int *qtd)
{
    printf("%ld", aux->celular);
    *(cad + *qtd) = *aux;
    ++(*qtd);
}
int lerArquivo(REG *cad)
{
    int qtd;
    FILE *arq = fopen("./arquivo de clientes.txt", "r");
    if (!arq)
    {
        puts("Erro ao abrir a base de dados!");
        exit(0);
    }
    fscanf(arq, "%d", &qtd);
    if (qtd > 100)
        printf("Alguns registros serão perdidos, o sistema tem capacidade de lidar com no maximo 100 clientes, essa base de dados possui %d clientes.", qtd);
    for (int i = 0; i < qtd; i++)
    {
        fscanf(arq, "%s", (cad + i)->nome);
        fscanf(arq, "%s", (cad + i)->sobrenome);
        fscanf(arq, "%ld", &(cad + i)->celular);
        fscanf(arq, "%ld", &(cad + i)->cpf);
    }
    fclose(arq);
    bubbleSortCELULAR(cad, qtd); //Ordenando durante a leitura inicial, como o pedido no topico 4 de Requisitos;
    return qtd;
}
int menu(int qtd)
{
    int op;
    puts("\n-----------------------Menu de Opções------------------------------");
    printf("%d Clientes\n", qtd);
    puts("\n1)Inserir");
    puts("2)Excluir");
    puts("3)Alterar");
    puts("4)Buscar por telefone");
    puts("5)Buscar por CPF");
    puts("\n6)Sair");
    printf("\n\nDigite uma opção > ");
    scanf("%d", &op);
    return op;
}
