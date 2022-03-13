#include <stdio.h> // biblioteca padrão
#include <stdlib.h> // biblioteca padrão
#include <time.h> // usada no cronômetro e no gerador aleatório

using namespace std; // altera o espaço de trabalho para o padrão

// Constroi uma solução aleatoriamente
void Construir(int n_nos,int n_classes,int *group_numbers, int *group_size) //Nova construção rabiscada em sala
{
	int *vm = (int *) malloc(n_nos*sizeof(int));
	for (int i = 0; i < n_classes; i++)
		group_size[i] = 0; // zera vetor de tamanhos das classes
	for (int i = 0; i < n_nos; i++)
		vm[i] = i % n_classes; // classe do vetor auxiliar

	srand( (unsigned)time(NULL) ); // inicia gerador aleatório
	int ch,m = n_nos;
	for (int i = 0; i < n_nos; i++)
	{
		ch = rand() % m; // posição do elemento sorteado do vetor auxiliar
		group_numbers[i] = vm[ch]; // solução recebe elemento sorteado
		group_size[group_numbers[i]]++; // incrementa o tamanho da classe sorteada
		vm[ch] = vm[m-1]; 
		m--; // vetor auxiliar é reduzido
	}
}
