#include <stdio.h> // biblioteca padrão
#include <stdlib.h> // biblioteca padrão
#include <time.h> // usada no cronômetro e no gerador aleatório

using namespace std; // altera o espaço de trabalho para o padrão

// Perturbação que une duas classes e depois as divide de forma aleatória 
void unir_e_dividir(int n_nos,int n_classes,int *group_numbers,int *group_size)
{
	srand( (unsigned)time(NULL) ); // inicia gerador aleatório
	int classe1, classe2; 

	// sorteia duas classes
	do
	{
		classe1 = rand() % n_classes;
		classe2 = rand() % n_classes;
	} while ( classe1 == classe2 && n_classes > 1 );

	// união de duas classes
	for (int i = 0; i < n_nos; i++)
	{
		if (group_numbers[i] == classe2)
		{
			group_numbers[i] = classe1;
			group_size[classe2]--;
			group_size[classe1]++;
		}
	}

	// divisão de uma classe em duas classes
	do 
	{
		for (int i = 0; i < n_nos; i++)
		{
			if ( group_numbers[i] == classe1 && group_size[classe1] > 1 && rand() % 100 < 50)
			{
				group_numbers[i] = classe2;
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
		unir_e_dividir(n_nos,n_classes,group_numbers,group_size);
}
