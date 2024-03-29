// line 240 start the case 1 from menu
// line 363 start the case 2 from menu
// line 445 start the case 3 from menu

# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <string>
# include <iostream>

// VARIAVEIS GLOBIAS
static int LINHA_MATRIZ=0;
static int COLUNA_MATRIZ=0;

// --------------------------- //
// DECLARANDO FUNCOES:

// JOGO TWO PLAYERS
void Jogo(std::string nome_do_jogador, std::string nome_do_jogador2);

// JOGO SOLO
void JogoSolo(std::string nome_do_jogador);
void PosicionaBarcosAleatorios(char tabuleiro[10][10]);
void JogoSelecionandoOrdem(std::string nome_do_jogador, std::string nome_do_jogador2);

// JOGO COM SELECAO DE ORDEM
void IniciaTabuleiroSelecionandoOrdem(char tabuleiro[][10], char mascara[][10]);
void ExibeMapaSelecionandoOrdem();
void ExibeTabuleiroSelecionandoOrdem(char tabuleiro[10][10], char mascara[10][10]);
void PosicionaBarcosSelecionandoOrdem(char tabuleiro[][10]);
void PosicionaBarcosPlayer2SelecionandoOrdem(char tabuleiro[][10]);
void VerificaTiroSelecionandoOrdem(char tabuleiro[][10], int linha_jogada, int coluna_jogada, int *pontuacao, std::string *mensagem);
void JogoSelecionandoOrdem(std::string nome_do_jogador, std::string nome_do_jogador2);
// --------------------------- //

void LimpaTela(){
    system("clear");
    // Or system("CLS"); for windows
}

void MenuInicial(){
    int option = 0;
    // Declara String
    std::string nome_do_jogador;
    std::string nome_do_jogador2;

    // Laço para opçoes validas para iniciar o jogo
    while (option < 1 || option > 3){
        LimpaTela();
        printf("Welcome to Naval Battle !\n");
        printf("1 - Two Players\n");
        printf("2 - One Player\n");
        printf("3 - Two Player and Select The Order\n");
        printf("4 - Exit\n");
        printf("Press one option and type ENTER: ");
        scanf("%d", &option);
    }

    // Opcao escolhida pelo jogador
    switch (option){
    case 1:
        printf("Player1: ");
        // Input do nome do jogador 1
        std::cin >> nome_do_jogador;
        printf("Player2: ");
        // Input do nome do jogador 2
        std::cin >> nome_do_jogador2;
        // Inicia a funçao Jogo
        Jogo(nome_do_jogador, nome_do_jogador2);
        break;
    case 2:
        printf("Player1: ");
        // Input do nome do jogador 1
        std::cin >> nome_do_jogador;
        // Inicia a funcao JogoSolo
        JogoSolo(nome_do_jogador);
        break;
    case 3:
        printf("Insira a Ordem do Tabuleiro:\n");
        printf("Linha: ");
        // Input da linha
        std::cin >> LINHA_MATRIZ;
        printf("Coluna: ");
        // Input da Coluna
        std::cin >> COLUNA_MATRIZ;
        printf("Player1: ");
        // Input nome Jogador 1
        std::cin >> nome_do_jogador;
        printf("Player2: ");
        // Input nome Jogador 2
        std::cin >> nome_do_jogador2;
        // Inicia funçao JogoSlecionandoOrdem, OBS: Funciona até 10L:10C
        JogoSelecionandoOrdem(nome_do_jogador, nome_do_jogador2);
        break;
    case 4:
        printf("Game Over !\n");
        break;
    }
}

void IniciaTabuleiro(char tabuleiro[10][10], char mascara[10][10]){
    // i = linha, j = coluna
    int i, j;
    // Preenchendo o tabuleiro(Agua = A) e a mascara(*) 
    for (i = 0; i < 10; i++){
        for (j = 0; j < 10; j++){
            tabuleiro[i][j] = 'A';
            mascara[i][j] = '*';
        }
    }
}

