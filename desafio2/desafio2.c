#include "stdio.h"
#include "locale.h"

struct produto {
    char nome[21];
    int qtd;
    float preco;
    int mes_validade;
    int ano_validade;
};

void limpar_tela(){
    system("cls || clear");
}

void exibir_produto(struct produto *pdados) {
    if(pdados -> nome[0] != '*') {
        printf("\nNome: %s", pdados -> nome);
        printf("\nQuantidade: %d", pdados -> qtd);
        printf("\nPreço: %.2f", pdados -> preco);
        printf("\nValidade: %d/%d\n", pdados -> mes_validade, pdados -> ano_validade);
    }
}

void cadastrar_produto(struct produto *pdados){
    FILE *parquivo;
    parquivo = fopen("produtos.bin", "a");

    printf("CADASTRAR DADOS DO PRODUTO\n");

    printf("\nDigite o nome do produto: ");
    gets(&pdados -> nome);

    printf("Digite a quantidade do produto: ");
    scanf("%d", &pdados -> qtd);

    printf("Digite o preço do produto: ");
    scanf("%f", &pdados -> preco);

    printf("Digite o MÊS da validade do produto: ");
    scanf("%d", &pdados -> mes_validade);

    printf("Digite o ANO da validade do produto: ");
    scanf("%d", &pdados -> ano_validade);

    fwrite(pdados, sizeof(*pdados), 1, parquivo);

    fclose(parquivo);

    getchar();
    printf("\nDigite ENTER para retornar ao menu!");
    getchar();
}

int resultado_leitura_do_arquivo(FILE *parquivo, struct produto *pdados) {
    return fread(pdados, sizeof(*pdados), 1, parquivo);
}

void listar_produtos(struct produto *pdados){
    int leitura_de_dados;
    FILE *parquivo;

    parquivo = fopen("produtos.bin", "r");

    printf("LISTA DE PRODUTOS\n");
    for(;;) {
        if(resultado_leitura_do_arquivo(parquivo, pdados) == 0) {
            break;
        }

        exibir_produto(pdados);
    }

    fclose(parquivo);

    printf("\nDigite ENTER para retornar ao menu!");
    getchar();
}

int verificar_existencia_por_nome(struct produto *pdados, char *pqsa){
    int i, produto_existente = 0;

    for(i = 0; pqsa[i] != '\0' ; i++){
        if(pqsa[i] != pdados -> nome[i]){
            break;
        }
    }
    if(pqsa[i] == '\0' && pdados -> nome[i] == '\0'){
        produto_existente = 1;
    }

    return produto_existente;
}

void pesquisar_por_nome(struct produto *pdados){
    char produto_pqsa[21], *pqsa;
    int leitura_de_dados, produto_existente = 0;
    FILE *parquivo;

    pqsa = &produto_pqsa[0];

    printf("PESQUISAR PRODUTO POR NOME\n");

    printf("\nDigite o nome do produto que deseja pesquisar: ");
    gets(&pqsa[0]);

    parquivo = fopen("produtos.bin", "r");

    while(1) {
        if(resultado_leitura_do_arquivo(parquivo, pdados) == 0) {
            break;
        }

        if(verificar_existencia_por_nome(pdados, pqsa)) {
            exibir_produto(pdados);
            produto_existente = 1;
            break;
        }
    }

    if(produto_existente == 0) {
        printf("\nProduto inexistente!\n");
    }

    fclose(parquivo);

    printf("\nDigite ENTER para retornar ao menu!");
    getchar();
}

void pesquisar_por_validade(struct produto *pdados){
    int mes_val, ano_val, leitura_de_dados, validade_existente;

    FILE *parquivo;

    printf("PESQUISAR PRODUTO POR VALIDADE\n");

    printf("\nDigite o mês da validade do produto que deseja pesquisar: ");
    scanf("%d", &mes_val);
    printf("\nDigite o ano da validade do produto que deseja pesquisar: ");
    scanf("%d", &ano_val);

    parquivo = fopen("produtos.bin", "r");

    while(1) {
        if(resultado_leitura_do_arquivo(parquivo, pdados) == 0) {
            break;
        }

        if((mes_val == pdados -> mes_validade) && (ano_val == pdados -> ano_validade)) {
            exibir_produto(pdados);
            validade_existente = 1;
        }
    }

    if(validade_existente == 0) {
            printf("\nNenhum produto possui essa validade!\n");
    }

    fclose(parquivo);

    getchar();
    printf("\nDigite ENTER para retornar ao menu!");
    getchar();
}

