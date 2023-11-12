#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

// Implementações das funções


MatrizEsparsa* leMatriz(const char* nomeArquivo, int linhas, int colunas) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        printf("Não foi possível abrir o arquivo.\n");
        return NULL;
    }




    MatrizEsparsa* matriz = criaMatriz(linhas, colunas);
    if (!matriz) {
        fclose(arquivo);
        return NULL;
    }

    int l, c;
    float valor;

    // Lendo os elementos do arquivo
    while (fscanf(arquivo, "%d %d %f", &l, &c, &valor) == 3) {
        if (l < linhas && c < colunas) {
            insere(matriz, l, c, valor);
        }
    }

    fclose(arquivo);
    return matriz;
}

void escreveMatriz(const char* nomeArquivo, MatrizEsparsa* matriz) {
    if (!matriz) {
        printf("Matriz não inicializada.\n");
        return;
    }

    FILE* arquivo = fopen(nomeArquivo, "w");
    if (!arquivo) {
        printf("Não foi possível abrir o arquivo para escrita.\n");
        return;
    }

    Celula* linhaAtual = matriz->cabeca->abaixo;

    // Percorre todas as linhas
    while (linhaAtual != matriz->cabeca) {
        Celula* celulaAtual = linhaAtual->direita;

        // Percorre todas as células da linha
        while (celulaAtual != linhaAtual) {
            fprintf(arquivo, "%d %d %.2f\n", celulaAtual->linha, celulaAtual->coluna, celulaAtual->valor);
            celulaAtual = celulaAtual->direita;
        }

        linhaAtual = linhaAtual->abaixo;
    }

    fclose(arquivo);
}


// Exemplo: criaMatriz
MatrizEsparsa* criaMatriz(int linhas, int colunas) {
    MatrizEsparsa* novaMatriz = (MatrizEsparsa*) malloc(sizeof(MatrizEsparsa));

    // Verifica se a alocação de memória foi bem-sucedida
    if (!novaMatriz) {
        printf("Erro de alocação de memória.\n");
        return NULL;
    }

    novaMatriz->linhas = linhas;
    novaMatriz->colunas = colunas;

    // Criação da célula cabeça
    novaMatriz->cabeca = (Celula*) malloc(sizeof(Celula));
    if (!novaMatriz->cabeca) {
        printf("Erro de alocação de memória.\n");
        free(novaMatriz);
        return NULL;
    }

    // Inicializando a célula cabeça
    novaMatriz->cabeca->direita = novaMatriz->cabeca;
    novaMatriz->cabeca->abaixo = novaMatriz->cabeca;
    novaMatriz->cabeca->linha = -1;
    novaMatriz->cabeca->coluna = -1;

    return novaMatriz;
}

// Exemplo: insere
void insere(MatrizEsparsa* matriz, int linha, int coluna, float valor) {
    if (!matriz || linha >= matriz->linhas || coluna >= matriz->colunas) {
        printf("Posição inválida ou matriz não inicializada.\n");
        return;
    }

    Celula *nova = (Celula*) malloc(sizeof(Celula));
    if (!nova) {
        printf("Erro de alocação de memória.\n");
        return;
    }

    nova->linha = linha;
    nova->coluna = coluna;
    nova->valor = valor;

    // Inserção na lista da linha
    Celula *linhaAtual = matriz->cabeca;
    while (linhaAtual->abaixo != matriz->cabeca && linhaAtual->abaixo->linha < linha)
        linhaAtual = linhaAtual->abaixo;

    Celula *colunaAtual = linhaAtual;
    while (colunaAtual->direita != linhaAtual && colunaAtual->direita->coluna < coluna)
        colunaAtual = colunaAtual->direita;

    nova->direita = colunaAtual->direita;
    colunaAtual->direita = nova;

    // Inserção na lista da coluna
    Celula *colunaCabeca = matriz->cabeca;
    while (colunaCabeca->direita != matriz->cabeca && colunaCabeca->direita->coluna < coluna)
        colunaCabeca = colunaCabeca->direita;

    Celula *linhaColuna = colunaCabeca;
    while (linhaColuna->abaixo != colunaCabeca && linhaColuna->abaixo->linha < linha)
        linhaColuna = linhaColuna->abaixo;

    nova->abaixo = linhaColuna->abaixo;
    linhaColuna->abaixo = nova;
}