void ExibeMapa(){
    // Indicando colunas (Mapea), Apenas desenha o numero de colunas e os " | "
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
    // Declarando Cores
    char blue[] = { 0x1b, '[', '1', ';', '3', '4', 'm', 0 };
    char green[] = { 0x1b, '[', '1', ';', '3', '2', 'm', 0 };
    char normal[] = { 0x1b, '[', '1', ';', '3', '9', 'm', 0 };


    // i = linha, j = coluna
    int i, j;
    // Printa Mascara
    for (i = 0; i < 10; i++){
        printf("%d -",i); // Mapea as linhas
        for (j = 0; j < 10; j++){

            // Achei na internet, da pra colocar CORES
            switch (mascara[i][j]){
            case 'A':
                // "Fura a mascara" e mostra ao jogador oque ele acertou Agua
                std::cout << blue << " " << mascara[i][j] << normal;
                break;
            
            case 'B':
                // "Fura a mascara" e mostra ao jogador oque ele acertou Barco
                std::cout << green << " " << mascara[i][j] << normal;
                break;
            
            default:
                // "Fura a mascara" e mostra ao jogador oque ele acertou Nada
                std::cout << " " << mascara[i][j];
                break;
            }

        }
        printf("\n");
    }
    printf("\n");
    // ------------- //
    // Printa Tabuleiro
        // Comente esse codigo para n aparecer as repostas
    // for (i = 0; i < 10; i++){
    //     for (j = 0; j < 10; j++){
    //         printf("%c ", tabuleiro[i][j]);
    //     }
    //     printf("\n");
    // }
    // ------------- //
}

void PosicionaBarcos(char tabuleiro[10][10]){
    // Declara a quantidade de barco
    int quantidade = 5, quantidade_posicionada=0;

    // Coloca 5 barcos no tabuleiro
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
    // Coloca 5 barcos no tabuleiro
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
    // Os '*' sao apenas ponteiros
    if (tabuleiro[linha_jogada][coluna_jogada] == 'B'){
        *pontuacao += 10;
        *mensagem = "Afundo ! (10pts)";
    }
    // Jogou e deu Agua, Verifica se ao redor tem Barco, Regra do Exercicio.
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

    // Apenas um 'break' para visualizaçao
    int prossiga = 0;
    printf("Type 1 to continue the Game\n");
    scanf("%d", &prossiga);
    if (prossiga != 1){
        exit(1); // Seria o Break, só que n tava funcionando break entao coloquei exit
    }

    // Pontos jogador 2, para exibir o placar no final
    int pontuacao_player2 = pontuacao;


    // ------ Vez do Player 1 JOGAR ----------
    IniciaTabuleiro(tabuleiro, mascara);
    PosicionaBarcosPlayer2(tabuleiro);
    mensagem = "Player1 is turn";
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

    // Placar:
    if (pontuacao > pontuacao_player2){
        printf("Player1 Won\n");
    }
    else if (pontuacao_player2 > pontuacao){
        printf("Player2 Won\n");
    }
    else if (pontuacao_player2 == pontuacao){
        printf("The Game is drew\n");
    }
    // Opcoes finais
    printf("Player1 = %d | Player2 = %d\n", pontuacao, pontuacao_player2);
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

// --------------------------------- JOGAR SOLO --------------------------------- //

void JogoSolo(std::string nome_do_jogador){
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
    PosicionaBarcosAleatorios(tabuleiro);

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
        JogoSolo(nome_do_jogador);
        break;
    case 2:
        MenuInicial();
        break;
    }
}

void PosicionaBarcosAleatorios(char tabuleiro[10][10]){
    // Coloca X barcos no tabuleiro, no caso 10
    int quantidade = 10, quantidade_posicionada=0, contador=0;

    while(quantidade_posicionada < quantidade){
        int linha_aleatoria = rand() % 10;
        int coluna_aleatoria = rand() % 10;

        if (tabuleiro[linha_aleatoria][coluna_aleatoria] == 'A'){
            // Posiciona os 10 barcos aleatorios
            tabuleiro[linha_aleatoria][coluna_aleatoria] = 'B';

            // Aumenta a quantidade para evitar barcos na mesma posicao
            quantidade_posicionada++;
        }
    }

}

// ------------------------ THE GAME WITH SELECTION ORDER ------------------------- //
void IniciaTabuleiroSelecionandoOrdem(char tabuleiro[][10], char mascara[][10]){
    // i = linha, j = coluna
    int i, j;
    // Preenchendo o tabuleiro
    for (i = 0; i < LINHA_MATRIZ; i++){
        for (j = 0; j < COLUNA_MATRIZ; j++){
            tabuleiro[i][j] = 'A';
            mascara[i][j] = '*';
        }
    }
}

void ExibeMapaSelecionandoOrdem(){
    // Indicando colunas (Mapea)
    for (int cont = 0; cont < COLUNA_MATRIZ; cont++){
        if (cont == 0){
            printf("    ");
        }
        printf("%d ", cont);
    }
    printf("\n");
    for (int cont = 0; cont < COLUNA_MATRIZ; cont++){
        if (cont == 0){
            printf("    ");
        }
        printf("| ");
    }
    printf("\n");
}