void listar_por_preco(struct produto *pdados){
    int preco_min, preco_max, leitura_de_dados, faixa_existente = 0;

    FILE *parquivo;

    printf("PESQUISAR PRODUTO POR FAIXA DE PREÇO\n");

    printf("\nDigite o valor mínimo do produto que deseja pesquisar: ");
    scanf("%d", &preco_min);
    printf("\nDigite o valor máximo do produto que deseja pesquisar: ");
    scanf("%d", &preco_max);

    parquivo = fopen("produtos.bin", "r");

    while(1) {
        if(resultado_leitura_do_arquivo(parquivo, pdados) == 0) {
            break;
        }

        if((pdados -> preco >= preco_min) && (pdados -> preco <= preco_max)) {
            exibir_produto(pdados);
            faixa_existente = 1;
        }
    }

    if(faixa_existente == 0) {
            printf("\nNenhum produto encontrado nessa faixa de preço!\n");
    }

    fclose(parquivo);

    getchar();
    printf("\nDigite ENTER para retornar ao menu!");
    getchar();
}

void entrada_produtos(struct produto *pdados) {
    int nova_qtd;

    printf("\nENTRADA DE PRODUTOS\n");
    printf("Digite quantos produtos ENTRARAM no estoque de %s: ", pdados -> nome);
    scanf("%d", &nova_qtd);

    pdados -> qtd += nova_qtd;
}

void saida_produtos(struct produto *pdados) {
    int nova_qtd;

    printf("\nSAÍDA DE PRODUTOS\n");
    printf("Digite quantos produtos SAÍRAM do estoque de %s: ", pdados -> nome);
    scanf("%d", &nova_qtd);
    pdados -> qtd -= nova_qtd;
}

void salvar_alteracao(FILE *parquivo, struct produto *pdados, int indice_produto) {
    fseek(parquivo, sizeof(*pdados) * indice_produto, 0);
    fwrite(pdados, sizeof(*pdados), 1, parquivo);
}

void alterar_quantidade(struct produto *pdados){
    char produto_pqsa[21], *pqsa;
    int opcao = 0, produto_existente = 0, indice_produto = 0, continuar = 1;
    FILE *parquivo;

    pqsa = &produto_pqsa[0];

    printf("ALTERAR QUANTIDADE\n");
    printf("\n1 - Entrada produtos\n");
    printf("2 - Saída de produtos\n");
    printf("\nSelecione a modificação que deseja realizar: ");
    scanf("%d", &opcao);
    getchar();

    parquivo = fopen("produtos.bin", "r+");

    if((opcao != 1) && (opcao != 2)) {
        printf("\nVocê digitou uma opção inválida!\n\n");
    } else {
        printf("\nDigite o nome do produto que deseja alterar a quantidade: ");
        gets(&pqsa[0]);

        while(continuar) {
            if(resultado_leitura_do_arquivo(parquivo, pdados) == 0) {
                break;
            }

            if(verificar_existencia_por_nome(pdados, pqsa)) {
                produto_existente = 1;
                limpar_tela();
                printf("ALTERAR QUANTIDADE\n");

                exibir_produto(pdados);

                switch(opcao) {
                    case 1: {
                        entrada_produtos(pdados);
                        break;
                    }
                    case 2: {
                        saida_produtos(pdados);
                        break;
                    }
                }
                salvar_alteracao(parquivo, pdados, indice_produto);
                continuar = 0;
                printf("\nProduto alterado com sucesso!\n");
                getchar();
            } else {
                indice_produto ++;
            }
        }

        if(produto_existente == 0) {
            printf("\nProduto inexistente!\n");
        }
    }

    fclose(parquivo);

    printf("Digite ENTER para retornar ao menu!");
    getchar();
}

void alterar_preco(struct produto *pdados){
    char produto_pqsa[21], *pqsa;
    int produto_existente = 0, indice_produto = 0, continuar = 1;

    FILE *parquivo;

    pqsa = &produto_pqsa[0];

    printf("ALTERAR PREÇO\n");
    printf("\nDigite o nome do produto que deseja alterar o preço: ");
    gets(&pqsa[0]);

    parquivo = fopen("produtos.bin", "r+");

    while(continuar) {
        if(resultado_leitura_do_arquivo(parquivo, pdados) == 0) {
            break;
        }

        if(verificar_existencia_por_nome(pdados, pqsa)) {
            produto_existente = 1;
            limpar_tela();
            printf("ALTERAR PREÇO\n");
            exibir_produto(pdados);

            printf("\nDigite o novo preço do produto %s: ", pdados -> nome);
            scanf("%f", &pdados -> preco);

            salvar_alteracao(parquivo, pdados, indice_produto);
            continuar = 0;

            printf("\nProduto alterado com sucesso!\n");
            getchar();
        } else {
            indice_produto ++;
        }
    }

    fclose(parquivo);

    if(produto_existente == 0) {
        printf("\nProduto inexistente!\n");
    }

    printf("\nDigite ENTER para retornar ao menu!");
    getchar();
}

