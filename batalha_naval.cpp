# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <string>
# include <iostream>

// Declara funcao para n gerar erro
void Jogo(std::string nome_do_jogador, std::string nome_do_jogador2);

void LimpaTela(){
    system("clear");
    // Or system("CLS");
}

void MenuInicial(){
    int option = 0;
    std::string nome_do_jogador;
    std::string nome_do_jogador2;

    // Laço para opçoes validas
    while (option < 1 || option > 3){
        LimpaTela();
        printf("Welcome to Naval Battle !\n");
        printf("1 - Play\n");
        printf("2 - About\n");
        printf("3 - Exit\n");
        printf("Press one option and type ENTER: ");
        scanf("%d", &option);
    }

    switch (option){
    case 1:
        printf("Player1: ");
        std::cin >> nome_do_jogador;
        printf("Player2: ");
        std::cin >> nome_do_jogador2;
        Jogo(nome_do_jogador, nome_do_jogador2);
        break;
    case 2:
        printf("About this game !\n");
        break;
    case 3:
        printf("Game Over !\n");
        break;
    }
}

void IniciaTabuleiro(char tabuleiro[10][10], char mascara[10][10]){
    // i = linha, j = coluna
    int i, j;
    // Preenchendo o tabuleiro
    for (i = 0; i < 10; i++){
        for (j = 0; j < 10; j++){
            tabuleiro[i][j] = 'A';
            mascara[i][j] = '*';
        }
    }
}

void ExibeMapa(){
    // Indicando colunas (Mapea)
    for (int cont = 0; cont < 10; cont++){
        if (cont == 0){
            printf("    ");
        }
        printf("%d ", cont);
    }
    printf("\n");
    for (int cont = 0; cont < 10; cont++){
        if (cont == 0){
            printf("    ");
        }
        printf("| ");
    }
    printf("\n");
}

void ExibeTabuleiro(char tabuleiro[10][10], char mascara[10][10]){

    char blue[] = { 0x1b, '[', '1', ';', '3', '4', 'm', 0 };
    char green[] = { 0x1b, '[', '1', ';', '3', '2', 'm', 0 };
    char normal[] = { 0x1b, '[', '1', ';', '3', '9', 'm', 0 };


    // i = linha, j = coluna
    int i, j;
    // Printa Mascara
    for (i = 0; i < 10; i++){
        printf("%d -",i); // Mapea as linhas
        for (j = 0; j < 10; j++){

            // Achei na internet, da pra colocar CORs
            switch (mascara[i][j]){
            case 'A':
                std::cout << blue << " " << mascara[i][j] << normal;
                break;
            
            case 'B':
                std::cout << green << " " << mascara[i][j] << normal;
                break;
            
            default:
                std::cout << " " << mascara[i][j];
                break;
            }

        }
        printf("\n");
    }
    printf("\n");
    // Printa Tabuleiro
        // Comente esse codigo para n aparecer as repostas
    // for (i = 0; i < 10; i++){
    //     for (j = 0; j < 10; j++){
    //         printf("%c ", tabuleiro[i][j]);
    //     }
    //     printf("\n");
    // }
}

void PosicionaBarcos(char tabuleiro[10][10]){
    // Coloca 10 barcos no tabuleiro
    int quantidade = 5, quantidade_posicionada=0;

    while(quantidade_posicionada < quantidade){
        LimpaTela();
        printf("Insira %d barcos no tabuleiro do Player1\n", quantidade-quantidade_posicionada);
        int linha_posicionada;
        int coluna_posicionada;

        printf("Insira a linha a ser Poscionada o Barco: \n");
        scanf("%d", &linha_posicionada);
        printf("Insira a coluna a ser Poscionada o Barco: \n");
        scanf("%d", &coluna_posicionada);

        tabuleiro[linha_posicionada][coluna_posicionada] = 'B';

        quantidade_posicionada++;
    }
}

void PosicionaBarcosPlayer2(char tabuleiro[10][10]){
    // Coloca 10 barcos no tabuleiro
    int quantidade = 5, quantidade_posicionada=0;

    while(quantidade_posicionada < quantidade){
        LimpaTela();
        printf("Insira %d barcos no tabuleiro do Player2\n", quantidade-quantidade_posicionada);
        int linha_posicionada;
        int coluna_posicionada;

        printf("Insira a linha a ser Poscionada o Barco: \n");
        scanf("%d", &linha_posicionada);
        printf("Insira a coluna a ser Poscionada o Barco: \n");
        scanf("%d", &coluna_posicionada);

        tabuleiro[linha_posicionada][coluna_posicionada] = 'B';

        quantidade_posicionada++;
    }
}

