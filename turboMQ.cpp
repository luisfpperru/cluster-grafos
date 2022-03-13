#include <stdio.h> // biblioteca padrão
#include <stdlib.h> // biblioteca padrão
#include <time.h> // usada no cronômetro e no gerador aleatório

using namespace std; // altera o espaço de trabalho para o padrão

// Função de avaliação Turbo MQ
float Avaliar2(int n_arestas,int n_classes,int *arestas,float *peso_arestas,int *group_numbers, int *group_size) 
{
	float *conect = (float *) malloc(n_classes*n_classes*sizeof(float)); // vetor de conexão de cada classe i com classe j
	for (int i = 0; i < n_classes ; i++)
	{
		for (int j = 0; j < n_classes; j++)
			conect[n_classes*i + j] = 0.0; // zera vetor conect
	}
	for (int i = 0; i < n_arestas; i++) 
	{
	        // incrementa as conexões das classes dos nos destino e origem de uma dada aresta
		conect[n_classes*group_numbers[arestas[2*i]]+ group_numbers[arestas[2*i+1]]] += peso_arestas[i]; 
		conect[n_classes*group_numbers[arestas[2*i+1]] + group_numbers[arestas[2*i]]]+= peso_arestas[i];	
	} 
	float *intra_conect = (float *) malloc(n_classes*sizeof(float)); //intraconectividade 
	float *inter_conect = (float *) malloc( (n_classes - 1)*(n_classes - 1)/2*sizeof(float)); // e interconectividade das arestas
	for (int i = 0; i < n_classes ; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			if (i == j) // soma dos pesos das conexões de i com nós da mesma classe
				intra_conect[i] += conect[n_classes*i + j];
			else  // soma dos pesos das conexões de i com outras classes j
				inter_conect[(i-1)*i/2 +j] += conect[n_classes*i + j];
		}
	}
	float f = 0.0;
	 // calcula funcional Turbo MQ (Modularization Quality)
	for (int i = 0; i < n_classes ; i++)
		f += intra_conect[i]/(intra_conect[i] + 0.5*inter_conect[i]);
	return f;
}