void alterar_produto(struct produto *pdados){
    char produto_pqsa[21], *pqsa, novo_nome[21];
    int produto_existente = 0, indice_produto = 0, continuar = 1, i = 0, nova_qtd, novo_mes_va, novo_ano_val;
    float novo_preco;
    FILE *parquivo;

    pqsa = &produto_pqsa[0];

    printf("ALTERAR PRODUTO\n");
    printf("\nDigite o nome do produto que deseja alterar: ");
    gets(&pqsa[0]);

    parquivo = fopen("produtos.bin", "r+");

    while(continuar) {
        if(resultado_leitura_do_arquivo(parquivo, pdados) == 0) {
            break;
        }

        if(verificar_existencia_por_nome(pdados, pqsa)) {
            produto_existente = 1;
            limpar_tela();
            exibir_produto(pdados);

            printf("\nDigite o novo nome do produto %s: ", pdados -> nome);
            gets(pdados -> nome);

            printf("Digite a nova quantidade do produto %s: ", pdados -> nome);
            scanf("%d", &pdados -> qtd);

            printf("Digite o novo preço do produto %s: ", pdados -> nome);
            scanf("%f", &pdados -> preco);

            printf("Digite o novo MÊS de validade do produto %s: ", pdados -> nome);
            scanf("%d", &pdados -> mes_validade);

            printf("Digite o novo ANO de validade do produto %s: ", pdados -> nome);
            scanf("%d", &pdados ->ano_validade);

            salvar_alteracao(parquivo, pdados, indice_produto);
            continuar = 0;

            printf("\nProduto alterado com sucesso!\n");
            getchar();
        } else {
            indice_produto ++;
        }
    }

    fclose(parquivo);

    if(produto_existente == 0) {
        printf("\nProduto inexistente!\n");
    }

    printf("\nDigite ENTER para retornar ao menu!");
    getchar();
}

void excluir_produto(struct produto *pdados){
    char produto_pqsa[21], *pqsa;
    int produto_existente = 0, indice_produto = 0, continuar = 1;
    FILE *parquivo;

    pqsa = &produto_pqsa[0];

    printf("EXCLUIR PRODUTO\n");
    printf("\nDigite o nome do produto que deseja excluir: ");
    gets(&pqsa[0]);

    parquivo = fopen("produtos.bin", "r+");

    while(continuar) {
        if(resultado_leitura_do_arquivo(parquivo, pdados) == 0) {
            break;
        }

        if(verificar_existencia_por_nome(pdados, pqsa)) {
            produto_existente = 1;
            exibir_produto(pdados);

            pdados -> nome[0] = '*';

            salvar_alteracao(parquivo, pdados, indice_produto);
            continuar = 0;

            printf("\nProduto excluído com sucesso!");
        } else {
            indice_produto ++;
        }
    }

    fclose(parquivo);

    if(produto_existente == 0) {
        printf("\nProduto inexistente!\n");
    }

    printf("\nDigite ENTER para retornar ao menu!");
    getchar();
}

void sair(){
    exit(0);
}


void main() {
    setlocale(LC_ALL,"Portuguese");
    int opcao = 0;

    static struct produto dados;
    struct produto *pdados;

    pdados = &dados;

    while(1) {
        limpar_tela();

        printf("CADASTRO DE PRODUTOS:\n");
        printf("1 - Entrada de dados do produto\n");
        printf("2 - Listar todos os produtos na tela\n");
        printf("3 - Pesquisar produto pelo nome completo\n");
        printf("4 - Pesquisar produto pela validade (mês/ano)\n");
        printf("5 - Listar produtos pela faixa de preço\n");
        printf("6 - Alterar quantidade em estoque (entrada/saída)\n");
        printf("7 - Alterar preço do produto\n");
        printf("8 - Alterar produto\n");
        printf("9 - Excluir produto\n");
        printf("10 - Sair\n");

        printf("\nSelecione a opção desejada: ");
        scanf("%d", &opcao);

        limpar_tela();
        getchar();

        switch(opcao) {
            case 1: {
                cadastrar_produto(pdados);
                break;
            }
            case 2: {
                listar_produtos(pdados);
                break;
            }
            case 3: {
                pesquisar_por_nome(pdados);
                break;
            }
            case 4: {
                pesquisar_por_validade(pdados);
                break;
            }
            case 5: {
                listar_por_preco(pdados);
                break;
            }
            case 6: {
                alterar_quantidade(pdados);
                break;
            }
            case 7: {
                alterar_preco(pdados);
                break;
            }
            case 8: {
                alterar_produto(pdados);
                break;
            }
            case 9: {
                excluir_produto(pdados);
                break;
            }
            case 10: {
                sair();
                break;
            }
            default: {
                printf("\nVocê digitou uma opção inválida, tecle ENTER para retornar ao menu!\n\n");
                getchar();
            }
        }
    }
}
