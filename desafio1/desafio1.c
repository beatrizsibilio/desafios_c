#include <stdio.h>
#include <locale.h>

char produto1[20], produto2[20], produto3[20], produto_pqsa[20];
int qtd1, qtd2, qtd3;

void limpar_tela() {
    system("cls || clear");
}

void exibir_produto(int num_produto) {
     if(num_produto == 1){
        printf("\nProduto: %s\n", produto1);
        printf("Quantidade: %d\n", qtd1);
    }

    if(num_produto == 2){
        printf("\nProduto: %s\n", produto2);
        printf("Quantidade: %d\n", qtd2);
    }

    if(num_produto == 3){
        printf("\nProduto: %s\n", produto3);
        printf("Quantidade: %d\n", qtd3);
    }
}

int verificar_existencia() {
    int i, produto_existente = 0;

    for(i=0; produto_pqsa[i] != '\0' ; i++){
        if(produto_pqsa[i] != produto1[i]){
            break;
        }
    }
    if(produto_pqsa[i] == '\0' && produto1[i] == '\0'){
        produto_existente = 1;
        return 1;
    }

    for(i=0; produto_pqsa[i] != '\0' ; i++){
        if(produto_pqsa[i] != produto2[i]){
            break;
        }
    }
    if(produto_pqsa[i] == '\0' && produto2[i] == '\0'){
        produto_existente = 1;
        return 2;
    }

    for(i=0; produto_pqsa[i] != '\0' ; i++){
        if(produto_pqsa[i] != produto3[i]){
            break;
        }
    }
    if(produto_pqsa[i] == '\0' && produto3[i] == '\0'){
        produto_existente = 1;
        return 3;
    }

    if(produto_existente == 0) {
        printf("\nVocê pesquisou por um produto inexistente!\n");
    }
}

int produto_eh_igual() {
    int i, produto_igual = 0;

    for(i=0; produto1[i] != '\0' ; i++){
        if(produto1[i] != produto2[i]){
            break;
        }
    }
    if(produto1[i] == '\0' && produto2[i] == '\0'){
        produto_igual = 1;
    }

    for(i=0; produto1[i] != '\0' ; i++){
        if(produto1[i] != produto3[i]){
            break;
        }
    }
    if(produto1[i] == '\0' && produto3[i] == '\0'){
        produto_igual = 1;
    }

    for(i=0; produto2[i] != '\0' ; i++){
        if(produto2[i] != produto3[i]){
            break;
        }
    }
    if(produto2[i] == '\0' && produto3[i] == '\0'){
        produto_igual = 1;
    }

    if(produto_igual) {
        printf("\nVocê digitou um produto que já existe, tente novamente!\n");
    }

    return produto_igual;
}

void cadastrar_dados() {

    FILE *arquivo;

    arquivo = fopen("produtos.bin", "w");

    printf("CADASTRAR PRODUTOS\n");

    printf("Digite o nome do 1º produto: ");
    gets(produto1);
    printf("Digite a quantidade do 1º produto: ");
    scanf("%d", &qtd1);
    fwrite(produto1, sizeof(produto1), 1, arquivo);
    fwrite(&qtd1, sizeof(qtd1), 1, arquivo);

    do{
        printf("\nDigite o nome do 2º produto: ");
        getchar();
        gets(produto2);
        printf("Digite a quantidade do 2º produto: ");
        scanf("%d", &qtd2);
        fwrite(produto2, sizeof(produto2), 1, arquivo);
        fwrite(&qtd2, sizeof(qtd2), 1, arquivo);
        } while(produto_eh_igual());

    do{
        printf("\nDigite o nome do 3º produto: ");
        getchar();
        gets(produto3);
        printf("Digite a quantidade do 3º produto: ");
        scanf("%d", &qtd3);
        fwrite(produto3, sizeof(produto3), 1, arquivo);
        fwrite(&qtd3, sizeof(qtd3), 1, arquivo);

    } while(produto_eh_igual());

     if(arquivo != NULL){
        printf("\nArquivo criado com sucesso!");
    }else{
         printf("\nERRO: O arquivo nao pôde ser aberto");
         system("pause");
         exit(1);
    }

    fclose(arquivo);
    printf("\nTecle ENTER para retornar ao menu!");
    getchar();
    getchar();
}

