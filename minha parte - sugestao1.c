///Inclusão de bibliotecas
#include <stdio.h>// printf e scanf
#include <stdlib.h>// system
#include <locale.h>// acentuação

/// Constantes globais
#define NUM_PRODUTOS 25
#define MAX_QUANTIDADE 100   // Variaveis declaradas com palavras-chaves antes do tipo de dados
#define NUM_SETORES 4          
#define semEstoque 10

/// Estrutura para armazenar as informacoes de um produto
typedef struct {
    int codigo;
    char nome[50];  // é possível agrupar diferentes tipos de dados, representando as propriedades do produto de forma lógica e acessível.
    float preco;
} Produto;

/// Variaveis globais
Produto produtos[NUM_PRODUTOS] = {
    {1, "Detergente", 1.99},
    {2, "Sabao em po - 1kg", 8.99},
    {3, "Esponja", 1.50},
    {4, "Amaciante - 1Lt", 15.00},
    {5, "Bucha de Pia - kit com 3", 4.99},        //Elementos que armazenam dados acessados e modificados, declarações tem escopo global cujo existe ao ciclo inteiro e sendo de facil acesso em qualquer função
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
    printf("=== MENU PRINCIPAL ===\n");
    printf("1. Venda de Produtos\n");   
    printf("2. Carrinho\n");
    printf("3. Pagamento\n");
    printf("4. Sair\n");
}

/// Funcao para exibir o submenu de produtos
void exibirSubmenuProdutos() {    //A funcao void mostra o Submenu de opções via interação com usuario, buscamos simplificar a interface do User facilitando a expansão como add novos produtos e categorias
    printf("======== SUBMENU PRODUTOS ========\n");
    printf(" 1. Limpeza\n");          
    printf(" 2. Alimentos\n");
    printf(" 3. Padaria\n");
    printf(" 4. Voltar ao menu principal\n");
}

/// Funcao para exibir o submenu de limpeza
void exibirSubmenuLimpeza() {
    printf("======== SUBMENU LIMPEZA ========\n");
    printf(" 1. Detergente              R$1,99\n");
    printf(" 2. Sabao em po - 1kg       R$8,99\n");
 if (semEstoque[2] == 1) {
    printf(" 3. Esponja         R$1,50\n");  //Exibindo SubmenuLimpeza atraves do void, porem sem estoque na Esponja e aqui comeca a brincadeira onde a Matriz Bidimensional interfere.
    } else {
        printf(" 3. Esponja         R$1,50 (Sem estoque)\n");
    }
    printf(" 4. Amaciante - 1Lt         R$15,00\n");
    printf(" 5. Bucha de Pia - kit c/3  R$4,99\n");
    printf(" 6. Desinfetante - 1Lt      R$7,99\n");
    printf(" 7. Sabao em Barra          R$1,00\n");
    printf(" 8. Voltar ao submenu produtos\n");
}

/// Funcao para exibir o submenu de alimentos
void exibirSubmenuAlimentos() {
    printf("======== SUBMENU ALIMENTOS ========\n");
    printf(" 1. Cafe                    R$5,00\n");
    printf(" 2. Leite                   R$4,50\n");
    printf(" 3. Arroz - 1kg             R$8,00\n");  //Aqui temos a função de Alimentos onde tem os produtos Cafe, Arroz, Feijao e etc
    printf(" 4. Feijao Preto - 1kg      R$12,00\n");
    printf(" 5. Acucar - 1kg            R$5,00\n");
    printf(" 6. Sal - 1kg               R$2,00\n");
    printf(" 7. Farinha de Trigo - 1kg  R$5,00\n");
    printf(" 8. Voltar ao submenu produtos\n");
}

