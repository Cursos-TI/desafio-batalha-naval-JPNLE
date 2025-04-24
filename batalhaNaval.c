#include <stdio.h>

#define TAMANHO 10
#define TAMANHO_NAVIO 3
#define TAM_HABILIDADE 5

int tabuleiro[TAMANHO][TAMANHO] = {0};

// ---------- Funções de Navios ----------
int podePosicionar(int linha, int coluna, int direcao, int diagonal) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha + (diagonal ? i : (direcao == 1 ? i : 0));
        int c = coluna + (diagonal ? (direcao == 1 ? i : -i) : (direcao == 0 ? i : 0));
        if (l < 0 || l >= TAMANHO || c < 0 || c >= TAMANHO || tabuleiro[l][c] != 0)
            return 0;
    }
    return 1;
}

void posicionarNavio(int linha, int coluna, int direcao, int diagonal) {
    if (podePosicionar(linha, coluna, direcao, diagonal)) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            int l = linha + (diagonal ? i : (direcao == 1 ? i : 0));
            int c = coluna + (diagonal ? (direcao == 1 ? i : -i) : (direcao == 0 ? i : 0));
            tabuleiro[l][c] = 3;
        }
    }
}

// ---------- Funções de Habilidade ----------
void aplicarHabilidade(int origemLinha, int origemColuna, char tipo) {
    int matriz[TAM_HABILIDADE][TAM_HABILIDADE] = {0};

    // Preencher matriz de habilidade conforme o tipo
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int centro = TAM_HABILIDADE / 2;
            switch (tipo) {
                case 'C': // Cone para baixo
                    if (i >= centro && j >= centro - (i - centro) && j <= centro + (i - centro))
                        matriz[i][j] = 1;
                    break;
                case 'X': // Cruz
                    if (i == centro || j == centro)
                        matriz[i][j] = 1;
                    break;
                case 'O': // Octaedro (losango)
                    if (abs(i - centro) + abs(j - centro) <= centro)
                        matriz[i][j] = 1;
                    break;
            }
        }
    }

    // Aplicar a habilidade ao tabuleiro
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (matriz[i][j] == 1) {
                int linha = origemLinha - TAM_HABILIDADE / 2 + i;
                int coluna = origemColuna - TAM_HABILIDADE / 2 + j;
                if (linha >= 0 && linha < TAMANHO && coluna >= 0 && coluna < TAMANHO) {
                    if (tabuleiro[linha][coluna] == 0)
                        tabuleiro[linha][coluna] = 5;
                }
            }
        }
    }
}

// ---------- Exibição ----------
void exibirTabuleiro() {
    printf("Tabuleiro:\n");
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            if (tabuleiro[i][j] == 0)
                printf("~ ");
            else if (tabuleiro[i][j] == 3)
                printf("N ");
            else if (tabuleiro[i][j] == 5)
                printf("* ");
        }
        printf("\n");
    }
}

// ---------- Main ----------
int main() {
    // Posiciona navios (reutiliza código anterior)
    posicionarNavio(2, 1, 0, 0);     // horizontal
    posicionarNavio(5, 7, 1, 0);     // vertical
    posicionarNavio(0, 0, 1, 1);     // diagonal principal
    posicionarNavio(0, 9, -1, 1);    // diagonal secundária

    // Aplicar habilidades
    aplicarHabilidade(2, 4, 'C'); // Cone em (2,4)
    aplicarHabilidade(5, 5, 'X'); // Cruz em (5,5)
    aplicarHabilidade(7, 2, 'O'); // Octaedro em (7,2)

    // Exibir resultado
    exibirTabuleiro();

    return 0;
}
