# Cluster Grafos
 - Projeto prático em C++ para agrupamento de Grafos desenvolvido durante o Mestrado em Modelagem Computacional

### Compilador
 - No projeto eu uso o g++ presente no [Mingw-w64](https://www.mingw-w64.org/downloads/).
 - Qualquer duvida recorrer a [documentação](https://code.visualstudio.com/docs/cpp/config-mingw) para rodar o projeto no VS Code.

### Compilar/Build

g++ main.cpp -o main

### Executar

./main caminho_arquivo_entrada caminho_arquivo_saida n_classes max_it chance_buscar chance_perturbar  

#### Exemplo usando os dados em instancia-1.txt na pasta instancias, com 2 classes, 1000 interações do programa, chance de buscar e perturbar 1.0 e 0.5, respectivamente:  
./main instancias/instancia-1.txt saidas/saida1-2.txt 2 1000 1.0 0.5 

### Arquivo de entrada
O arquivo segue o seguinte padrão: <br>

número_de_nós <br>
número_de_arestas <br>
número_nó_saida número_nó_entrada peso_da_aresta <br>
... <br>

#### <b> Exemplo com <b/> 6 nós, 7 arestas, o nó 0 se liga ao nó 1 com uma aresta de peso 0.9

6 <br>
7 <br>
0 1 0.9 <br>
1 2 0.3 <br>
0 2 0.5 <br>
2 3 0.6 <br>
3 4 0.9 <br>
4 5 0.2 <br>
5 3 0.3 <br>

### Arquivo de saida
O arquivo de saída é construido no seguinte padrão: <br>

avaliação_solução <br>
número_nó classe_do_nó <br>
... <br>
tempo_execução <br>
<br>
Exemplo: <br> 
<br>
0.416667 <br>
0 1 <br>
1 1 <br>
2 1 <br>
3 0 <br>
4 0 <br>
5 1 <br>
6 0 <br>
7 0 <br>
8 0 <br>
9 2 <br>
0.297260 <br>
<br>
No exemplo, como temos 3 classes os nós só podem ser da classe 0, 1 ou 2.
  
### Avaliação da Solução/ Funcional
 - A avaliação da solução é melhor quanto mais próximo de zero estiver. 
 - Seu cálculo é feito usando o funcional MQ (Modularization Quality).
 - o MQ é feito através da diferença da média de arestas externas menos a média das arestas internas de cada classe.
 - Uma aresta interna é aquela que liga a dois nós da mesma classe.
 - Uma aresta externa é aquela que liga dois nós de classes diferentes.
  