/// Funcao para exibir o submenu de padaria
void exibirSubmenuPadaria() {
    printf("======== SUBMENU PADARIA ========\n");
    printf(" 1. Pao de Forma         R$9,50\n");
 if (semEstoque[1] == 1) {
     printf(" 2. Pao Integral        R$12,50\n");   //Exibindo SubmenuLimpeza atraves do void, mas não temos Pão Integral, a Matriz Bidimensional interfere novamente.
     } else {
        printf(" 2. Pao Integral     R$12,50(Sem Estoque)\n");
     }
    printf(" 3. Pao Frances - Unid   R$1,90\n");
    printf(" 4. Sonho                R$8,50\n");
    printf(" 5. Biscoito - kg        R$12,50\n");
    printf(" 6. Pao Doce - unidade   R$2,50\n");
    printf(" 7. Salgado - unidade    R$17,50\n");
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

int main() {   //Declaracao de Variaveis Locais e para Entrada do Usuario, usado pra armazenar opcoes selecionada pro usuario em Submenus, sem atribuicao de valor inicial.
    int x = 10;
    int semEstoque[3][0] = 1;     
    int semEstoque[2][0] = 1;
    int escolha, submenuProdutos, submenuLimpeza, submenuAlimentos, submenuPadaria, submenuPagamentos;

    do {   //O loop do-while continua em execucao até que seja digitada uma das opções validas como 8 para Sair ou 4 pra ir rumo outro Submenu
        exibirMenuPrincipal();
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);                 //Ciclo Principal, mostrando Menus e Submenus que permite a interacao
        switch (escolha) {             //do usuario pra adicionar produtos no Carrinho, selecionando opcoes de pagamentos e assim finalizar a compra
            case 1:
                do {
                    system("cls");
                    exibirSubmenuProdutos();             //O codigo mostra informacoes sobre produtos, adicao de produtos, calculos de totais
                    printf("Escolha uma opcao: ");
                    scanf("%d", &submenuProdutos);

                    switch (submenuProdutos) {
                        case 1:
                            do {
                                system("cls");               //Depois que foi processado a escolha, limpa a tela até que decida sair do programa
                                exibirSubmenuLimpeza();
                                printf("Escolha uma opcao: ");
                                scanf("%d", &submenuLimpeza);

                                if (submenuLimpeza >= 1 && submenuLimpeza <= 7) {
                                    printf("Informe a quantidade: ");
                                    scanf("%d", &quantidade[submenuLimpeza - 1]); // Ajuste no índice
                                    adicionarCarrinho(submenuLimpeza - 1, quantidade[submenuLimpeza - 1]); // Ajuste no índice
                                } else if (submenuLimpeza != 8) {
                                    printf("Opcao invalida!\n");
                                }
                            } while (submenuLimpeza != 8);
                            break;
                        case 2:
                            do {
                                system("cls");
                                exibirSubmenuAlimentos();
                                printf("Escolha uma opcao: ");
                                scanf("%d", &submenuAlimentos);

                                if (submenuAlimentos >= 1 && submenuAlimentos <= 7) {
                                    printf("Informe a quantidade: ");
                                    scanf("%d", &quantidade[submenuAlimentos + 6]); // Ajuste no índice
                                    adicionarCarrinho(submenuAlimentos + 6, quantidade[submenuAlimentos + 6]); // Ajuste no índice
                                } else if (submenuAlimentos != 8) {
                                    printf("Opcao invalida!\n");
                                }
                            } while (submenuAlimentos != 8);
                            break;
                        case 3:
                            do {
                                system("cls");
                                exibirSubmenuPadaria();
                                printf("Escolha uma opcao: ");
                                scanf("%d", &submenuPadaria);

                                if (submenuPadaria >= 1 && submenuPadaria <= 7) {
                                    printf("Informe a quantidade: ");
                                    scanf("%d", &quantidade[submenuPadaria + 13]); // Ajuste no índice
                                    adicionarCarrinho(submenuPadaria + 13, quantidade[submenuPadaria + 13]); // Ajuste no índice
                                } else if (submenuPadaria != 8) {
                                    printf("Opcao invalida!\n");
                                }
                            } while (submenuPadaria != 8);
                            break;
                        case 4:
                            break;
                        default:
                            printf("Opcao invalida!\n");
                    }
                } while (submenuProdutos != 4);    //Final do Submenu
                break;
            case 2:
                system("cls");
                exibirCarrinho();
                break;
            case 3:
                do {
                    exibirSubmenuPagamento();
                    printf("Escolha uma opcao: ");
                    scanf("%d", &submenuPagamentos);

                    if (submenuPagamentos == 1) {
                        float total = 0;

                        for (int i = 0; i < NUM_PRODUTOS; i++) {
                            total += carrinho[i] * produtos[i].preco;
                        }

                        total -= total * desconto;
                        printf("Total a pagar com desconto: R$%.2f\n", total);
                        printf("Valor gasto por setor:\n");
                        for (int i = 0; i < NUM_SETORES; i++) {
                            printf("Setor %d: R$%.2f\n", i + 1, valorGastoPorSetor[i]);
                        }
                    } else if (submenuPagamentos == 2) {
                        float total = 0;

                        for (int i = 0; i < NUM_PRODUTOS; i++) {
                            total += carrinho[i] * produtos[i].preco;
                        }

                        printf("Total a pagar sem desconto: R$%.2f\n", total);
                        printf("Valor gasto por setor:\n");
                        for (int i = 0; i < NUM_SETORES; i++) {
                            printf("Setor %d: R$%.2f\n", i + 1, valorGastoPorSetor[i]);
                        }
                    } else if (submenuPagamentos != 3) {
                        printf("Opcao invalida!\n");
                    }
                } while (submenuPagamentos != 3);
                break;                             //O programa encerra de vez, e aparece uma mensagem de Despedida, o que indica o retorno = 0 bem-sucedido
            case 4:
                printf("Saindo do programa...\n");
                break;
            default:                         //Ciclo de interacao entre exibicao de Menus, Submenus, Processamento de escolhas do User e execucao de acoes relacionadas repetem-se até decisao final do usuario
                printf("Opcao invalida!\n");
        }
    } while (escolha != 4);

    return 0;
}