#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct equipe{
	char nome_equipe[30];
	int num_tentativas;
	float dist_alvo;
	int situacao;
};
struct no2 { 
       struct equipe dado;
       struct no2 *prox;
};

typedef struct no2* tipofila;

void INIT2(tipofila*inicio, tipofila*fim)
{
*inicio = NULL;
*fim = NULL;
}

int IsEmpty2(tipofila inicio,tipofila fim)
{
if ((inicio==NULL) && (fim == NULL))
  return(1);
else
  return(0);
}

void ENQUEUE(tipofila *inicio,tipofila *fim, struct equipe v)
{
tipofila aux;
aux=(tipofila) malloc (sizeof(struct no2));
if (aux!=NULL)
	{
	aux->dado=v;
	aux->prox=NULL;
	if (IsEmpty2(*inicio,*fim)){
	  *inicio=aux;
	  }
	else{
	  (*fim)->prox=aux;
	  }
   *fim=aux;
	}
else
	printf("overflow \n");
}


int DEQUEUE (tipofila *inicio,tipofila *fim, struct equipe *v)
{
tipofila aux;
aux = *inicio;
if (!IsEmpty2(*inicio,*fim))
     {
     *v=(*inicio)->dado;
     *inicio=(*inicio)->prox;
     if(*inicio==NULL)
       *fim=NULL;
     free(aux);
     return(1);
     }
else
     {
     printf("fila vazia \n ");
     return(0);
     }
}
