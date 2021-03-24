#!/bin/bash

#SBATCH --partition=cluster
#SBATCH --job-name=paralelo2
#SBATCH --output=paralelo_matriz2.out
#SBATCH --error=paralelo_matriz2.err
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=32
#SBATCH --time=0-2:00
#SBATCH --hint=compute_bound
#SBATCH --exclusive

#Carrega os módulos do sistema
rm paralelo_matriz_time2.txt
module load compilers/gnu/7.3
module load compilers/intel/2018.2.199
eval $loadIntelLibs

#Compila o código
gcc -std=c99 -g -Wall -fopenmp -o paralelo_matriz_omp2 paralelo_matriz_omp2.c

tentativas=15 #Quantas vezes o código será executado

for cores in 2 4 8 16 32 #número de cores utilizados
do
	for size in 1400 1550 1700 1800 #tamanho do problema			
	do   									
		echo -e "\n$cores\t$size\t\t\c" >> "paralelo_matriz_time2.txt" 
			
		for tentativa in $(seq $tentativas) #Cria uma vetor de 1 a "tentativas"				
		do
			echo -e `./paralelo_matriz_omp2 $cores $size`	#$cores como número de processos e $size como tamanho da matriz						
		done			
	done
done	
		
exit 
