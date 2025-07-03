/*
 * Funcionalidades:
 * 1. Cadastrar OF (codigo, item, status)
 * 2. Listar OFs
 * 3. Editar cadastros existentes
 * 4. Excluir cadastros com confirma??o
 */

#include <stdio.h>  // Biblioteca padr?o para entrada e sa?da (ex: printf, scanf)

#define MAX 100  // Define o n?mero m?ximo de cadastros permitidos

// Estrutura que representa uma pessoa com c?digo, nome e idade
struct OFs {
    int codigo;
    char item[50];  // String de at? 49 caracteres + 1 para o caractere '\0' de finaliza??o
    char status[50];
};

// Vetor que armazena at? 100 pessoas
struct OFs OF[MAX];
// Vari?vel que armazena quantas pessoas j? foram cadastradas
int qtd = 0;

// Fun??o que cadastra uma nova pessoa
void cadastrar() {
    // Verifica se o limite de cadastros foi atingido
    if (qtd >= MAX) {
        printf("\nLimite de pessoas atingido (%d cadastros)!\n", MAX);
        return; // Encerra a fun??o
    }

    printf("\n--- NOVO CADASTRO ---\n");

    // Pede os dados da pessoa: c?digo, nome e idade
    printf("Codigo: ");
    scanf("%d", &OF[qtd].codigo);
    while(getchar() != '\n'); // Limpa o "lixo" do buffer do teclado

    printf("Item: ");
    scanf(" %49[^\n]", OF[qtd].item); // L? at? 49 caracteres com espa?os

    printf("Status: ");
    scanf(" %49[^\n]", OF[qtd].status);

    // Aumenta o n?mero de pessoas cadastradas
    qtd++;

    printf("\nCadastro realizado com sucesso!\n");
}

// Fun??o que busca uma pessoa pelo c?digo informado
int buscarPorCodigo(int codigo) {
    int i;
    for (i = 0; i < qtd; i++) {
        if (OF[i].codigo == codigo) {
            return i; // Retorna o ?ndice da pessoa no vetor
        }
    }
    return -1; // Retorna -1 se n?o encontrou
}

// Fun??o que edita os dados de uma pessoa
void editar() {
    int codigo, index;

    printf("\n--- EDITAR CADASTRO ---\n");
    printf("Digite o codigo da OF: ");
    scanf("%d", &codigo);

    // Procura a pessoa com o c?digo digitado
    index = buscarPorCodigo(codigo);

    // Se n?o encontrar, avisa e retorna
    if (index == -1) {
        printf("\nOF nao encontrada!\n");
        return;
    }

    // Mostra os dados atuais
    printf("\nEDITANDO CADASTRO:\n");
    printf("Codigo: %d\n", OF[index].codigo);
    printf("Item atual: %s\n", OF[index].item);
    printf("Status atual: %s\n\n", OF[index].status);

    // Pede os novos dados
    printf("Novo item: ");
    scanf(" %49[^\n]", OF[index].item);

    printf("Nova status: ");
    scanf("%s", &OF[index].status);

    printf("\nCadastro atualizado com sucesso!\n");
}

// Fun??o que exclui uma pessoa do sistema
void excluir() {
    int codigo, index;
    char confirmacao;

    printf("\n--- EXCLUIR CADASTRO ---\n");
    printf("Digite o codigo da OF: ");
    scanf("%d", &codigo);

    index = buscarPorCodigo(codigo);

    if (index == -1) {
        printf("\nOF nao encontrada!\n");
        return;
    }

    // Mostra os dados da of e pede confirma??o
    printf("\nCONFIRMAR EXCLUSAO:\n");
    printf("Codigo: %d\n", OF[index].codigo);
    printf("Item: %s\n", OF[index].item);
    printf("Status: %s\n", OF[index].status);

    printf("\nTem certeza que deseja excluir? (s/n): ");
    scanf(" %c", &confirmacao);

    // Se confirmar, remove a pessoa do vetor e ajusta a quantidade
    if (confirmacao == 's' || confirmacao == 'S') {
        int i;
        for (i = index; i < qtd - 1; i++) {
            OF[i] = OF[i + 1]; // Desloca os dados para "tapar o buraco"
        }
        qtd--; // Diminui a quantidade total
        printf("\nCadastro excluido com sucesso!\n");
    } else {
        printf("\nOperacao cancelada.\n");
    }
}

// Fun??o que lista todas as pessoas cadastradas
void listar() {
    printf("\n--- OF CADASTRADAS ---\n");
    printf("Total: %d\n\n", qtd);

    if (qtd == 0) {
        printf("Nenhuma OF cadastrada.\n");
        return;
    }

    // Cabe?alho da tabela
    printf("CODIGO  ITEM%-42s STATUS\n", "");
    printf("--------------------------------------------------\n");

    // Mostra os dados de cada pessoa
    int i;
    for (i = 0; i < qtd; i++) {
        printf("%-8d%-45s%-45s\n",
               OF[i].codigo,
               OF[i].item,
               OF[i].status);
    }
}

// Fun??o principal (ponto de entrada do programa)
int main() {
    int op;

    printf("\n----------------------------------------");
    printf("\n    SISTEMA DE CADASTRO DE OF");
    printf("\n----------------------------------------\n");

    // Loop principal do menu
    do {
        printf("\n----------- MENU PRINCIPAL -----------\n");
        printf("1. Cadastrar nova OF\n");
        printf("2. Listar todas as OF\n");
        printf("3. Editar cadastro existente\n");
        printf("4. Excluir cadastro\n");
        printf("0. Sair do sistema\n");
        printf("--------------------------------------\n");
        printf("Opcao: ");
        scanf("%d", &op);
        while(getchar() != '\n'); // Limpa o buffer do teclado

        // Executa a op??o escolhida
        switch (op) {
            case 1: cadastrar(); break;
            case 2: listar(); break;
            case 3: editar(); break;
            case 4: excluir(); break;
            case 0: printf("\nEncerrando sistema...\n"); break;
            default: printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while (op != 0); // Repete at? o usu?rio escolher sair

    printf("\nObrigado por utilizar o sistema!\n");
    return 0; // Finaliza o programa
}