void listar_dados() {
    printf("LISTA DE PRODUTOS\n");

     FILE *arquivo;

    arquivo = fopen("produtos.bin", "r");

        fread(produto1, sizeof(produto1), 1, arquivo);
        fread(&qtd1, sizeof(qtd1), 1, arquivo);
        fread(produto2, sizeof(produto2), 1, arquivo);
        fread(&qtd2, sizeof(qtd2), 1, arquivo);
        fread(produto3, sizeof(produto3), 1, arquivo);
        fread(&qtd3, sizeof(qtd3), 1, arquivo);

        fclose(arquivo);

    if(produto1[0] != '*') {
        exibir_produto(1);
    }
    if(produto2[0] != '*') {
        exibir_produto(2);
    }
    if(produto3[0] != '*') {
        exibir_produto(3);
    }

    if(arquivo != NULL){
        printf("\nArquivo aberto com sucesso!");
    }else{
         printf("ERRO: O arquivo nao pôde ser aberto");
         system("pause");
         exit(1);
    }

    printf("\nTecle ENTER para retornar ao menu!");
    getchar();
}

void pesquisar_por_nome() {
    int num_produto;

    FILE *arquivo;

    arquivo = fopen("produtos.bin", "r");

    fread(produto1, sizeof(produto1), 1, arquivo);
    fread(&qtd1, sizeof(qtd1), 1, arquivo);
    fread(produto2, sizeof(produto2), 1, arquivo);
    fread(&qtd2, sizeof(qtd2), 1, arquivo);
    fread(produto3, sizeof(produto3), 1, arquivo);
    fread(&qtd3, sizeof(qtd3), 1, arquivo);

    fclose(arquivo);


    printf("BUSCAR PRODUTO POR NOME\n");
    printf("\nDigite o nome do produto deseja buscar: ");
    gets(produto_pqsa);

    num_produto = verificar_existencia();

    exibir_produto(num_produto);

    if(arquivo != NULL){
        printf("\nArquivo aberto com sucesso!");
    }else{
         printf("ERRO: O arquivo nao pôde ser aberto");
         system("pause");
         exit(1);
    }

    printf("\nTecle ENTER para retornar ao menu!");
    getchar();
}

void pesquisar_por_letra() {
    char primeira_letra, num_produto = 0;

    FILE *arquivo;

    arquivo = fopen("produtos.bin", "r");

    fread(produto1, sizeof(produto1), 1, arquivo);
    fread(&qtd1, sizeof(qtd1), 1, arquivo);
    fread(produto2, sizeof(produto2), 1, arquivo);
    fread(&qtd2, sizeof(qtd2), 1, arquivo);
    fread(produto3, sizeof(produto3), 1, arquivo);
    fread(&qtd3, sizeof(qtd3), 1, arquivo);

    fclose(arquivo);


    printf("BUSCAR PRODUTOS PELA PRIMEIRA LETRA\n");
    printf("\nDigite a primeira letra do produto desejado: ");
    primeira_letra = getchar();
    getchar();

    if(primeira_letra == produto1[0]){
        num_produto = 1;
        exibir_produto(num_produto);
    }
    if(primeira_letra == produto2[0]){
        num_produto = 2;
        exibir_produto(num_produto);
    }
    if(primeira_letra == produto3[0]){
        num_produto = 3;
        exibir_produto(num_produto);
    }

    if(num_produto == 0) {
        printf("\nNenhum produto corresponde a primeira letra digitada!\n");
    }

    if(arquivo != NULL){
        printf("\nArquivo aberto com sucesso!");
    }else{
         printf("ERRO: O arquivo nao pôde ser aberto");
         system("pause");
         exit(1);
    }

    printf("\nTecle ENTER para retornar ao menu!");
    getchar();
}

