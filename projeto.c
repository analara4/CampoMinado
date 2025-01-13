#include <stdio.h>
#include <stdlib.h>

// definindo constantes para valores do tabuleiro
#define BOMBA 'b'
#define VAZIO 'x'
#define ABERTO 'o'

// funçao para inicializar o tabuleiro
char** iniciarTabuleiro(int tamanho) {
    // alocaçao dinamica de memoria para o tabuleiro
    
    char** tabuleiro = (char**)malloc(tamanho * sizeof(char*));
    for (int i = 0; i < tamanho; i++) {
        tabuleiro[i] = (char*)malloc(tamanho * sizeof(char));
    }
    return tabuleiro;
}

// fuçao para liberar memoria do tabuleiro
void liberarTabuleiro(char** tabuleiro, int tamanho) {
    // libera cada linha do tabuleiro
    for (int i = 0; i < tamanho; i++) {
        free(tabuleiro[i]);
    }
    // libera o ponteiro principal
    free(tabuleiro);
}

// funçao para revelar quadrados
void revelarQuadrado(char** tabuleiro, int tamanho, int x, int y) {
    // verifica se a posiçao é valida e se o quadrado ja foi revelado
    if (x < 0 || x >= tamanho || y < 0 || y >= tamanho || tabuleiro[x][y] == ABERTO) {
        return;
    }
    
    // marca o quadrado como revelado
    tabuleiro[x][y] = ABERTO;
    
    // verificar se os quadrados adjacentes nao possuem minas
    int adjTemBomba = 0;
    if (x > 0 && tabuleiro[x-1][y] == BOMBA) adjTemBomba = 1;
    if (x < tamanho-1 && tabuleiro[x+1][y] == BOMBA) adjTemBomba = 1;
    if (y > 0 && tabuleiro[x][y-1] == BOMBA) adjTemBomba = 1;
    if (y < tamanho-1 && tabuleiro[x][y+1] == BOMBA) adjTemBomba = 1;

    // se nao houver minas adjacentes, revelar os quadrados adjacentes recursivamente
    // if (adjTemBomba != 0), ou seja, se adjTemBomba = 1, nao tem mina adjacente
    if (!adjTemBomba) {
        if (x > 0) revelarQuadrado(tabuleiro, tamanho, x-1, y);
        if (x < tamanho-1) revelarQuadrado(tabuleiro, tamanho, x+1, y);
        if (y > 0) revelarQuadrado(tabuleiro, tamanho, x, y-1);
        if (y < tamanho-1) revelarQuadrado(tabuleiro, tamanho, x, y+1);
    }
}

// funçao para verificar se o jogador ganhou
int checagemVitoria(char** tabuleiro, int tamanho) {
    // vai percorrer todo o tabuleiro
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            // se encontrar algum quadrado vazio nao revelado, retorna 0 (quer dizer que o jogo ainda nao terminou)
            if (tabuleiro[i][j] == VAZIO) {
                return 0;
            }
        }
    }
    // se todos os quadrados vazios foram revelados, retorna 1 (jogador ganhou)
    return 1;
}

int main() {
    int numJogos, tamanhoTabuleiro, numJogadas;
    
    // leitura da quantidade de jogos
    // printf("Digite o numero de jogos: ");
    scanf("%d", &numJogos);
    
    for (int jogo = 0; jogo < numJogos; jogo++) {
        // leitura do tamanho do tabuleiro
        // printf("Digite o tamanho do tabuleiro: ");
        scanf("%d", &tamanhoTabuleiro);
        
        // inicializando o tabuleiro
        char** tabuleiro = iniciarTabuleiro(tamanhoTabuleiro);
        
        // leitura do conteudo do tabuleiro
        // printf("Digite o conteudo do tabuleiro:\n");
        for (int i = 0; i < tamanhoTabuleiro; i++) {
            for (int j = 0; j < tamanhoTabuleiro; j++) {
                scanf(" %c", &tabuleiro[i][j]);
            }
        }
        // leitura do numero de jogadas
        // printf("Digite o numero de jogadas: ");
        scanf("%d", &numJogadas);
        
        // indica para o usuario digitar as jogadas
        // printf("Jogadas:\n");
        
        int resultado = 0; // 0 = nao terminou, 1 = ganhou, -1 = perdeu
        for (int jogada = 0; jogada < numJogadas; jogada++) {
            int x, y;
            scanf("%d %d", &x, &y);
            
            // verificando se a jogada revela uma bomba
            if (tabuleiro[x][y] == BOMBA) {
                resultado = -1;
                break;
            } else {
                // revela o quadrado e os adjacentes (se possivel)
                revelarQuadrado(tabuleiro, tamanhoTabuleiro, x, y);
            }
        }
        
        if (resultado == 0) {
            // verifica se ganhou
            if (checagemVitoria(tabuleiro, tamanhoTabuleiro)) {
                resultado = 1;
            }
        }
        
        // impressao dos resultadoados
        if (resultado == -1) {
            printf("PERDEU\n");
        } else if (resultado == 1) {
            printf("GANHOU\n");
        } else {
            printf("FALTOU TERMINAR\n");
        }
        
        // liberar memoria do tabuleiro
        liberarTabuleiro(tabuleiro, tamanhoTabuleiro);
    }
    
    return 0;
}