#include <stdio.h> // biblioteca padrão
#include <stdlib.h> // biblioteca padrão
#include <time.h> // usada no cronômetro e no gerador aleatório

using namespace std; // altera o espaço de trabalho para o padrão

// Perturbação de explodir uma classe e dividir uma outra classe 
void explodir_e_dividir(int n_nos,int n_classes,int *group_numbers,int *group_size) 
{
	srand( (unsigned)time(NULL) ); // inicia gerador aleatório
	int classe1,classe2;
	classe2 = rand() % n_classes; // sorteia uma classe para explodir

	// explode uma classe
	for (int i = 0; i < n_nos; i++)
	{
		if (group_numbers[i] == classe2)
		{
			do 
				classe1 = rand() % n_classes; // sorteia uma classe para doar um nó
			while (classe1 == classe2);
			group_numbers[i] = classe1; // inclui nó naquele grupo
			group_size[classe2]--;
			group_size[classe1]++;
		}
	}

	// divisão de uma classe em duas classes
	
	do 
	{
		do 
		{
			classe1 = rand() % n_classes; // sorteia um grupo para dividir
		}while (classe1 == classe2);

		for (int i = 0; i < n_nos && group_size[classe1] > 1; i++)
		{
			if ( group_numbers[i] == classe1 && rand() % 100 < 50)
			{
				group_numbers[i] = classe2; // inclui nó naquele grupo
				group_size[classe2]++;
				group_size[classe1]--;
			}
		}
	}while (group_size[classe2] == 0); // repete o processo enquanto classe2 estiver vazio

}
void Perturbar(int n_nos,int n_classes,int *group_numbers,int *group_size, float chance_perturbar)
{
	srand( (unsigned)time(NULL) ); // inicia gerador aleatório

	if ( rand() % 100 < 100*chance_perturbar)
		explodir_e_dividir(n_nos,n_classes,group_numbers,group_size);
}
