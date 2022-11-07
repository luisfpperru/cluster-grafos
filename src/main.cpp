#include <stdio.h> // biblioteca padrão
#include <stdlib.h> // biblioteca padrão
#include <time.h> // usada no cronômetro e no gerador aleatório
#include "basicMQ.cpp" // avaliação
//#include "turboMQ.cpp" // avaliação
#include "ConstrucaoAleatoria.cpp" // construção
#include "BuscaLocal.cpp" // busca
//#include "perturbar2.cpp" // perturbação
//#include "unir_e_dividir.cpp" // perturbação
#include "explodir_e_dividir.cpp" // perturbação


using namespace std; // altera o espaço de trabalho para o padrão

void salvar(char *nome_arquivo_saida, int n_nos,int *group_numbers,float f,float tempo_exec)
{
	FILE *arquivo;
	arquivo = fopen(nome_arquivo_saida,"wt"); // wt - write text rt - read text  a - append
	if (arquivo == NULL)
	{
		printf("\n\n Nao foi possivel escrever o arquivo!! \n\n");
		exit(0);
	}
	fprintf(arquivo,"%f\n",f);
	for (int i = 0; i < n_nos; i++)
		fprintf(arquivo,"%d %d\n",i,group_numbers[i]);
	fprintf(arquivo,"%f\n",tempo_exec);
	fclose(arquivo);
}
int main(int argc, char *argv[]){

	if (argc < 7)
		exit(0);

	// declara as variáveis

  	int n_nos,n_arestas,n_classes = atoi(argv[3]),max_it = atoi(argv[4]),*arestas; // atoi() converte string para inteiro
	float chance_buscar = atof(argv[5]),chance_perturbar = atof(argv[6]),*peso_arestas;     // atof() converte string para float
	bool cond = 0; // condição de exibir detalhes na tela

	if (max_it < 0)
	{
		printf("\n\n Número de iteracoes não deve ser negativo. \n\n");
		exit(0);
	} 

	if (chance_buscar < 0 | chance_buscar > 1 )
	{
		printf("\n\n Valor de parametro chance_buscar incoerente. \n\n");
		exit(0);
	} 

	if (chance_perturbar < 0 | chance_perturbar > 1 )
	{
		printf("\n\n Valor de parametro chance_perturbar incoerente. \n\n");
		exit(0);
	} 

	// Ler arquivo de texto
	
	FILE *arquivo;
	arquivo = fopen(argv[1],"rt");	       // abre arquivo no modo leitura
					      // wt - write text, rt - read text,  a - append
	if (arquivo == NULL)
	{
		printf("\n\n Nao foi possivel ler o arquivo de entrada!! \n\n"); // falha em ler o arquivo
		exit(0);
	}

	fscanf(arquivo,"%d",&n_nos); 		// lê arquivo: linha 1 - número de vértices,
	fscanf(arquivo,"\n%d",&n_arestas);       //            linha 2 - número de arestas
	
	arestas = (int *) malloc(2*n_arestas*sizeof(int)); // vetor que armazena os vértices de cada aresta
	peso_arestas = (float *) malloc(n_arestas*sizeof(float)); // vetor que armazena os pesos de cada aresta
	for (int i = 0; i < n_arestas; i++)
	{
		fscanf(arquivo,"\n%d",&arestas[2*i]); // leia o primeiro vertice da aresta
		while (arestas[2*i] < 0 || arestas[2*i] >= n_nos)
		{
			printf("\n\n Numeracao de nos incoerente. Entre com o primeiro no da aresta %d  novamente: \n\n",i);
			scanf("%d",&arestas[2*i]);
		}
		fscanf(arquivo," %d",&arestas[2*i+1]); // leia o segundo vertice da aresta
		while (arestas[2*i+1] < 0 || arestas[2*i+1] >= n_nos)
		{
			printf("\n\n Numeracao de nos incoerente. Entre com o segundo no da aresta %d  novamente: \n\n",i);
			scanf("%d",&arestas[2*i+1]);
		}
		fscanf(arquivo," %f\n",&peso_arestas[i]); // leia o peso daquela aresta
	}
	fclose(arquivo); // fecha arquivo

	if (n_classes > n_nos)
	{
		printf("\n\n Número de classes deve ser menor do que o número de nós. \n\n");
		exit(0);
	}

 
	// Alocando espaço para os vetores de classificação dos nós (group_numbers) e do tamanho de cada grupo (group_size)
	int *group_numbers,*group_size,*best_group_numbers,*best_group_size;
	group_numbers = (int *) malloc(n_nos*sizeof(int));
	group_size = (int *) malloc(n_classes*sizeof(int));

	clock_t inicio, fim;  // variáveis usadas no cronômetro
	inicio = clock(); // inicializa cronômetro 

	// 2) CONSTRUIR UMA SOLUÇÃO INICIAL VÁLIDA: 
	Construir(n_nos,n_classes,group_numbers,group_size);
	best_group_numbers = group_numbers;
	best_group_size = group_size;	

	// 3) AVALIAR A SOLUÇÃO 
	float f,bestf;
	f = Avaliar(n_arestas,n_classes,arestas,peso_arestas,group_numbers,group_size);
	bestf = f;	
	if (cond == 1)
		printf("\n\n A solução após a construcao eh: %f \n\n",f);

	// 4) EXECUTAR A BUSCA LOCAL NA SOLUÇÃO
	Busca_Local(n_nos,n_arestas,n_classes,arestas,peso_arestas,group_numbers,group_size,chance_buscar);

	// 5) AVALIAR A NOVA SOLUÇÃO (após a busca local)
	
	f = Avaliar(n_arestas,n_classes,arestas,peso_arestas,group_numbers,group_size);
	if (cond == 1)
		printf("\n\n A solução após a busca local eh: %f \n\n",f); 
	// salva a melhor solução
	if (f > bestf){
		bestf = f;
		best_group_numbers = group_numbers;
		best_group_size = group_size;
	}
	int it = 0; 
	while (it < max_it) // Fase Iterativa
	{
   		// 6) PERTURBAR A SOLUÇÃO
		Perturbar(n_nos,n_classes,group_numbers,group_size,chance_perturbar);

   		// 7) AVALIAR A NOVA SOLUÇÃO (após a perturbação)
		f = Avaliar(n_arestas,n_classes,arestas,peso_arestas,group_numbers,group_size);
		if (cond == 1)
			printf("\n\n A solução após a perturbacao eh: %f \n\n",f);
		// salva a melhor solução
		if (f > bestf){
			bestf = f;
			best_group_numbers = group_numbers;
			best_group_size = group_size;
		}

   		// 8) EXECUTAR A BUSCA LOCAL 
		Busca_Local(n_nos,n_arestas,n_classes,arestas,peso_arestas,group_numbers,group_size,chance_buscar);

   		// 9) AVALIAR A NOVA SOLUÇÃO (após a busca local)
		f = Avaliar(n_arestas,n_classes,arestas,peso_arestas,group_numbers,group_size);
		if (cond == 1)
			printf("\n\n A solução após a nova busca local eh: %f \n\n",f);

		// salva a melhor solução
		if (f > bestf){
			bestf = f;
			best_group_numbers = group_numbers;
			best_group_size = group_size;
		}

		it++;
	}


    	fim = clock(); // finaliza cronômetro
    	float tempo_exec = ( (float) (fim - inicio))/CLOCKS_PER_SEC ; // armazena tempo de execução
	
	if (cond == 1) 
		printf("\n\n A melhor solução final eh: %f \n\n",bestf);
	
	// Gravar solução em arquivo de texto
	salvar(argv[2],n_nos,best_group_numbers,bestf,tempo_exec);

  	return 0;
}
