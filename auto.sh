#!/bin/bash
exec=./main
for i in {1..3}
do 
  for k in {2..4} 
  do 
    $exec instancias/instancia-$i.txt saidas/saida-$i-$k.txt $k 10 1.0 0.5; 
    # ./nome_do_programa nome_arquivo_entrada.txt nome_arquivo_saida.txt n_classes max_it chance_buscar chance_perturbar  
  done
done
