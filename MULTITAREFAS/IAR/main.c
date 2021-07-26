#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "multitarefas.h"

/*
 * Prototipos das tarefas
 */
void produtor(void);
void consumidor(void);

/*
 * Configuracao dos tamanhos das pilhas
 */
#define TAM_PILHA_1		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_2		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_OCIOSA	(TAM_MINIMO_PILHA + 24)
#define TAM_BUFFER               5

/*
 * Declaracao das pilhas das tarefas
 */
uint32_t PILHA_PRODUTOR[TAM_PILHA_1];
uint32_t PILHA_CONSUMIDOR[TAM_PILHA_2];
uint32_t PILHA_TAREFA_OCIOSA[TAM_PILHA_OCIOSA];
/*
 * Declaracao das variaveis utilizadas no problema do produtor e consumidor
 */
semaforo_t cheio = {0, NULL};
semaforo_t vazio = {TAM_BUFFER, NULL};

uint32_t buffer[TAM_BUFFER];
uint8_t i=0, j=0, valor_lido;

/*
 * Funcao principal de entrada do sistema
 */
int main(void)
{
	
	/* Criacao das tarefas */
	/* Parametros: ponteiro, nome, ponteiro da pilha, tamanho da pilha, prioridade da tarefa */
	
	CriaTarefa(produtor, "Produtor", PILHA_PRODUTOR, TAM_PILHA_1, 2);
	
	CriaTarefa(consumidor, "Consumidor", PILHA_CONSUMIDOR, TAM_PILHA_2, 1);
        
	/* Cria tarefa ociosa do sistema */
	CriaTarefa(tarefa_ociosa,"Tarefa ociosa", PILHA_TAREFA_OCIOSA, TAM_PILHA_OCIOSA, 0);
        
        printf("Criou as tarefas");
	
	/* Configura marca de tempo */
	ConfiguraMarcaTempo();   
	
	/* Inicia sistema multitarefas */
	IniciaMultitarefas();
	
	/* Nunca chega aqui */
	while (1)
	{
	}
}

void produtor(){
  
  while(1){ 
  // decrementa semaforo 'vazio'. Se vazio.contador for < 0, o buffer esta cheio e nao produz mais, troca de contexto
    SemaforoAguarda(&vazio);    // vazio.contador-- e testa
    
    buffer[i]=rand()%10;        // produz um valor aleatorio para o buffer, funcao produz()
    
    i++;
    if(i == TAM_BUFFER)         
      i=0;                      // volta para a primeira posicao do buffer
 
  // incrementa semaforo 'cheio' indicando que produziu algo
    SemaforoLibera(&cheio);     // cheio.contador++;
  // Tarefa faz uma leitura a cada 10ms
    TarefaEspera(10);
  }
}

void consumidor(){
  
  while(1){
  // decrementa semaforo 'cheio'. Se cheio.contador for < 0, nao tem nada pra consumir e troca de contexto
    SemaforoAguarda(&cheio);    // cheio.contador-- e testa
  
    valor_lido = buffer[j];     // consome um valor do buffer
    
    j++;
    if(j == TAM_BUFFER)         
      j=0;                      // volta para a primeira posicao do buffer
    
  // incrementa semaforo 'vazio' indicando que consumiu algo
    SemaforoLibera(&vazio);     // vazio.contador++;
  }
}     