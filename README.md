# Batalha-Naval
INSTALAÇÃO  DO PROJETO MAC/LINUX

1- Ja criado um diretório faça o clone do projeto:

    $ git clone git@github.com:luivilella/academia.git

2 - Confira se esta na pasta com o comando:

    $ ls

3 - Com o VsCode instalado rode o comando no terminal para abrir o Editor com o projeto:

    $ code .

4 - Rode o comando para rodar o projeto:

    $ g++ -o /tmp/a.out batalha_naval.cpp && /tmp/a.out


# Descrição:
A = Agua

B = Barco

Jogo entre dois usuários, cada um poderá escolher a ordem de sua matriz
(linhas e colunas). O programa então cria essa matriz e o usuario preenche
as posições com o valor B, o restante deverá ser A.

Cada usuário deverá acertar qual a posição da matriz do adversário possui o
valor B, se ele acertar é como se afundasse aquela posição. Ganha quem
afundar o maior número de posições do outro. O usuário informa a linha e
coluna, se caso esse valor for B o programa imprime “Afundou”, se caso não
for B mas alguma posição ao redor for B deve imprimir “Passou perto”, senão
deve imprimir “Errrou!”. O número de tentativas pode ser limitado.

# Logica Código:

No menu inicial, o usuário escolhe se quer jogar sozinho ou não.

Com apenas um jogador: 
    Player X Maquina

Com dois player:
    Player 1 insere seus barcos, em seguida o Player 2 joga e ocorre
    o inverso depois.