void ExibeTabuleiroSelecionandoOrdem(char tabuleiro[10][10], char mascara[10][10]){

    char blue[] = { 0x1b, '[', '1', ';', '3', '4', 'm', 0 };
    char green[] = { 0x1b, '[', '1', ';', '3', '2', 'm', 0 };
    char normal[] = { 0x1b, '[', '1', ';', '3', '9', 'm', 0 };


    // i = linha, j = coluna
    int i, j;
    // Printa Mascara
    for (i = 0; i < LINHA_MATRIZ; i++){
        printf("%d -",i); // Mapea as linhas
        for (j = 0; j < COLUNA_MATRIZ; j++){

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

void PosicionaBarcosSelecionandoOrdem(char tabuleiro[][10]){
    // Coloca 5 barcos no tabuleiro
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

void PosicionaBarcosPlayer2SelecionandoOrdem(char tabuleiro[][10]){
    // Coloca 5 barcos no tabuleiro
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

void VerificaTiroSelecionandoOrdem(char tabuleiro[][10], int linha_jogada, int coluna_jogada, int *pontuacao, std::string *mensagem){
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

void JogoSelecionandoOrdem(std::string nome_do_jogador, std::string nome_do_jogador2){
    char tabuleiro[LINHA_MATRIZ][10];
    char mascara[LINHA_MATRIZ][10];
    int i, j;
    int linhaJogada, colunaJogada;
    int status_jogo = 1;
    int pontuacao = 0;
    int tentativas = 0, maximo_de_tentativa = 5;
    // Mensagem de iniciacao, e no decorrer vira mensagem de feedback
    std::string mensagem = "Bem vindo ao jogo !";

    IniciaTabuleiroSelecionandoOrdem(tabuleiro, mascara);

    // Posiciona Barcos Aleatorios
    PosicionaBarcosSelecionandoOrdem(tabuleiro);

    while (tentativas < maximo_de_tentativa){
        LimpaTela();
        ExibeMapaSelecionandoOrdem();
        ExibeTabuleiroSelecionandoOrdem(tabuleiro, mascara);

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

        VerificaTiroSelecionandoOrdem(tabuleiro, linhaJogada, colunaJogada, &pontuacao, &mensagem); // & = Ponteiro para haver a troca de valores da variavel

        // Revela a posicao jogada
        mascara[linhaJogada][colunaJogada] = tabuleiro[linhaJogada][colunaJogada];

        tentativas++;
    }

    int prossiga = 0;
    printf("Feedback the Board Game - Type 1 to continue\n");
    scanf("%d", &prossiga);
    if (prossiga != 1){
        exit(1); // Seria o Break
    }

    // Pontos jogador 2
    int pontuacao_player2 = pontuacao;


    // ------ Vez do Player 1 JOGAR ----------
    IniciaTabuleiroSelecionandoOrdem(tabuleiro, mascara);
    PosicionaBarcosPlayer2SelecionandoOrdem(tabuleiro);
    mensagem = "Player1 is turn";
    tentativas = 0;
    pontuacao = 0;
    while (tentativas < maximo_de_tentativa){
        LimpaTela();
        ExibeMapaSelecionandoOrdem();
        ExibeTabuleiroSelecionandoOrdem(tabuleiro, mascara);

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

        VerificaTiroSelecionandoOrdem(tabuleiro, linhaJogada, colunaJogada, &pontuacao, &mensagem); // & = Ponteiro para haver a troca de valores da variavel

        // Revela a posicao jogada
        mascara[linhaJogada][colunaJogada] = tabuleiro[linhaJogada][colunaJogada];

        tentativas++;
    }

    if (pontuacao > pontuacao_player2){
        printf("Player1 Won\n");
    }
    else if (pontuacao_player2 > pontuacao){
        printf("Player2 Won\n");
    }
    else if (pontuacao_player2 == pontuacao){
        printf("The game is drew\n");
    }
    
    printf("Player1 = %d | Player2 = %d\n", pontuacao, pontuacao_player2);
    printf("Game Over :\n");
    printf("1 - Play Again\n");
    printf("2 - Go to Menu\n");
    printf("3 - Exit\n");
    int opcao; // Opcao para continuar
    scanf("%d", &opcao);
    switch (opcao){
    case 1:
        JogoSelecionandoOrdem(nome_do_jogador, nome_do_jogador2);
        break;
    case 2:
        MenuInicial();
        break;
    }
}