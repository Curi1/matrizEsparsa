#include <stdio.h>
#include "matriz.h"

int main() {



    // Criação e manipulação da matriz esparsa
    MatrizEsparsa *matriz = criaMatriz(10, 10);

    // Exemplo de inserção
    insere(matriz, 1, 2, 5.0);
    insere(matriz, 1, 3, 5.0);
    insere(matriz, 1, 4, 5.0);
    insere(matriz, 1, 5, 5.0);
    insere(matriz, 1, 6, 5.0);
    insere(matriz, 1, 7, 5.0);
    insere(matriz, 1, 8, 5.0);
    insere(matriz, 1, 9, 5.0);
    insere(matriz, 1, 10, 5.0);



    // Exemplo de impressão
    imprimeMatriz(matriz);

    // Liberação de memória
    //destroiMatriz(matriz);

    return 0;
}