# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <string>
# include <iostream>

// Declara funcao para n gerar erro
void JogoAlone(std::string nome_do_jogador);
void JogoTogether(std::string player1, std::string player2);

void LimpaTela(){
    system("clear");
    // Or system("CLS");
}

void MenuInicial(){
    int option = 0;
    std::string nome_do_jogador;
    std::string player1;
    std::string player2;

    // Laço para opçoes validas
    while (option < 1 || option > 3){
        LimpaTela();
        printf("Welcome to Naval Battle !\n");
        printf("1 - Play Alone\n");
        printf("2 - Play Together\n");
        printf("3 - Exit\n");
        printf("Press one option and type ENTER: ");
        scanf("%d", &option);
    }

    switch (option){
    case 1:
        printf("What is your name: ");
        std::cin >> nome_do_jogador;
        JogoAlone(nome_do_jogador);
        break;
    case 2:
        printf("Name the Player 1: ");
        std::cin >> player1;
        printf("Name the Player 2: ");
        std::cin >> player2;
        JogoTogether(player1, player2);
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
            
            case 'P':
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
    // Coloca X barcos no tabuleiro, no caso 10
    int quantidade = 10, quantidade_posicionada=0;

    while(quantidade_posicionada < quantidade){
        int linha_aleatoria = rand() % 10;
        int coluna_aleatoria = rand() % 10;

        if (tabuleiro[linha_aleatoria][coluna_aleatoria] == 'A'){
            // Posiciona os 10 barcos aleatorios
            tabuleiro[linha_aleatoria][coluna_aleatoria] = 'P';

            // Aumenta a quantidade para evitar barcos na mesma posicao
            quantidade_posicionada++;
        }
    }

}

void VerificaTiro(char tabuleiro[10][10], int linha_jogada, int coluna_jogada, int *pontuacao, std::string *mensagem){
    switch (tabuleiro[linha_jogada][coluna_jogada]){
    case 'P':
        *pontuacao += 10;
        *mensagem = "Afundo um barco pequeno (10pts)";
        break;
    
    case 'A':
        *mensagem = "Nao afundou nenhum barco";
        break;
    }
}

void JogoAlone(std::string nome_do_jogador){
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
            printf("%s, Digite uma linha: \n", nome_do_jogador.c_str());
            scanf("%d", &linhaJogada);
            printf("%s, Digite uma coluna: \n", nome_do_jogador.c_str());
            scanf("%d", &colunaJogada);
        }

        VerificaTiro(tabuleiro, linhaJogada, colunaJogada, &pontuacao, &mensagem); // & = Ponteiro para haver a troca de valores da variavel

        // Revela a posicao jogada
        mascara[linhaJogada][colunaJogada] = tabuleiro[linhaJogada][colunaJogada];

        tentativas++;
        // if tentativas == maximo...:
            // break
    }

    printf("Game Over :\n");
    printf("1 - Play Again\n");
    printf("2 - Go to Menu\n");
    printf("3 - Exit\n");
    int opcao; // Opcao para continuar
    scanf("%d", &opcao);
    switch (opcao){
    case 1:
        JogoAlone(nome_do_jogador);
        break;
    case 2:
        MenuInicial();
        break;
    }
}

// ----------------- JOGO COM DOIS JOGADORES --------------------- //

void VerificaTiro_DoPlayer2(int linha_tabuleiro, int coluna_tabuleiro, int linha_jogada, int coluna_jogada, int *pontuacao){ //std::string *mensagem
    char tabuleiro[linha_tabuleiro][coluna_tabuleiro];

    switch (tabuleiro[linha_jogada][coluna_jogada]){
    case 'P':
        *pontuacao += 10;
        // *mensagem = "Afundo um barco pequeno (10pts)";
        break;
    
    case 'A':
        // *mensagem = "Nao afundou nenhum barco";
        break;
    }
}

