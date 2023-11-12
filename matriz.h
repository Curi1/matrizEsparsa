//
// Created by mathe on 11/11/2023.
//

#ifndef MATRIZESPARSA_MATRIZ_H
#define MATRIZESPARSA_MATRIZ_H

#endif //MATRIZESPARSA_MATRIZ_H


#ifndef MATRIZ_H
#define MATRIZ_H

typedef struct Celula {
    int linha, coluna;
    float valor;
    struct Celula *direita, *abaixo;
} Celula;

typedef struct {
    Celula *cabeca;
    int linhas, colunas;
} MatrizEsparsa;

// Protótipos das funções
MatrizEsparsa* criaMatriz(int linhas, int colunas);
void insere(MatrizEsparsa* matriz, int linha, int coluna, float valor);
void imprimeMatriz(MatrizEsparsa* matriz);
void destroiMatriz(MatrizEsparsa* matriz);

#endif
