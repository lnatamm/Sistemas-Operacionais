#include <stdio.h>

//Enum com os 3 estados principais e 1 estado "CONCLUIDO" auxiliar
typedef enum {
    PRONTO,
    EXEC,
    BLOQ,
    CONCLUIDO
} EstadoProcesso;

//Struct base do processo
typedef struct{
    int id;
    int tempo;
    EstadoProcesso estado;
} Processo;

void roundRobin(Processo processos[], int quantum, int nProcessos){

    //Inicialização das variáveis
    //Salvamos o valor do quantum em uma variável para podermos decrementá-lo mais adiante
    int aux = quantum;
    int tempo_atual = 0;
    int i = 0;
    int processosConcluidos = 0;

    //Enquanto houver processos a serem concluidos continuamos iterando
    while(processosConcluidos != nProcessos){
        //Se o processo ainda não foi concluído (estado != CONCLUIDO), alteramos o estado do processo pra EXEC
        if(processos[i].estado < 3){
            processos[i].estado = EXEC;
            //Executamos o processo pela quantidade de tempo do quantum
            while(quantum > 0){
                tempo_atual++;
                processos[i].tempo--;
                quantum--;
                printf("Tempo %d: Processo %d em execucao\n", tempo_atual, processos[i].id);
                //Se o processo terminar, alteramos seu estado para CONCLUIDO e aumentamos o n° de processos concluídos
                if(processos[i].tempo <= 0){
                    processos[i].estado = CONCLUIDO;
                    processosConcluidos++;
                    printf("Processo %d concluido\n", processos[i].id);
                    //O quantum é zerado para dessatisfazer a condição do loop e encerramos a execução do processo
                    quantum = 0;
                }
            }
            //O quantum é atribuído o seu valor original armazenado pela variável aux
            quantum = aux;
        }
        i++;
        //Se a atual iteração for a do último processo, zeramos o i para retornarmos ao primeiro processo da fila
        if(i >= nProcessos){
            i = 0;
        }
    }

}

int main() {

    //Inicialização dos processos para o nosso caso de teste
    Processo processos[] = {
        {1, 5, PRONTO},
        {2, 3, PRONTO},
        {3, 7, PRONTO},
    };

    //Calculamos a quantidade de processos pela fórmula
    int nProcessos = sizeof(processos)/sizeof(processos[0]);
    //Chamada do roundRobin
    roundRobin(processos, 4, nProcessos);

    return 0;

}