void alterar_dados() {
    int num_produto;

    FILE *arquivo;

    arquivo = fopen("produtos.bin", "r");

    fread(produto1, sizeof(produto1), 1, arquivo);
    fread(&qtd1, sizeof(qtd1), 1, arquivo);
    fread(produto2, sizeof(produto2), 1, arquivo);
    fread(&qtd2, sizeof(qtd2), 1, arquivo);
    fread(produto3, sizeof(produto3), 1, arquivo);
    fread(&qtd3, sizeof(qtd3), 1, arquivo);

    fclose(arquivo);

    printf("ALTERAR DADOS\n");
    printf("\nDigite o nome do produto deseja alterar: ");
    gets(produto_pqsa);

    num_produto = verificar_existencia();

    if(num_produto == 1){
        exibir_produto(num_produto);

        printf("\nDigite o novo nome do produto: ");
        gets(produto1);

        printf("Digite a nova quantidade do produto: ");
        scanf("%d", &qtd1);
    }

    if(num_produto == 2){
        exibir_produto(num_produto);

        printf("\nDigite o novo nome do produto: ");
        gets(produto2);

        printf("Digite a nova quantidade do produto: ");
        scanf("%d", &qtd2);
    }

    if(num_produto == 3){
        exibir_produto(num_produto);

        printf("\nDigite o novo nome do produto: ");
        gets(produto3);

        printf("Digite a nova quantidade do produto: ");
        scanf("%d", &qtd3);
    }


    arquivo = fopen("produtos.bin", "w");

    fwrite(produto1, sizeof(produto1), 1, arquivo);
    fwrite(&qtd1, sizeof(qtd1), 1, arquivo);

    fwrite(produto2, sizeof(produto2), 1, arquivo);
    fwrite(&qtd2, sizeof(qtd2), 1, arquivo);

    fwrite(produto3, sizeof(produto3), 1, arquivo);
    fwrite(&qtd3, sizeof(qtd3), 1, arquivo);

    if(arquivo != NULL){
        printf("\nArquivo alterado com sucesso!");
    }else{
        printf("\nERRO: O arquivo nao pôde ser aberto");
        system("pause");
        exit(1);
    }

    fclose(arquivo);

    printf("\nTecle ENTER para retornar ao menu!");
    getchar();
    getchar();
}

void excluir_dados() {
    int num_produto, excluido = 0;

    FILE *arquivo;

    arquivo = fopen("produtos.bin", "r");

    fread(produto1, sizeof(produto1), 1, arquivo);
    fread(&qtd1, sizeof(qtd1), 1, arquivo);
    fread(produto2, sizeof(produto2), 1, arquivo);
    fread(&qtd2, sizeof(qtd2), 1, arquivo);
    fread(produto3, sizeof(produto3), 1, arquivo);
    fread(&qtd3, sizeof(qtd3), 1, arquivo);

    fclose(arquivo);


    printf("EXCLUIR DADOS\n");
    printf("\nDigite o nome do produto deseja excluir: ");
    gets(produto_pqsa);

    num_produto = verificar_existencia();

    if(num_produto == 1) {
        exibir_produto(num_produto);
        produto1[0] = '*';
        excluido = 1;
    }

    if(num_produto == 2) {
        exibir_produto(num_produto);
        produto2[0] = '*';
        excluido = 1;
    }

    if(num_produto == 3) {
        exibir_produto(num_produto);
        produto3[0] = '*';
        excluido = 1;
    }

    if(excluido) {
        printf("\nProduto excluído com sucesso!");
    }

    arquivo = fopen("produtos.bin", "w");

    fwrite(produto1, sizeof(produto1), 1, arquivo);
    fwrite(&qtd1, sizeof(qtd1), 1, arquivo);

    fwrite(produto2, sizeof(produto2), 1, arquivo);
    fwrite(&qtd2, sizeof(qtd2), 1, arquivo);

    fwrite(produto3, sizeof(produto3), 1, arquivo);
    fwrite(&qtd3, sizeof(qtd3), 1, arquivo);

    if(arquivo != NULL){
        printf("\nArquivo alterado com sucesso!");
    }else{
        printf("\nERRO: O arquivo nao pôde ser aberto");
        system("pause");
        exit(1);
    }

    fclose(arquivo);


    printf("\nTecle ENTER para retornar ao menu!");
    getchar();
}

void sair(){
    exit(0);
}


void main() {
    setlocale(LC_ALL,"Portuguese");
    int opcao;

    while(1) {
        limpar_tela();

        printf("CADASTRO DE PRODUTOS:\n");
        printf("1 - Entrada de dados\n");
        printf("2 - Listar todos os dados na tela\n");
        printf("3 - Pesquisar produto pelo nome completo\n");
        printf("4 - Pesquisar produto pela 1º letra\n");
        printf("5 - Alterar dados\n");
        printf("6 - Excluir dados\n");
        printf("7 - Sair\n");
        printf("\nSelecione a opção desejada: ");
        scanf("%d", &opcao);

        limpar_tela();
        getchar();

        switch(opcao) {
            case 1: {
                cadastrar_dados();
                break;
            }
            case 2: {
                listar_dados();
                break;
            }
            case 3: {
                pesquisar_por_nome();
                break;
            }
            case 4: {
                pesquisar_por_letra();
                break;
            }
            case 5: {
                alterar_dados();
                break;
            }
            case 6: {
                excluir_dados();
                break;
            }
            case 7: {
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
