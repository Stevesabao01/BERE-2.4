//Contem diversos erros, esperando declaracoes, nao confundir com variaveis(tudo certo esta parte) e a expressao que precisa ser tipo ponteiro, eu resolvi a parte da Matriz e calculei certo, resta apenas inserir expressao certa
/// Inclusão de bibliotecas
#include <stdio.h>// printf e scanf
#include <stdlib.h>// system
#include <locale.h>// acentuação

/// Constantes globais
#define NUM_PRODUTOS 25
#define MAX_QUANTIDADE 100   // Variaveis declaradas com palavras-chaves antes do tipo de dados
#define NUM_SETORES 4
#define SEMEstoque 10

/// Estrutura para armazenar as informacoes de um produto
typedef struct { //armazena todas as Variaveis
    int codigo;
    char nome[50];  // é possível agrupar diferentes tipos de dados, representando as propriedades do produto de forma lógica e acessível.
    float preco; //armazena valores
} Produto;

/// Variaveis globais
Produto produtos[NUM_PRODUTOS] = {
    {1, "Detergente", 1.99},
    {2, "Sabao em po - 1kg", 8.99},
    {3, "Esponja", 1.50},
    {4, "Amaciante - 1Lt", 15.00},
    {5, "Bucha de Pia - kit com 3", 4.99},  //Elementos que armazenam dados acessados e modificados, declarações tem escopo global cujo existe ao ciclo inteiro e sendo de facil acesso em qualquer função
    {6, "Desinfetante - 1Lt", 7.99},
    {7, "Sabao em barra - unidade", 1.00},
    {8, "Cafe", 19.99},
    {9, "Leite de caixa", 5.90},
    {10, "Arroz - 1kg", 4.50},
    {11, "Feijao Preto - 1kg", 8.00},
    {12, "Acucar - 1kg", 5.00},
    {13, "Sal - 1kg", 2.00},
    {14, "Farinha de Trigo - 1kg", 5.00},
    {15, "Pao de Forma", 9.50},
    {16, "Pao Integral", 12.50}, //sem estoque!
    {17, "Pao frances - unidade", 1.90},
    {18, "Sonho", 8.50},
    {19, "Biscoito - kg", 12.50},
    {20, "Pao doce - unidade", 2.50},
    {21, "Salgado - unidade", 17.50},
};
int quantidade[NUM_PRODUTOS] = {0};  //A partir daqui inserimos  os valores das variaveis no vetores para Carrinho de Compras
float carrinho[NUM_PRODUTOS] = {0};
float desconto = 0.1; /// Desconto de 10% para pagamento a vista em dinheiro
float valorGastoPorSetor[NUM_SETORES] = {0};

/// Funcao para exibir o menu principal
void exibirMenuPrincipal() {
    printf("======== MENU PRINCIPAL ========   \n");
    printf("\n=================================\n");
    printf("1. Venda de Produtos\n");
    printf("\n=================================\n");
    printf("2. Carrinho                        \n");
    printf("\n=================================\n");
    printf("3. Pagamento                       \n");
    printf("\n=================================\n");
    printf("4. Sair\n");
}

/// Funcao para exibir o submenu de produtos
void exibirSubmenuProdutos() {    //A funcao void mostra o Submenu de opções via interação com usuario, buscamos simplificar a interface do User facilitando a expansão como add novos produtos e categorias
    printf("======== SUBMENU PRODUTOS =========\n");
    printf(" 1. Limpeza                        \n");
    printf("\n=================================\n");
    printf(" 2. Alimentos                      \n");
    printf("\n=================================\n");
    printf(" 3. Padaria                        \n");
    printf("\n=================================\n");
    printf(" 4. Voltar ao menu principal       \n");
}

/// Funcao para exibir o submenu de limpeza
void exibirSubmenuLimpeza() {
    printf("\n======== SUBMENU LIMPEZA ========\n");
    printf(" 1. Detergente              R$1,99 \n");
    printf("\n=================================\n");
    printf(" 2. Sabao em po - 1kg       R$8,99 \n");
    printf("\n=================================\n");
    printf(" 3. Esponja(Sem Estoque)    R$1,50 \n");  //Exibindo SubmenuLimpeza atraves do void, porem sem estoque
    printf("\n=================================\n");
    printf(" 4. Amaciante               R$15,00\n");
    printf("\n=================================\n");
    printf(" 5. Bucha de Pia - kit c/3  R$4,99 \n");
    printf("\n=================================\n");
    printf(" 6. Desinfetante - 1Lt      R$7,99 \n");
    printf("\n=================================\n");
    printf(" 7. Sabao em Barra          R$1,00 \n");
    printf("\n=================================\n");
    printf(" 8. Voltar ao submenu produtos     \n");
}

