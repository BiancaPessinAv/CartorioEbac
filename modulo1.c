//Declaração de biblioteca
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <string.h>

// Definição de constantes
#define MAX_NOMES 100
#define MAX_TAMANHO_NOME 100

// Função para limpar a tela
void limparTela() {
    system("cls");
}

// Função para registrar usuários no sistema
void registrarNomes(char nomes[][MAX_TAMANHO_NOME], int *totalNomes) {
    char resposta;
    do {
        limparTela();//limpa a tela antes do processamento
        if (*totalNomes >= MAX_NOMES) {//valida se a quantidade de usuários cadastrados não atingiu seu limite
            printf("Limite máximo de registros atingido.\n");
            Sleep(2000);
            return;
        }
		//Declaração de váriaveis
        char nome[MAX_TAMANHO_NOME];
        char cpf[40];
        char cargo[40];
        char arquivo[40];

        printf("Digite o CPF a ser cadastrado: \n");
        scanf("%s", cpf);
        
        strcpy(arquivo, cpf); //Transfere o valor do CPF informado para a váriavel arquivo
        FILE *file = fopen(arquivo, "w");//Cria um arquivo com o nome (CPF) informado
        if (file) {
            fprintf(file, "%s,", cpf);//Guarda o CPF informado dentro do arquivo
            fclose(file);
        }

        printf("\nDigite o nome completo a ser cadastrado: \n");
        scanf(" %[^\n]s", nome);
        
        file = fopen(arquivo, "a");//Abre o arquivo já criado
        if (file) {
            fprintf(file, "%s,", nome);//Registra o nome informado no arquivo
            fclose(file);
        }

        printf("\nDigite o cargo a ser cadastrado: \n");
        scanf("%s", cargo);
        
        file = fopen(arquivo, "a");//Abre o arquivo já criado
        if (file) {
            fprintf(file, "%s", cargo);//Registra o cargo informado no arquivo
            fclose(file);
        }

        strcpy(nomes[*totalNomes], nome);
        (*totalNomes)++;//Aumenta o total de nomes registrados

        printf("\nNome registrado com sucesso!\n");

        printf("\nDeseja registrar mais um nome? \n1 - Sim \n2 - Não\n");
        scanf(" %c", &resposta);
    } while (resposta == '1');//Repete a função caso a resposta seja sim
}

// Função para consultar nomes a partir do CPF
void consultarNomes() {
    setlocale(LC_ALL, "Portuguese");
    char cpf[40];
    char arquivo[40];
    char buffer[255];
    char resposta;

    do {
        limparTela();//Limpa a tela antes de começar a função
        printf("Digite o CPF a ser consultado: \n");
        scanf("%s", cpf);
        
        strcpy(arquivo, cpf);//Copia o nome do CPF inforamdo para a váriavel arquivo
        FILE *file = fopen(arquivo, "r");//Lê o arquivo com o nome (CPF) informado
        if (file == NULL) {//Caso o arquivo não exista
            printf("\nRegistro não encontrado.\n");
            Sleep(2000);
            continue;
        }

        printf("\nInformações do registro:\n");
        while (fgets(buffer, sizeof(buffer), file) != NULL) {//Exibe as informações registradas no arquivo
            char *token = strtok(buffer, ",");
            printf("CPF: %s\n", token);

            token = strtok(NULL, ",");
            printf("Nome: %s\n", token);

            token = strtok(NULL, ",");
            printf("Cargo: %s\n", token);
        }
        fclose(file);//Fecha o arquivo

        printf("\nDeseja consultar mais um registro? \n1 - Sim \n2 - Não\n");
        scanf(" %c", &resposta);
    } while (resposta == '1');//Repete a função caso a resposta seja sim
}

// Função para deletar registros
void deletarRegistro(char nomes[][MAX_TAMANHO_NOME], int *totalNomes) {
    char cpf[40];
    char arquivo[40];
    char resposta;

	do {
	    limparTela();//Limpa a tela antes de começar a função
	    printf("Digite o CPF do registro a ser deletado: \n");
	    scanf("%s", cpf);
	    
	    strcpy(arquivo, cpf);//Copia o nome do CPF inforamdo para a váriavel arquivo
	    FILE *file = fopen(arquivo, "r");//Lê o arquivo com o nome (CPF) informado
	    
	    if (file == NULL) {//Caso não exista, exibe o erro e retorna ao menu
	        printf("\nRegistro não encontrado.\n");
	        Sleep(2000);
	        return;
	    }
	    
	    printf("\nInformações do registro:\n");
	    char buffer[255];
	    while (fgets(buffer, sizeof(buffer), file) != NULL) {//Exibe as informações registradas no arquivo
	        char *token = strtok(buffer, ",");
	        printf("CPF: %s\n", token);
	
	        token = strtok(NULL, ",");
	        printf("Nome: %s\n", token);
	
	        token = strtok(NULL, ",");
	        printf("Cargo: %s\n", token);
	    }
	    fclose(file);
	
	    printf("\nDeseja realmente deletar este registro? \n1 - Sim \n2 - Não\n ");//Confirmação do usuário
	    scanf(" %c", &resposta);
	    
	    if (resposta == '1') {//deleta o arquivo caso a resposta seja sim.
	        if (remove(arquivo) == 0) {
	            printf("\nRegistro deletado com sucesso!\n");
	        } else {//Caso de algum erro
	            printf("\nErro ao deletar o registro.\n");
	        }
	    } else {//caso o usuário escreva não
	        printf("\nOperação de deletar cancelada.\n");
	    }
	    printf("\nDeseja deletar mais um registro? \n1 - Sim \n2 - Não\n");
	        scanf(" %c", &resposta);
    } while (resposta == '1');//Repete a função caso a resposta seja sim
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    system("color 3f");

    int totalNomes = 0;
    int escolha = 0;
    char nomes[MAX_NOMES][MAX_TAMANHO_NOME];

    while (1) {//Menu
        limparTela();
        printf("\t___ Cartório da EBAC ___\n\n");
        printf("Escolha a opção desejada:\n\n");
        printf("\t1 - Registrar nomes\n");
        printf("\t2 - Consultar nomes\n");
        printf("\t3 - Deletar nomes\n\n");
        printf("Esse software é feito por Bianca Pessin Avelino, uma aplicação de uso livre.\n");
        printf("Software feito através dos ensinamentos do curso da EBAC\n");
        printf("____________________________________________________________________\n");
        printf("Insira uma opção: ");
        scanf("%d", &escolha);

        if (escolha < 1 || escolha > 3) {//Valida a escolha do usuário
            printf("Opção inválida. Tente novamente.\n");
            Sleep(2000);
            continue;
        }

        switch (escolha) {//Executa a função de acordo com a escolha do usuário
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
        }
    }

    return 0;
}

