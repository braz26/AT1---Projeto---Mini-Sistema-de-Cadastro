#include <stdio.h>
#include <string.h>

#define MAX 20 // capacidade máxima de registros

void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // consome os caracteres restantes da linha
    }
}

int main(void) {
    // Vetores relacionados: a mesma posição representa o mesmo produto.
    // Ex.: codigo[1], nome[1], preco[1] e quantidade[1] são o mesmo registro.
    int codigo[MAX];
    char nome[MAX][50];
    float preco[MAX];
    int quantidade[MAX];
    int total = 0;       // quantos registros válidos existem agora
    int i;               // contador dos laços
    int posicao;         // posição encontrada numa busca (-1 = não encontrou)
    int codigoBusca;     // código digitado pelo usuário
    int c;               // auxiliar para limpar o buffer do teclado
    int opcao;           // opção escolhida no menu

    do {
        printf("\n1 - Cadastrar");
        printf("\n2 - Consultar");
        printf("\n3 - Listar");
        printf("\n4 - Alterar");
        printf("\n5 - Excluir");
        printf("\n0 - Sair");
        printf("\nEscolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            // Se o usuário digitar letra ou valor inválido, trata como opção inválida.
            printf("Opcao invalida!\n");
            limparBuffer();
            opcao = -1;
        }

        switch (opcao) {
            case 1:
                printf("\n -- CADASTRAR PRODUTO --\n");

                if (total >= MAX) {
                    printf("Limite maximo de cadastros atingido.\n");
                } else {
                    printf("Codigo: ");
                    if (scanf("%d", &codigoBusca) != 1) {
                        printf("Codigo invalido.\n");
                        limparBuffer();
                        break;
                    }

                    // o código identifica o produto, então ele não pode e não deve se repetir.
                    posicao = -1;
                    for (i = 0; i < total; i++) {
                        if (codigo[i] == codigoBusca) {
                            posicao = i;
                            break;
                        }
                    }

                    if (posicao != -1) {
                        printf("Ja existe um produto com esse codigo\n");
                    } else {
                        codigo[total] = codigoBusca;

                        printf("Nome: ");
                        scanf(" %49[^\n]", nome[total]);
                        // lê o nome inteiro e aceita espaços
                        // limita a 49 caracteres para não estourar o vetor

                        printf("Preco (use ponto, ex.: 3.50): ");
                        scanf("%f", &preco[total]);

                        printf("Quantidade: ");
                        scanf("%d", &quantidade[total]);

                        total++; // só incrementa após o cadastro ser concluído
                        printf("Produto cadastrado com sucesso!\n");
                    }
                }
                break;

            case 2:
                printf("\n -- CONSULTAR PRODUTO --\n");
                printf("Codigo do produto: ");
                if (scanf("%d", &codigoBusca) != 1) {
                    printf("Codigo invalido.\n");
                    limparBuffer();
                    break;
                }

                posicao = -1;
                for (i = 0; i < total; i++) {
                    if (codigo[i] == codigoBusca) {
                        posicao = i;
                        break;
                    }
                }

                if (posicao == -1) {
                    printf("Registro nao encontrado.\n");
                } else {
                    printf("\nCodigo: %d", codigo[posicao]);
                    printf("\nNome: %s", nome[posicao]);
                    printf("\nPreco: %.2f", preco[posicao]);
                    printf("\nQuantidade: %d\n", quantidade[posicao]);
                }
                break;

            case 3:
                printf("\n -- LISTAR PRODUTOS --\n");

                if (total == 0) {
                    printf("Nenhum registro cadastrado.\n");
                } else {
                    // Percorre de 0 até total - 1: as posições a partir de
                    // total ainda não foram preenchidas (têm lixo de memória).
                    for (i = 0; i < total; i++) {
                        printf("\nCodigo: %d", codigo[i]);
                        printf("\nNome: %s", nome[i]);
                        printf("\nPreco: %.2f", preco[i]);
                        printf("\nQuantidade: %d\n", quantidade[i]);
                    }
                }
                break;

            case 4:
                printf("\n -- ALTERAR PRODUTO --\n");
                printf("Codigo do produto: ");
                if (scanf("%d", &codigoBusca) != 1) {
                    printf("Codigo invalido.\n");
                    limparBuffer();
                    break;
                }

                // primeiro) localizar a posição (igual à consulta)
                posicao = -1;
                for (i = 0; i < total; i++) {
                    if (codigo[i] == codigoBusca) {
                        posicao = i;
                        break;
                    }
                }

                if (posicao == -1) {
                    printf("Registro nao encontrado.\n");
                } else {
                    printf("Dados atuais -> Nome: %s | Preco: %.2f | Quantidade: %d\n",
                           nome[posicao], preco[posicao], quantidade[posicao]);

                    // segundo) gravar os novos valores na MESMA posição.
                    // o codigo é o identificador, por isso ele não muda
                    printf("Novo nome: ");
                    scanf(" %49[^\n]", nome[posicao]);

                    printf("Novo preco: ");
                    scanf("%f", &preco[posicao]);

                    printf("Nova quantidade: ");
                    scanf("%d", &quantidade[posicao]);

                    printf("Produto alterado com sucesso!\n");
                }
                break;

            case 5:
                printf("\n -- EXCLUIR PRODUTO --\n");
                printf("Codigo do produto: ");
                if (scanf("%d", &codigoBusca) != 1) {
                    printf("Codigo invalido.\n");
                    limparBuffer();
                    break;
                }

                posicao = -1;
                for (i = 0; i < total; i++) {
                    if (codigo[i] == codigoBusca) {
                        posicao = i;
                        break;
                    }
                }

                if (posicao == -1) {
                    printf("Nao foi possivel excluir.\n");
                } else {
                    // Desloca os elementos seguintes uma posição para trás,
                    // em TODOS os vetores, para manter os registros alinhados.
                    for (i = posicao; i < total - 1; i++) {
                        codigo[i] = codigo[i + 1];
                        strcpy(nome[i], nome[i + 1]);
                        preco[i] = preco[i + 1];
                        quantidade[i] = quantidade[i + 1];
                    }
                    total--; // diminui o total de registros válidos
                    printf("Produto excluido com sucesso!\n");
                }
                break;

            case 0:
                printf("Saindo e encerrando o programa...\n");
                break;

            default:
                printf("\nOpcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}




