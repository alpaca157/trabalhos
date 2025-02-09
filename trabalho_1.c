#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//função para verificar se pode plantar as flores
bool canPlaceFlower(int* flowerbed, int flowerbedSize, int n) {
    int plantadas = 0;

    for (int i = 0; i < flowerbedSize; i++) {
        if (flowerbed[i] == 0 && //verifica se o local está vazio
            (i == 0 || flowerbed[i-1] == 0) &&  //verifica se o vizinho da esquerda está vazio
            (i == flowerbedSize - 1 || flowerbed[i+1] == 0)) {  //verifica se o vizinho da direita está vazio

            flowerbed[i] = 1;  //planta a flor
            plantadas++;  //incrementa o contador de flores plantadas

            if (plantadas == n) {  //se já plantou o número desejado de flores
                return true;
            }

            i++;  //pula para o próximo local depois de plantar
        }
    }

    return plantadas >= n;  //retorna verdadeiro se o número de flores plantadas for suficiente
}

// Função principal
int main() {
    // Exemplo de uso
    int flowerbed[] = {0, 0, 1, 0, 0, 1, 0, 0};  // Estado inicial do canteiro
    int flowerbedSize = sizeof(flowerbed) / sizeof(flowerbed[0]);  // Calcula o tamanho do canteiro
    int n = 2;  // Número de flores a plantar

    // Verifica se é possível plantar as flores
    if (canPlaceFlower(flowerbed, flowerbedSize, n)) {
        printf("É possível plantar %d flores.\n", n);  //exibe mensagem de sucesso
    } else {
        printf("Não é possível plantar %d flores.\n", n);  //exibe mensagem de erro
    }

    return 0;
}