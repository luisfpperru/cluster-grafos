#include <stdio.h> // biblioteca padrão
#include <stdlib.h> // biblioteca padrão
#include <time.h> // usada no cronômetro e no gerador aleatório

using namespace std; // altera o espaço de trabalho para o padrão

int melhor_classe(int no,int n_classes,int n_arestas,int *group_numbers,int *arestas,float *peso_arestas) // retorna a melhor classe para o no pertencer
{
	srand( (unsigned)time(NULL) ); // inicia gerador aleatório
	int classe;
	float *group_arestas,maior;
	group_arestas = (float *)malloc(n_classes*sizeof(float)); // aloca espaço
	for (int i = 0; i < n_classes; i++)
		group_arestas[i] = 0;
	for (int j = 0; j < n_arestas; j++) // conta o número total de ligações de cada grupo de nós com o nó em questão
	{
		if (arestas[2*j] == no)
			group_arestas[group_numbers[arestas[2*j+1] ] ]+= peso_arestas[j];
		if (arestas[2*j+1] == no)
			group_arestas[group_numbers[arestas[2*j] ] ]+= peso_arestas[j];
	}
	maior = group_arestas[0], classe = 0;
	for (int i = 1; i < n_classes; i++)
	{
		if ( group_arestas[i] > maior)
		{
			maior = group_arestas[i]; // armazena o valor do maior
			classe = i;  // armazena a classe com maior número de arestas ligadas ao nó sorteado
		}
	}
	return classe;
}
void Busca_Local(int n_nos,int n_arestas,int n_classes, int *arestas,float *peso_arestas, int *group_numbers,int *group_size, float chance_buscar)
{
	for (int no = 0; no < n_nos ; no++){
		if (group_size[ group_numbers[no] ] > 1) // se o grupo não ficar vazio...
		{
			if (rand() % 100 < 100*chance_buscar)  // ... e com certa probabilidade...
			{	
				group_size[ group_numbers[no] ]--; 
				group_numbers[no] = melhor_classe(no,n_classes,n_arestas,group_numbers,arestas,peso_arestas); // ...e altera a classificação do nó para o grupo com mais arestas
				group_size[group_numbers[no]]++;
			} 
		}		 	
	}
}