void ExibeTabuleiroPlayer1(int linha_tabuleiro, int coluna_tabuleiro){
    char tabuleiro[linha_tabuleiro][coluna_tabuleiro];
    char mascara[linha_tabuleiro][coluna_tabuleiro];
    
    int i, j;
    // INICIA TABULEIRO PLAYER 1
    for (i = 0; i < linha_tabuleiro; i++){
        for (j = 0; j < coluna_tabuleiro; j++){
            tabuleiro[i][j] = 'A';
            mascara[i][j] = '*';
        }
    }
    // Printa Mascara
    for (i = 0; i < linha_tabuleiro; i++){
        printf("%d -",i); // Mapea as linhas
        for (j = 0; j < coluna_tabuleiro; j++){
            printf("%c", mascara[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    // Printa Tabuleiro
        // Comente esse codigo para n aparecer as repostas
    for (i = 0; i < linha_tabuleiro; i++){
        for (j = 0; j < coluna_tabuleiro; j++){
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// MAPEA AS COLUNAS
void ExibeMapaJogoTogether(int coluna_tabuleiro){
    // Indicando colunas (Mapea)
    for (int cont = 0; cont < coluna_tabuleiro; cont++){
        if (cont == 0){
            printf("    ");
        }
        printf("%d ", cont);
    }
    printf("\n");
    for (int cont = 0; cont < coluna_tabuleiro; cont++){
        if (cont == 0){
            printf("    ");
        }
        printf("| ");
    }
    printf("\n");
}

void PosicionaBarcosPlayer1(int linha_tabuleiro, int coluna_tabuleiro){
    char tabuleiro[linha_tabuleiro][coluna_tabuleiro];
    printf("Insira 5 barcos no tabuleiro do Player1\n");

    // Coloca 5 barcos no tabuleiro
    int quantidade = 5, quantidade_posicionada=0;

    while(quantidade_posicionada < quantidade){
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

void IniciaTabuleiroPlayer2(int linha_tabuleiro, int coluna_tabuleiro){ // nt tabuleiro[][], char mascara[][], i
    char tabuleiro[linha_tabuleiro][coluna_tabuleiro];
    char mascara[linha_tabuleiro][coluna_tabuleiro];
    // i = linha, j = coluna
    int i, j;
    // Preenchendo o tabuleiro
    for (i = 0; i < linha_tabuleiro; i++){
        for (j = 0; j < coluna_tabuleiro; j++){
            tabuleiro[i][j] = 'A';
            mascara[i][j] = '*';
        }
    }
}

void PosicionaBarcosPlayer2(int linha_tabuleiro, int coluna_tabuleiro){
    char tabuleiro[linha_tabuleiro][coluna_tabuleiro];
    printf("Insira 5 barcos no tabuleiro do Player2\n");

    // Coloca 5 barcos no tabuleiro
    int quantidade = 5, quantidade_posicionada=0;

    while(quantidade_posicionada < quantidade){
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

void JogoTogether(std::string player1, std::string player2){
    int linha_tabuleiro, coluna_tabuleiro;
    printf("Insira a Ordem do Tabuleiro. Ex: 4x4 LinhaxColuna\n");
    scanf("%d %d", &linha_tabuleiro, &coluna_tabuleiro);
    char tabuleiro[linha_tabuleiro][coluna_tabuleiro];
    char mascara[linha_tabuleiro][coluna_tabuleiro];

    int i, j;
    int linhaJogada, colunaJogada;
    int status_jogo = 1;
    int pontuacao = 0;
    int tentativas = 1, maximo_de_tentativa = 5;

    // IniciaTabuleiroPlayer1(linha_tabuleiro, coluna_tabuleiro); -> Passei para funcao ExibeTabuleiroPLayer1
    PosicionaBarcosPlayer1(linha_tabuleiro, coluna_tabuleiro);
    
    // IniciaTabuleiroPlayer2(linha_tabuleiro, coluna_tabuleiro);
    // PosicionaBarcosPlayer2(linha_tabuleiro, coluna_tabuleiro);

    while (tentativas == 1){
        LimpaTela();
        ExibeMapaJogoTogether(coluna_tabuleiro);
        ExibeTabuleiroPlayer1(linha_tabuleiro, coluna_tabuleiro);

    //     printf("Pontos: %d\n", pontuacao);
    //     printf("Tentativas Restantes: %d\n", maximo_de_tentativa-tentativas);
    //     printf("%s\n", mensagem.c_str());

        // Verificando Entradas
        // linhaJogada = -1; // So para entrar no while
        // colunaJogada = -1; // So para entrar no while
        // while( (linhaJogada < 0 || linhaJogada > 9) || (colunaJogada < 0 || colunaJogada > 9) ){
            printf("%s, Digite uma linha: \n", player2.c_str());
            scanf("%d", &linhaJogada);
            printf("%s, Digite uma coluna: \n", player2.c_str());
            scanf("%d", &colunaJogada);
        // }

        VerificaTiro_DoPlayer2(linha_tabuleiro, coluna_tabuleiro, linhaJogada, colunaJogada, &pontuacao); // &mensagem - & = Ponteiro para haver a troca de valores da variavel

        // Revela a posicao jogada
        mascara[linhaJogada][colunaJogada] = tabuleiro[linhaJogada][colunaJogada];

        // tentativas++;
    //     // if tentativas == maximo...:
    //         // break
    }

    // printf("Game Over :\n");
    // printf("1 - Play Again\n");
    // printf("2 - Go to Menu\n");
    // printf("3 - Exit\n");
    // int opcao; // Opcao para continuar
    // scanf("%d", &opcao);
    // switch (opcao){
    // case 1:
    //     JogoAlone(nome_do_jogador);
    //     break;
    // case 2:
    //     MenuInicial();
    //     break;
    // }

}

int main(){
    // Gerando numeros aleatorios
    srand((unsigned)time(NULL));

    MenuInicial();

    return 0;
}