// Exemplo: imprimeMatriz
void imprimeMatriz(MatrizEsparsa* matriz) {
    if (!matriz) {
        printf("Matriz não inicializada.\n");
        return;
    }

    Celula *linhaAtual = matriz->cabeca->abaixo; // Começa na primeira linha

    while (linhaAtual != matriz->cabeca) { // Percorre todas as linhas
        Celula *celulaAtual = linhaAtual->direita;
        for (int j = 0; j < matriz->colunas; j++) {
            // Se existir uma célula na coluna atual e na linha atual, imprime seu valor
            if (celulaAtual != linhaAtual && celulaAtual->coluna == j) {
                printf("%.2f\t", celulaAtual->valor);
                celulaAtual = celulaAtual->direita; // Vai para a próxima célula na linha
            } else {
                printf("0.00\t"); // Imprime 0 para células vazias
            }
        }
        printf("\n");
        linhaAtual = linhaAtual->abaixo; // Vai para a próxima linha
    }
}

// Exemplo: destroiMatriz
void destroiMatriz(MatrizEsparsa* matriz) {
    if (!matriz) {
        printf("Matriz não inicializada ou já destruída.\n");
        return;
    }

    Celula *linhaAtual = matriz->cabeca->abaixo;

    // Percorre cada linha da matriz
    while (linhaAtual != matriz->cabeca) {
        Celula *celulaAtual = linhaAtual->direita;

        // Percorre e libera cada célula da linha
        while (celulaAtual != linhaAtual) {
            Celula *temp = celulaAtual;
            celulaAtual = celulaAtual->direita;
            free(temp);
        }

        // Move para a próxima linha e libera a linha atual
        Celula *linhaTemp = linhaAtual;
        linhaAtual = linhaAtual->abaixo;
        free(linhaTemp);
    }

    // Libera a célula cabeça e a estrutura da matriz
    free(matriz->cabeca);
    free(matriz);
}

float getValor(MatrizEsparsa* matriz, int linha, int coluna) {
    Celula* celulaAtual = matriz->cabeca->abaixo;
    while (celulaAtual != matriz->cabeca) {
        if (celulaAtual->linha == linha) {
            Celula* celulaColuna = celulaAtual->direita;
            while (celulaColuna != celulaAtual) {
                if (celulaColuna->coluna == coluna) {
                    return celulaColuna->valor;
                }
                celulaColuna = celulaColuna->direita;
            }
        }
        celulaAtual = celulaAtual->abaixo;
    }
    return 0;
}


MatrizEsparsa* somaMatrizes(MatrizEsparsa* A, MatrizEsparsa* B) {
    if (!A || !B) {
        printf("Uma ou ambas as matrizes não estão inicializadas.\n");
        return NULL;
    }

    if (A->linhas != B->linhas || A->colunas != B->colunas) {
        printf("Matrizes de dimensões diferentes não podem ser somadas.\n");
        return NULL;
    }

    MatrizEsparsa* C = criaMatriz(A->linhas, A->colunas);

    // Percorre as linhas de A
    for (int i = 0; i < A->linhas; i++) {
        // Percorre as colunas de A
        for (int j = 0; j < A->colunas; j++) {
            float valorA = getValor(A, i, j);
            float valorB = getValor(B, i, j);

            if (valorA != 0 || valorB != 0) {
                insere(C, i, j, valorA + valorB);
            }
        }
    }

    return C;
}

MatrizEsparsa* multiplicaMatrizes(MatrizEsparsa* A, MatrizEsparsa* B) {
    if (!A || !B) {
        printf("Uma ou ambas as matrizes não estão inicializadas.\n");
        return NULL;
    }

    if (A->colunas != B->linhas) {
        printf("Matrizes com dimensões incompatíveis para multiplicação.\n");
        return NULL;
    }

    MatrizEsparsa* C = criaMatriz(A->linhas, B->colunas);

    // Para cada linha de A
    for (int i = 0; i < A->linhas; i++) {
        // E para cada coluna de B
        for (int j = 0; j < B->colunas; j++) {
            float valor = 0;

            // Multiplica cada elemento da linha de A pelo elemento correspondente da coluna de B
            for (int k = 0; k < A->colunas; k++) {
                valor += getValor(A, i, k) * getValor(B, k, j);
            }

            if (valor != 0) {
                insere(C, i, j, valor);
            }
        }
    }

    return C;
}


