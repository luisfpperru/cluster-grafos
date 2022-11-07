#!/bin/bash
g++ src/main.cpp -o main
exec=./main
for i in {1..4}
do 
  for k in {2..4} 
  do 
    $exec input/dataset$i.txt output/output-$i-$k.txt $k 10 1.0 0.5; 
    # ./nome_do_programa nome_arquivo_entrada.txt nome_arquivo_saida.txt n_classes max_it chance_buscar chance_perturbar  
  done
done