/// Funcao para exibir o submenu de alimentos

void exibirSubmenuAlimentos() {
    printf("\n=======SUBMENU ALIMENTOS ========\n");
    printf(" 1. Cafe  - Un               R$5,00\n");
    printf("\n=================================\n");
    printf(" 2. Leite - Un               R$4,50\n");
    printf("\n=================================\n");
    printf(" 3. Arroz - 1kg              R$8,00\n");  //Aqui temos a função de Alimentos onde tem os produtos Cafe, Arroz, Feijao e etc
    printf("\n=================================\n");
    printf(" 4. Feijao Preto - 1kg      R$12,00\n");
    printf("\n=================================\n");
    printf(" 5. Acucar - 1kg             R$5,00\n");
    printf("\n=================================\n");
    printf(" 6. Sal - 1kg                R$2,00\n");
    printf("\n=================================\n");
    printf(" 7. Farinha de Trigo - 1kg   R$5,00\n");
    printf("\n=================================\n");
    printf(" 8. Voltar ao submenu produtos     \n");
}

/// Funcao para exibir o submenu de padaria

void exibirSubmenuPadaria() {

    printf("=========  SUBMENU PADARIA ==========\n");
    printf(" 1. Pao de Forma               R$9,50\n");
    printf("\n===================================\n");
    printf(" 2. Pao Integral(Sem Estoque) R$12,50\n");   //Exibindo SubmenuLimpeza atraves do void, mas não temos Pão Integral
    printf("\n===================================\n");
    printf(" 3. Pao Frances - Un           R$1,90\n");
    printf("\n===================================\n");
    printf(" 4. Sonho                      R$8,50\n");
    printf("\n===================================\n");
    printf(" 5. Biscoito - kg             R$12,50\n");
    printf("\n===================================\n");
    printf(" 6. Pao Doce - Un              R$2,50\n");
    printf("\n===================================\n");
    printf(" 7. Salgado - Un              R$17,50\n");
    printf("\n===================================\n");
    printf(" 8. Voltar ao submenu produtos\n");
}

/// Funcao para exibir o carrinho

void exibirCarrinho() {
    float total = 0;

    printf("=== CARRINHO ===\n");    //Agora comeca a parte mais crucial: Loop de Repeticao que define o Valor Gasto de Produtos para o Usuario
    for (int i = 0; i < NUM_PRODUTOS; i++) {
        if (carrinho[i] > 0) {
            printf("Produto %s: R$%.2f x %d = R$%.2f\n", produtos[i].nome, produtos[i].preco, (int)carrinho[i], produtos[i].preco * carrinho[i]);
            total += produtos[i].preco * carrinho[i];
            valorGastoPorSetor[i / 4] += produtos[i].preco * carrinho[i];
        }
    }
    printf("Total: R$%.2f\n", total);
}

/// Funcao para adicionar um item ao carrinho

void adicionarCarrinho(int produto, int quantidade) {
    carrinho[produto] += quantidade;
}

/// Funcao para exibir o submenu de pagamento

