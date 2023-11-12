#include <stdio.h>
#include "matriz.h"Mmatrix

int main() {

    MatrizEsparsa *A, *B, *C, *D, *E;

    // Lendo e imprimindo a matriz A
    printf("Lendo a matriz A de 'matrizA.txt'\n");
    A = leMatriz("matrizA.txt");
    printf("Matriz A:\n");
    imprimeMatriz(A);

    // Lendo e imprimindo a matriz B
    printf("Lendo a matriz B de 'matrizB.txt'\n");
    B = leMatriz("matrizB.txt");
    printf("Matriz B:\n");
    imprimeMatriz(B);

    // Somando as matrizes A e B
    C = somaMatrizes(A, B);
    printf("Matriz A + B:\n");
    imprimeMatriz(C);

    // Multiplicando as matrizes A e B
    D = multiplicaMatrizes(A, B);
    printf("Matriz A * B:\n");
    imprimeMatriz(D);

    // Criando uma nova matriz E e inserindo valores manualmente
    printf("Criando uma nova matriz E 3x3 e inserindo valores\n");
    E = criaMatriz(3, 3);
    insere(E, 0, 0, 1.0);
    insere(E, 1, 1, 2.0);
    insere(E, 2, 2, 3.0);
    printf("Matriz E:\n");
    imprimeMatriz(E);

    // Liberando as matrizes da memória
    destroiMatriz(A);
    destroiMatriz(B);
    destroiMatriz(C);
    destroiMatriz(D);
    destroiMatriz(E);

    return 0;
}