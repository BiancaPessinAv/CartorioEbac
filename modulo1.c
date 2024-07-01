#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

#define MAX_NOMES 100
#define MAX_TAMANHO_NOME 100
#define MAX_TENTATIVAS 3

void limparTela() {
    system("cls");
}

// Função para ler senha sem ecoar no console
void lerSenha(char* senha, int tamanho) {
    int i = 0;
    char ch;
    while (i < tamanho - 1) {
        ch = getch();
        if (ch == '\r') { // Enter key
            break;
        } else if (ch == '\b') { 
            if (i > 0) {
                i--;
                printf("\b \b"); 
            }
        } else {
            senha[i++] = ch;
            printf("*");
        }
    }
    senha[i] = '\0';
    printf("\n");
}

// Função simples de hash (criptografia)
unsigned long hashSenha(const char* senha) {
    unsigned long hash = 5381;
    int c;
    while ((c = *senha++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

void registrarNomes(char nomes[][MAX_TAMANHO_NOME], int *totalNomes) {
    char resposta;
    do {
        limparTela();
        if (*totalNomes >= MAX_NOMES) {
            printf("Limite máximo de registros atingido.\n");
            Sleep(2000);
            return;
        }
        char nome[MAX_TAMANHO_NOME];
        char cpf[40];
        char cargo[40];
        char arquivo[40];

        printf("Digite o CPF a ser cadastrado: \n");
        scanf("%s", cpf);
        
        strcpy(arquivo, cpf);
        FILE *file = fopen(arquivo, "w");
        if (file) {
            fprintf(file, "%s,", cpf);
            fclose(file);
        }

        printf("\nDigite o nome completo a ser cadastrado: \n");
        scanf(" %[^\n]s", nome);
        
        file = fopen(arquivo, "a");
        if (file) {
            fprintf(file, "%s,", nome);
            fclose(file);
        }

        printf("\nDigite o cargo a ser cadastrado: \n");
        scanf("%s", cargo);
        
        file = fopen(arquivo, "a");
        if (file) {
            fprintf(file, "%s", cargo);
            fclose(file);
        }

        strcpy(nomes[*totalNomes], nome);
        (*totalNomes)++;

        printf("\nNome registrado com sucesso!\n");

        printf("\nDeseja registrar mais um nome? \n1 - Sim \n2 - Não\n");
        scanf(" %c", &resposta);
    } while (resposta == '1');
}

void consultarNomes() {
    setlocale(LC_ALL, "Portuguese");
    char cpf[40];
    char arquivo[40];
    char buffer[255];
    char resposta;

    do {
        limparTela();
        printf("Digite o CPF a ser consultado: \n");
        scanf("%s", cpf);
        
        strcpy(arquivo, cpf);
        FILE *file = fopen(arquivo, "r");
        if (file == NULL) {
            printf("\nRegistro não encontrado.\n");
            Sleep(2000);
            continue;
        }

        printf("\nInformações do registro:\n");
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            char *token = strtok(buffer, ",");
            printf("CPF: %s\n", token);

            token = strtok(NULL, ",");
            printf("Nome: %s\n", token);

            token = strtok(NULL, ",");
            printf("Cargo: %s\n", token);
        }
        fclose(file);

        printf("\nDeseja consultar mais um registro? \n1 - Sim \n2 - Não\n");
        scanf(" %c", &resposta);
    } while (resposta == '1');
}

void deletarRegistro(char nomes[][MAX_TAMANHO_NOME], int *totalNomes) {
    char cpf[40];
    char arquivo[40];
    char resposta;

    do {
        limparTela();
        printf("Digite o CPF do registro a ser deletado: \n");
        scanf("%s", cpf);
        
        strcpy(arquivo, cpf);
        FILE *file = fopen(arquivo, "r");
        
        if (file == NULL) {
            printf("\nRegistro não encontrado.\n");
            Sleep(2000);
            return;
        }
        
        printf("\nInformações do registro:\n");
        char buffer[255];
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            char *token = strtok(buffer, ",");
            printf("CPF: %s\n", token);

            token = strtok(NULL, ",");
            printf("Nome: %s\n", token);

            token = strtok(NULL, ",");
            printf("Cargo: %s\n", token);
        }
        fclose(file);

        printf("\nDeseja realmente deletar este registro? \n1 - Sim \n2 - Não\n ");
        scanf(" %c", &resposta);
        
        if (resposta == '1') {
            if (remove(arquivo) == 0) {
                printf("\nRegistro deletado com sucesso!\n");
            } else {
                printf("\nErro ao deletar o registro.\n");
            }
        } else {
            printf("\nOperação de deletar cancelada.\n");
        }
        printf("\nDeseja deletar mais um registro? \n1 - Sim \n2 - Não\n");
        scanf(" %c", &resposta);
    } while (resposta == '1');
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    system("color 3f");

    int totalNomes = 0;
    int escolha = 0;
    char nomes[MAX_NOMES][MAX_TAMANHO_NOME];
    char senhadigitada[100];
    unsigned long hashSenhaCorreta = hashSenha("admin");
    int tentativas = 0;

    while (tentativas < MAX_TENTATIVAS) {
    	limparTela();
        printf("\t___ Cartório da EBAC ___\n\n");
        printf("Login de administrador\n\nDigite a sua senha:\n");
        lerSenha(senhadigitada, sizeof(senhadigitada));

        if (hashSenha(senhadigitada) == hashSenhaCorreta) {
            while (1) {
                limparTela();
                printf("\t___ Cartório da EBAC ___\n\n");
                printf("Escolha a opção desejada:\n\n");
                printf("\t1 - Registrar nomes\n");
                printf("\t2 - Consultar nomes\n");
                printf("\t3 - Deletar nomes\n");
                printf("\t4 - Sair do sistema\n\n");
                printf("Esse software é feito por Bianca Pessin Avelino, uma aplicação de uso livre.\n");
                printf("Software feito através dos ensinamentos do curso da EBAC\n");
                printf("____________________________________________________________________\n");
                printf("Insira uma opção: ");
                scanf("%d", &escolha);

                if (escolha < 1 || escolha > 4) {
                    printf("Opção inválida. Tente novamente.\n");
                    Sleep(2000);
                    continue;
                }

                switch (escolha) {
                    case 1:
                        limparTela();
                        registrarNomes(nomes, &totalNomes);
                        break;
                    case 2:
                        limparTela();
                        consultarNomes();
                        break;
                    case 3:
                        limparTela();
                        deletarRegistro(nomes, &totalNomes);
                        break;
                    case 4:
                        limparTela();
                        printf("Obrigado por utilizar o sistema!");
                        return 0;
                }
            }
        } else {
        	limparTela();
            tentativas++;
            printf("Senha incorreta. Tentativas restantes: %d\n", MAX_TENTATIVAS - tentativas);
            Sleep(2000);
        }
    }

    printf("Número máximo de tentativas alcançado. Saindo do sistema.\n");
    return 0;
}

