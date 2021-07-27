#include <stdint.h>
#include <stdio.h>
#include "multitarefas.h"
/*
 * Prototipos das tarefas
 */
void tarefa1(void);
void tarefa2(void);
void tarefa3(void);
void tarefa4(void);
void tarefa5(void);
void imprime(void);

/*
 * Configuracao dos tamanhos das pilhas
 */
#define TAM_PILHA_1		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_2		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_3		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_4		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_5		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_6		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_OCIOSA	(TAM_MINIMO_PILHA + 24)

/*
 * Declaracao das pilhas das tarefas
 */
uint32_t PILHA_TAREFA1[TAM_PILHA_1];
uint32_t PILHA_TAREFA2[TAM_PILHA_2];
uint32_t PILHA_TAREFA3[TAM_PILHA_3];
uint32_t PILHA_TAREFA4[TAM_PILHA_4];
uint32_t PILHA_TAREFA5[TAM_PILHA_5];
uint32_t PILHA_TAREFA6[TAM_PILHA_6];
uint32_t PILHA_TAREFA_OCIOSA[TAM_PILHA_OCIOSA];
/*
 * Declaracao das variaveis utilizadas no benchmark
 */

uint32_t i=0, j=0, k=0, l=0, m=0, total=0;

/*
 * Funcao principal de entrada do sistema
 */
int main(void)
{	
	/* Criacao das tarefas */
	/* Parametros: ponteiro, nome, ponteiro da pilha, tamanho da pilha, prioridade da tarefa */
	
	CriaTarefa(tarefa1, "Tarefa1", PILHA_TAREFA1, TAM_PILHA_1, 5);
        
        CriaTarefa(tarefa2, "Tarefa2", PILHA_TAREFA2, TAM_PILHA_2, 4);

	CriaTarefa(tarefa3, "Tarefa3", PILHA_TAREFA3, TAM_PILHA_3, 3);
        
        CriaTarefa(tarefa4, "Tarefa4", PILHA_TAREFA4, TAM_PILHA_4, 2);
        
        CriaTarefa(tarefa5, "Tarefa5", PILHA_TAREFA5, TAM_PILHA_5, 1);
        
        CriaTarefa(imprime, "Imprime", PILHA_TAREFA6, TAM_PILHA_6, 6);
        
        // Coloca as tarefas 1,2,3 e 4 em espera, caso contrario, as variaveis contadoras
        // irão incrementar de forma errada. EX: i=4, j=3, k=2, l=1, m=0 
        TCB[1].estado = ESPERA;
        TCB[2].estado = ESPERA;
        TCB[3].estado = ESPERA;
        TCB[4].estado = ESPERA;    
        
	/* Cria tarefa ociosa do sistema */
	CriaTarefa(tarefa_ociosa,"Tarefa ociosa", PILHA_TAREFA_OCIOSA, TAM_PILHA_OCIOSA, 0);
	
	/* Configura marca de tempo */
	ConfiguraMarcaTempo();   
	
	/* Inicia sistema multitarefas */
	IniciaMultitarefas();
	
	/* Nunca chega aqui */
	while (1)
	{
	}
}

void tarefa1(){
  
        while(1){ 
              i++;
              TarefaSuspende(1);        //Suspende ela mesma
        }
}

void tarefa2(){
  
        while(1){ 
              j++;
              TarefaContinua(1);        // Continua a proxima tarefa de maior prioridade
              TarefaSuspende(2);        // Suspende ela mesma
        }
}  

void tarefa3(){
  
        while(1){ 
              k++;              
              TarefaContinua(2);        // Continua a proxima tarefa de maior prioridade
              TarefaSuspende(3);        // Suspende ela mesma
        }
}

void tarefa4(){
  
        while(1){ 
              l++;
              TarefaContinua(3);        // Continua a proxima tarefa de maior prioridade          
              TarefaSuspende(4);        // Suspende ela mesma
        }
} 

void tarefa5(){
  
        while(1){ 
              m++;
              TarefaContinua(4);        // Continua a proxima tarefa de maior prioridade
        }
} 

void imprime(){
  
        while(1){ 
              total = i+j+k+l+m;
              // Espera 30seg ate fazer a soma novamente
              // Simulando e cronometrando, 1500 ticks equivale a 30segundos no meu notebook
              TarefaEspera(1500);        
        }
}