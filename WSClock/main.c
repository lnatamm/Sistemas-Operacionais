#include <stdio.h>
#include <stdlib.h>

#define NUM_FRAMES 3 // Número de frames na memória
#define INFINITY 999999

typedef struct {
    int pageNumber;
    int referenceBit;
    int time;
} PageFrame;

int min(PageFrame memory[]){
    int min = INFINITY;
    int index = -1;
    for(int i = 0; i < NUM_FRAMES; i++){
        if(memory[i].time < min){
            min = memory[i].time;
            index = i;
        }
    }
    return index;
}

int main() {
    PageFrame memory[NUM_FRAMES];
    int pageReferences[] = {0, 1, 2, 1, 0, 2, 3, 0, 2, 4, 5, 6}; // Páginas referenciadas
    int numReferences = sizeof(pageReferences) / sizeof(pageReferences[0]);
    int latestPage = -1;
    int i, j, k;
    int currTime = 0;
    int currK;

    // Inicializa a memória
    for (i = 0; i < NUM_FRAMES; i++) {
        memory[i].pageNumber = -1; // -1 indica que o frame está vazio
        memory[i].referenceBit = 0;
        memory[i].time = 0;
    }

    k = 0; // Inicializa o ponteiro do relógio
    currK = k; //Salva o k atual

    // Simula as referências às páginas
    for (i = 0; i < numReferences; i++) {
        int pageReferenced = pageReferences[i];
        int pageFound = 0;

        // Verifica se a página está na memória
        for (j = 0; j < NUM_FRAMES; j++) {
            if (memory[j].pageNumber == pageReferenced) {
                memory[j].referenceBit = 1; // Define o bit de referência
                memory[j].time = currTime;
                pageFound = 1;
                printf("Pagina %d ja esta referenciada na memoria. Tempo de referencia: %d \n\n", pageReferenced, currTime);
                break;
            }
        }

        // Se a página não estiver na memória, substitui uma página
        if (!pageFound) {
            // Procura por uma página com bit de referência zero
            while (1) {
                if (memory[k].referenceBit == 0) {
                    // Substitui a página
                    printf("Substituiu pagina %d com tempo de referencia %d\n", memory[k].pageNumber, memory[k].time);
                    memory[k].pageNumber = pageReferenced;
                    memory[k].referenceBit = 1;
                    memory[k].time = currTime;
                    printf("Pagina %d entrou no lugar. Tempo de referencia: %d\n\n", pageReferenced, currTime);
                    break;
                }
                else{
                    // Zera o bit de referência para a próxima verificação
                    memory[k].referenceBit = 0;
                    latestPage = min(memory);
                }
                k = (k + 1) % NUM_FRAMES; // Avança para o próximo frame
                if(k == currK){
                    //Loopou
                    printf("Ponteiro ciclou, substituindo pagina %d por ter sido referenciada a mais tempo (%d)\n", memory[latestPage].pageNumber, memory[latestPage].time);
                    memory[latestPage].pageNumber = pageReferenced;
                    memory[latestPage].referenceBit = 1;
                    memory[latestPage].time = currTime;
                    printf("Pagina %d entrou no lugar. Tempo de referencia: %d\n\n", pageReferenced, currTime);
                    break;
                }
            }
        }

        // Imprime o estado da memória após cada referência
        printf("Estado da memoria apos referencia %d: ", pageReferenced);
        for (j = 0; j < NUM_FRAMES; j++) {
            if (memory[j].pageNumber == -1)
                printf("[ - ] ");
            else
                printf("[ %d ] ", memory[j].pageNumber);
        }
        printf("\n\n");
        currTime++;
        currK = k;
    }

    return 0;
}