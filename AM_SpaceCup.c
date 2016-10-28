/*
-----------------GRUPO----------------
INTEGRANTES
74251 - BRUNO SOL� MARTELLO
74083 - FL�VIO VIEIRA DE MACEDO FILHO
74509 - GIOVANNI COUTINHO BERNINI
74604 - OTAVIO BERNARDO NASCIMENTO
73869 - PEDRO ALLEFF COSTA SILVA
 -------------------------------------
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tipopilhaINT.h"
#include "tipofilaEQUIPE.h"

#define N 5 //NUMERO DE GRUPOS A SER CADASTRADOS

//ESTRUTURA DE DADOS DO VETOR LAN�AMENTO, DECLARADO NA BIBLIOTECA TIPOLISTA.h
//struct equipe{
//	char nome_equipe[30];
//	int num_tentativas;
//	float dist_alvo;
//	int situacao;
//};
//ESTRURURA DE DADOS DA PILHA PODIO, DECLARADO NA BIBLIOTECA TIPOPILHASUCESSO.h

//struct sucesso{
//	char nome_equipe[30];
//	int num_tentativas;
//	float dist_alvo;
//};

//FUN��O QUE � REALIZADA QUANDO O LAN�AMENTO FOI REALIZADO COM SUCESSO
//ATUALIZANDO AS INFORMA��ES DA EQUIPE
struct equipe lancamentoEfetuado(struct equipe lancamento){
	printf("----------LANCAMENTO EFETUADO-----------\n");
	printf("----------EQUIPE %s-----------\n",lancamento.nome_equipe);
	printf("Qual a distancia do alvo?\n");
	scanf("%f", &lancamento.dist_alvo);
	lancamento.num_tentativas=lancamento.num_tentativas + 1;
	lancamento.situacao=1;
	return lancamento;
}

//FUN��O QUE � REALIZADO QUANNDO O LAN�AMENTO NAO OBTEVE SUCESSO
//ATUALIZA O NUMERO DE TENTATIVAS E VERIFICA SE NAO ESGOTOU AS TENTATIVAS DA EQUIPE, GERANDO A DESCCLASSIFICA��O
struct equipe lancamentoNaoEfetuado(struct equipe lancamento){
	printf("----------LANCAMENTO NAO EFETUADO-----------\n");
	printf("----------EQUIPE %s-----------\n",lancamento.nome_equipe);
	if(lancamento.num_tentativas<3){
		lancamento.num_tentativas=lancamento.num_tentativas + 1;
	}
	if(lancamento.num_tentativas==3){
		printf("\nEquipe %s desclassificada!\n",lancamento.nome_equipe);
		lancamento.situacao=-1;
	}
	return lancamento;
}

int main() {
//DECLARA��O DE VARIAVEIS 
tipofila inicioLancamento,fimLancamento;
//INICIALIZA A FILA	
INIT2(&inicioLancamento, &fimLancamento);
//
struct equipe lancamento, lanAux;
int i,x,aux,t,y;
int situacao, valInva = 0;
struct sucesso podio,podioFinal;
int continua=1;
float menorDist;
//
tipopilha pilhaPodio;
//INICIALIZA A PILHA
INIT(&pilhaPodio);

//REALIZAR A INSCRI��O DAS EQUIPES
for(i=0; i<N; i++){
		printf("Nome da Equipe:");
		fflush(stdin);
	    gets(lancamento.nome_equipe);
	    lancamento.num_tentativas=0;
	    lancamento.dist_alvo = 0;
	    lancamento.situacao=0;
	    ENQUEUE(&inicioLancamento,&fimLancamento,lancamento);
	}

//LOOP QUE CONTROLA OS LANCAMENTOS, ATE TODOS SEREM REALIZADOS OU DESCLASSIFICADOS 
//MENU QUE PERMITE ESCOLHER SE O LAN�AMENTO FOI EFETUADO OU NAO
//CHAMANDO AS RESPECTIVAS FUN��ES, DE ACORDO COM O QUE FOI SELECIONADO
while(continua==1){
	continua = 0;
	for(i=0; i<N; i++){
		//RETIRA DA FILA
		DEQUEUE(&inicioLancamento,&fimLancamento,&lancamento);
		//DO PARA VERIFICAR QUE FOI ESCOLHIDO UMA OP��O VALIDA
		do{
			if(lancamento.situacao==0){
				printf("\nEQUIPE: %s \n",lancamento.nome_equipe);
				printf("Qual a situacao do lancamento?\n");
				printf("1-Lancamento Efetuado.\n");
				printf("2-Lancamento Nao Efetuado.\n");
				scanf("%d",&situacao);
				if(situacao==1){
					lancamento = lancamentoEfetuado(lancamento);
					valInva = 1;
				}else if(situacao==2){
					lancamento = lancamentoNaoEfetuado(lancamento);
					continua = 1;
					valInva = 1; 
				}else{
					printf("Valor Inserido Invalido!");
					valInva = 0;
				}
			}	
		}while(valInva == 0);
		//ADCIONA DE VOLTA A FILA DEPOIS DO LANCAMENTO
		//SE A EQUIPE FOR DESCLASSIFICADA NAO ADCIONA A FILA
		if(lancamento.situacao != -1){
			ENQUEUE(&inicioLancamento,&fimLancamento,lancamento);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//LOOP QUE VERIFICA O LAN�AMENTO MAIS PROXIMO DO ALVO
//EM CASO DE EMPATE VERIFICA NUMERO DE TENTATIVAS
//INSERINDO EM UMA PILHA PARA CLASSIFICAR A POSI��O DAS EQUIPES 
for(t=0; t<3; t++){
	menorDist=10000000;
	aux=0;
	for(x=0; x<N; x++){
		//RETIRA DA FILA
		DEQUEUE(&inicioLancamento,&fimLancamento,&lancamento);
		//EM CASO DE DISTANCIA IGUAIS COMPARAR QTD DE TENTATIVAS
		if(lancamento.dist_alvo==menorDist && lancamento.situacao==1){
			if(lancamento.num_tentativas < lanAux.num_tentativas){
				menorDist=lancamento.dist_alvo;
				lanAux = lancamento;
				
			}else{
				menorDist= lanAux.dist_alvo;
			}
		}
		//APENAS COMPARA��O DE DISTANCIA
		if(lancamento.dist_alvo < menorDist && lancamento.situacao==1){
			menorDist=lancamento.dist_alvo;
			lanAux = lancamento;
			
		}
		//ADCIONA DE VOLTA A FILA DEPOIS DO LANCAMENTO
		ENQUEUE(&inicioLancamento,&fimLancamento,lancamento);			
	}
	//FOR PARA ATRIBUIR O VALOR 0 A SITUA�AO DO LANCAMENTO NA FILA
	for(x=0; x<N; x++){
		//COMPARA A STRUTURA AUX COM A LISTA E MUDA A SITUA��O DO LANCAMENTO DA LISTA
		DEQUEUE(&inicioLancamento,&fimLancamento,&lancamento);
		if(strcmp(lanAux.nome_equipe,lancamento.nome_equipe) == 0 && lanAux.num_tentativas == lancamento.num_tentativas && lanAux.dist_alvo == lancamento.dist_alvo && lanAux.situacao == lancamento.situacao){
			lancamento.situacao = 0;
		}
		ENQUEUE(&inicioLancamento,&fimLancamento,lancamento);			
	}
	
	//CRIACAO DE UMA VARIAVEL PARA SER INSERIDA NA PILHA 
	//VARIAVEL COM MELHOR LANCAMENTO
	strcpy(podio.nome_equipe, lanAux.nome_equipe);
	podio.num_tentativas=lanAux.num_tentativas;
	podio.dist_alvo=lanAux.dist_alvo;
	//FUN��O PARA INSERIR NA PILHA
	PUSH(&pilhaPodio, podio);
}

printf("\n\n\n");



//LOOP PARA DESCARREGAR PILHA E IMPRIMIR A POSI��O DAS 3 MELHORES EQUIPES 
//GERANDO ASSIM A CLASSIFCA��O FINAL EM RELA��O AOS LAN�AMENTOS  
for(y=3; y>0; y--){
	POP(&pilhaPodio,&podioFinal);
	printf("%d Lugar - Equipe %s - %d Tentativa(s) - %0.2f Distancia do Alvo\n",y,podioFinal.nome_equipe, podioFinal.num_tentativas, podioFinal.dist_alvo);
}
//FIM
system("pause");
}
	