void VerificaTiro(char tabuleiro[10][10], int linha_jogada, int coluna_jogada, int *pontuacao, std::string *mensagem){
    // 00 01 02
    // 10 11 12
    // 20 21 22
    if (tabuleiro[linha_jogada][coluna_jogada] == 'B'){
        *pontuacao += 10;
        *mensagem = "Afundo ! (10pts)";
    }
    // Jogou e deu Agua, Verifica se ao redor tem B
    else if (tabuleiro[linha_jogada][coluna_jogada] == 'A'){
        int verificador = 0;
        if (tabuleiro[linha_jogada+1][coluna_jogada] == 'B'){
            verificador++;
        }
        if (tabuleiro[linha_jogada-1][coluna_jogada] == 'B'){
            verificador++;
        }
        if (tabuleiro[linha_jogada][coluna_jogada+1] == 'B'){
            verificador++;
        }
        if (tabuleiro[linha_jogada][coluna_jogada-1] == 'B'){
            verificador++;
        }
        if (tabuleiro[linha_jogada+1][coluna_jogada+1] == 'B'){
            verificador++;
        }
        if (tabuleiro[linha_jogada-1][coluna_jogada-1] == 'B'){
            verificador++;
        }
        // Mostra mensagem
        if (verificador > 0){
            *mensagem = "Passou perto";
        }
        else{
            *mensagem = "Errrroooouuuu";
        }
    }
}

void Jogo(std::string nome_do_jogador, std::string nome_do_jogador2){
    char tabuleiro[10][10];
    char mascara[10][10];
    int i, j;
    int linhaJogada, colunaJogada;
    int status_jogo = 1;
    int pontuacao = 0;
    int tentativas = 0, maximo_de_tentativa = 5;
    // Mensagem de iniciacao, e no decorrer vira mensagem de feedback
    std::string mensagem = "Bem vindo ao jogo !";

    IniciaTabuleiro(tabuleiro, mascara);

    // Posiciona Barcos Aleatorios
    PosicionaBarcos(tabuleiro);

    while (tentativas < maximo_de_tentativa){
        LimpaTela();
        ExibeMapa();
        ExibeTabuleiro(tabuleiro, mascara);

        printf("Pontos: %d\n", pontuacao);
        printf("Tentativas Restantes: %d\n", maximo_de_tentativa-tentativas);
        printf("%s\n", mensagem.c_str());

        // Verificando Entradas
        linhaJogada = -1; // So para entrar no while
        colunaJogada = -1; // So para entrar no while
        while( (linhaJogada < 0 || linhaJogada > 9) || (colunaJogada < 0 || colunaJogada > 9) ){
            printf("%s, Digite uma linha: \n", nome_do_jogador2.c_str());
            scanf("%d", &linhaJogada);
            printf("%s, Digite uma coluna: \n", nome_do_jogador2.c_str());
            scanf("%d", &colunaJogada);
        }

        VerificaTiro(tabuleiro, linhaJogada, colunaJogada, &pontuacao, &mensagem); // & = Ponteiro para haver a troca de valores da variavel

        // Revela a posicao jogada
        mascara[linhaJogada][colunaJogada] = tabuleiro[linhaJogada][colunaJogada];

        tentativas++;
    }

    int prossiga = 0;
    printf("Type 1 to continue the Game\n");
    scanf("%d", &prossiga);
    if (prossiga != 1){
        exit(1); // Seria o Break
    }

    // ------ Vez do Player 1 JOGAR ----------
    IniciaTabuleiro(tabuleiro, mascara);
    PosicionaBarcosPlayer2(tabuleiro);
    tentativas = 0;
    pontuacao = 0;
    while (tentativas < maximo_de_tentativa){
        LimpaTela();
        ExibeMapa();
        ExibeTabuleiro(tabuleiro, mascara);

        printf("Pontos: %d\n", pontuacao);
        printf("Tentativas Restantes: %d\n", maximo_de_tentativa-tentativas);
        printf("%s\n", mensagem.c_str());

        // Verificando Entradas
        linhaJogada = -1; // So para entrar no while
        colunaJogada = -1; // So para entrar no while
        while( (linhaJogada < 0 || linhaJogada > 9) || (colunaJogada < 0 || colunaJogada > 9) ){
            printf("%s, Digite uma linha: \n", nome_do_jogador.c_str());
            scanf("%d", &linhaJogada);
            printf("%s, Digite uma coluna: \n", nome_do_jogador.c_str());
            scanf("%d", &colunaJogada);
        }

        VerificaTiro(tabuleiro, linhaJogada, colunaJogada, &pontuacao, &mensagem); // & = Ponteiro para haver a troca de valores da variavel

        // Revela a posicao jogada
        mascara[linhaJogada][colunaJogada] = tabuleiro[linhaJogada][colunaJogada];

        tentativas++;
    }

    printf("Game Over :\n");
    printf("1 - Play Again\n");
    printf("2 - Go to Menu\n");
    printf("3 - Exit\n");
    int opcao; // Opcao para continuar
    scanf("%d", &opcao);
    switch (opcao){
    case 1:
        Jogo(nome_do_jogador, nome_do_jogador2);
        break;
    case 2:
        MenuInicial();
        break;
    }
}

int main(){
    // Gerando numeros aleatorios
    srand((unsigned)time(NULL));

    MenuInicial();

    return 0;
}