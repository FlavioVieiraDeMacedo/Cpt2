#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct sucesso{
	char nome_equipe[30];
	int num_tentativas;
	float dist_alvo;
};
struct no { 
	struct sucesso dado;
	struct no *prox;
};

/*Definição do tipo de dado pilha */ 
typedef struct no* tipopilha;

void INIT (tipopilha *topo){
*topo = NULL;
}

int IsEmpty(tipopilha topo){
if (topo == NULL)
   return(1);
else
  return(0);
}

void PUSH (tipopilha *topo, struct sucesso elem){
tipopilha novo;
novo = (tipopilha) malloc (sizeof(struct no));
if (novo != NULL){
	strcpy(novo->dado.nome_equipe, elem.nome_equipe);
	novo->dado.num_tentativas=elem.num_tentativas;
	novo->dado.dist_alvo=elem.dist_alvo;
	novo->prox=*topo;
	*topo = novo;
	}
else
	printf("pilha cheia \n");
}

int POP (tipopilha *topo,struct sucesso *elem){
tipopilha aux;
aux = *topo;
if (!IsEmpty(*topo))   {
	 strcpy(elem->nome_equipe, aux->dado.nome_equipe);
     elem->dist_alvo=aux->dado.dist_alvo;
     elem->num_tentativas=aux->dado.num_tentativas;     
     *topo=aux->prox;
     free(aux);
     return(1);
     }
else {
       printf("pilha vazia \n ");
       return(0);
       }
}

int TOP (tipopilha topo, struct sucesso *elem){
tipopilha aux;
aux = topo;
if (!IsEmpty(topo))   {
	 strcpy(elem->nome_equipe, aux->dado.nome_equipe);
     elem->dist_alvo=aux->dado.dist_alvo;
     elem->num_tentativas=aux->dado.num_tentativas;
     return(1);
     }
else {
       printf("pilha vazia \n ");
       return(0);
       }
}
