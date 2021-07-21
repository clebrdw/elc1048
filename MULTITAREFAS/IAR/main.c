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
	
        /* MODO COOPERATIVO - Temos duas tarefas executando, ambas periódicas de tempo
         * 2ms e 100ms. Assim como está, ambas executam e voltam a dormir, mas caso removemos
         * o Delay da tarefa_1, ela vai ficar eternamente executando e não irá liberar a CPU
         * a menos que se de o comando de Suspender, Continuar ou inserir novamente o dalay.
         * Neste ultimo caso, quando nenhuma das tarefas está executando, a tarefa ociosa
         * entra em acao para ficar gastando CPU.
         
         * No Cooperativo temos menor preocupação com recursos compartilhados e funcoes nao reentrantes 
         * pelo motivo de que a tarefa so troca de contexto quando estiver pronta.
         */ 

	/* Nunca chega aqui */
	while (1)
	{
	}
}

/* Tarefas de exemplo que usam funcoes para suspender/continuar as tarefas */
void tarefa_1(void)
{
	for(;;)
	{
                c++;
                TarefaEspera(2);
                //TarefaSuspende(1);                
	}
}
/*
 * tarefa 2 tem maior prioridade e tempo de espera de 100ms
 * 
 */
void tarefa_2(void)
{
        for(;;)
        {
                d++;
                TarefaEspera(100);
                //TarefaSuspende(2);
        }   	
}