#include <stdio.h> // biblioteca padrão
#include <stdlib.h> // biblioteca padrão
#include <time.h> // usada no cronômetro e no gerador aleatório

using namespace std; // altera o espaço de trabalho para o padrão

void Perturbar2(int n_nos,int n_classes,int *group_numbers,int *group_size, float chance_perturbar)
{
	srand( (unsigned)time(NULL) ); // inicia gerador aleatório
	int classe;
	for (int no = 0; no < n_nos; no++) // para todos os nós
	{
		if (group_size[ group_numbers[no] ] > 1) // se o grupo não ficar vazio...
		{
			if (rand() % 100 < 100*chance_perturbar) // ... e com certa probabilidade...
			{
				group_size[ group_numbers[no] ]--; 
				do 
					classe = rand() % n_classes; // garante que a classe é diferente da atual
				while (classe == group_numbers[no] );
				group_numbers[no] = classe; // sorteia uma classe e altera a classe do nó em questão
				group_size[group_numbers[no] ]++; 
			}
		}
	}
}
void Perturbar(int n_nos,int n_classes,int *group_numbers,int *group_size, float chance_perturbar)
{
	srand( (unsigned)time(NULL) ); // inicia gerador aleatório

	if ( rand() % 100 < 100*chance_perturbar)
		Perturbar2(n_nos,n_classes,group_numbers,group_size,chance_perturbar);
}
