#ifndef MATRIZ_H
#define MATRIZ_H

// Estrutura para uma célula da matriz esparsa
typedef struct Celula {
    int linha, coluna;
    float valor;
    struct Celula *direita, *abaixo;
} Celula;

// Estrutura para a matriz esparsa
typedef struct {
    Celula *cabeca;
    int linhas, colunas;
} MatrizEsparsa;

// Protótipos das funções
MatrizEsparsa* criaMatriz(int linhas, int colunas);
void insere(MatrizEsparsa* matriz, int linha, int coluna, float valor);
void imprimeMatriz(MatrizEsparsa* matriz);
void destroiMatriz(MatrizEsparsa* matriz);
MatrizEsparsa* leMatriz(const char* nomeArquivo);
MatrizEsparsa* somaMatrizes(MatrizEsparsa* A, MatrizEsparsa* B);
MatrizEsparsa* multiplicaMatrizes(MatrizEsparsa* A, MatrizEsparsa* B);
void limparBuffer();

#endif