void exibirSubmenuPagamento() {
    printf("======== SUBMENU PAGAMENTO ========\n");
    printf(" 1. Pagamento a vista em dinheiro\n");
    printf(" 2. Pagamento com cartao\n");
}
//adicionei isto 
void func(int *y) {
    printf("O endereco do y eh %p\n", &y); //mostra endereco do y
    /* Exemplo calculo
    int z = y * 2; // multiplicar y por 2 e guardar resultado do z
    printf("O valor do Z eh %d\n", z); //guarda valor do z
    }*/
}
// e isso de declaracao variavel
int main() {
    int x = 10;
    printf("O endereco do x  eh %p \n", &x);
    int y = 10;
    int vetor[10];
    int semEstoque = 0;
    int opcaoSubmenuLimpeza;

   do {
    exibirMenuPrincipal();
    printf("Escolha uma opcao: ");
    scanf("%d", &x);

    switch (x) {
        case 1:
            do {
                exibirSubmenuProdutos();
                printf("Escolha uma opcao: ");
                scanf("%d", &x);

                if (x == 1) {
                   // code to handle the "Limpeza" submenu
                } else if (x == 2) {
                   // code to handle the "Alimentos" submenu
                } else if (x == 3) {
                   // code to handle the "Padaria" submenu
                } else if (x == 4) {
                    break; // exit the inner loop and return to the main menu
                } else {
                    printf("Opcao invalida!\n");
                }
            } while (x!= 4);

            break;
            case 2:
            // code to handle the "Carrinho" option
            break;
            case 3:
            // code to handle the "Pagamento" option
            break;
            case 4:
            printf("Saindo do programa...\n");
            break;
            default:
            printf("Opcao invalida!\n");
        }
    } while (x!= 4);
                        //melhorei a limpeza, deu este erro: 'a expressão precisa ter o tipo de ponteiro-para-objeto, mas tem o tipo "int" '!
                       do {
                    system("cls");
                    exibirSubmenuLimpeza();
                    printf("Escolha uma opção: ");
                    scanf("%d", &opcaoSubmenuLimpeza);

               if (opcaoSubmenuLimpeza >= 1 && opcaoSubmenuLimpeza <= 7) {
               if ((opcaoSubmenuLimpeza == 3 && semEstoque[0] == 1))  {
                   printf("Produto sem estoque!\n");
                   system("pause");  // Para o usuário ler a mensagem
               } else {
                   printf("Informe a quantidade: ");
                   scanf("%d", &quantidade[opcaoSubmenuLimpeza - 1]); // Ajuste no índice
                   adicionarCarrinho(opcaoSubmenuLimpeza - 1, quantidade[opcaoSubmenuLimpeza - 1]); // Ajuste no índice
               }
            } else if (opcaoSubmenuLimpeza != 8) {
                  printf("Opção inválida!\n");
            }
        } while (opcaoSubmenuLimpeza != 8);
        //limpeza termina aqui!
                 break;
                     else if (x == 2) {
                        do {
                            exibirSubmenuAlimentos();
                            printf("Escolha uma opcao: ");
                            scanf("%d", &x);

                            if (x >= 1 && x <= 7) {
                                printf("Informe a quantidade: ");
                                scanf("%d", &quantidade[x + 6]);
                                adicionarCarrinho(x + 6, quantidade[x + 6]);
                            } else if (x != 8) {
                                printf("Opcao invalida!\n");
                            }
                        } while (x != 8);
                    } else if (x == 3) {
                        do {
                            exibirSubmenuPadaria();
                            printf("Escolha uma opcao: ");
                            scanf("%d", &x);

                            if (x >= 1 && x <= 7 && semEstoque == 0) {
                                printf("Informe a quantidade: ");
                                scanf("%d", &quantidade[x + 13]);
                                adicionarCarrinho(x + 13, quantidade[x + 13]);
                            } else if (x != 8) {
                                printf("Opcao invalida ou sem estoque!\n");
                            }
                        } while (x != 8);
                    } else if (x == 4) {
                        break;
                    } else {
                        printf("Opcao invalida!\n");
                    }
                } while (x != 4);

                break;
            case 2:
                exibirCarrinho();

                break;
            case 3:
                do {
                    printf("Forma de pagamento:\n");
                    printf("1 - Dinheiro\n");
                    printf("2 - Cartão\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &x);

                    if (x == 1) {
                        float total = 0;

                        for (int i = 0; i < NUM_PRODUTOS; i++)
                            total += carrinho[i] * produtos[i].preco;
                        total -= total * desconto;

                        printf("Total a pagar com desconto: R$%.2f\n", total);
                        printf("Valor gasto por setor:\n");
                        for (int i = 0; i < NUM_SETORES; i++) {
                            printf("Setor %d: R$%.2f\n", i + 1, valorGastoPorSetor[i]);
                        }
                    } else if (x == 2) {
                        float total = 0;

                        for (int i = 0; i < NUM_PRODUTOS; i++)
                            total += carrinho[i] * produtos[i].preco;

                        printf("Total a pagar sem desconto: R$%.2f\n", total);
                        printf("Valor gasto por setor:\n");
                        for (int i = 0; i < NUM_SETORES; i++) {
                            printf("Setor %d: R$%.2f\n", i + 1, valorGastoPorSetor[i]);
                        }
                    } else {
                        printf("Opcao invalida!\n");
                    }
                } while (x != 3);

                break;
            case 4:
                printf("Saindo do programa...\n");

                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (x != 4);

    return 0;
}
