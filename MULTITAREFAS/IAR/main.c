#include <stdint.h>
#include <stdio.h>

#include "multitarefas.h"

/*
 * Prototipos das tarefas
 */
void tarefa_1(void);
void tarefa_2(void);

/*
 * Configuracao dos tamanhos das pilhas
 */
#define TAM_PILHA_1		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_2		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_OCIOSA	(TAM_MINIMO_PILHA + 24)

/*
 * Declaracao das pilhas das tarefas
 */
uint32_t PILHA_TAREFA_1[TAM_PILHA_1];
uint32_t PILHA_TAREFA_2[TAM_PILHA_2];
uint32_t PILHA_TAREFA_OCIOSA[TAM_PILHA_OCIOSA];

// variaveis de teste para ter nocao de quantas vezes cada thread foi executada
unsigned int c = 0, d=0;

/*
 * Funcao principal de entrada do sistema
 */
int main(void)
{
	
	/* Criacao das tarefas */
	/* Parametros: ponteiro, nome, ponteiro da pilha, tamanho da pilha, prioridade da tarefa */
	
	CriaTarefa(tarefa_1, "Tarefa 1", PILHA_TAREFA_1, TAM_PILHA_1, 1);
	
	CriaTarefa(tarefa_2, "Tarefa 2", PILHA_TAREFA_2, TAM_PILHA_2, 2);
	
	/* Cria tarefa ociosa do sistema */
	CriaTarefa(tarefa_ociosa,"Tarefa ociosa", PILHA_TAREFA_OCIOSA, TAM_PILHA_OCIOSA, 0);
        
        printf("Criou as tarefas");
	
	/* Configura marca de tempo */
	ConfiguraMarcaTempo();   
	
	/* Inicia sistema multitarefas */
	IniciaMultitarefas();
	
        /* MODO PREEMPTIVO - Usando a interrupcao da troca de contexto que foi ativada na
         * interrupcao de timer em 'cpu-port.c'. Assim sendo, quando a tarefa_2 libera a CPU 
         * por meio de um delay 'TarefaEspera(100)', neste momento e ativada a troca de contexto 
         * e a tarefa_1 de menor prioridade volta a executar ate que o tempo de espera termine
         */ 

	/* Nunca chega aqui */
	while (1)
	{
	}
}

/* Tarefas de exemplo que usam funcoes para suspender/continuar as tarefas */
void tarefa_1(void)
{
	volatile uint16_t a = 0;
	for(;;)
	{
		a++;
                if(a==65000){
                  c++;
                  a = 0;
                }
                //TarefaContinua(2);                
	}
}
/*
 * tarefa 2 tem maior prioridade e tempo de espera de 100ms
 * 
 */
void tarefa_2(void)
{
        volatile uint16_t b = 0;
        for(;;)
        {
                b++;
                d++;
                TarefaEspera(100);
                //TarefaSuspende(2);
        }   	
}