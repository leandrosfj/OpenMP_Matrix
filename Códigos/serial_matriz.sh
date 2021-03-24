#!/bin/bash

#SBATCH --partition=cluster
#SBATCH --job-name=serial
#SBATCH --output=serial_matriz.out
#SBATCH --error=serial_matriz.err
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=32
#SBATCH --time=0-2:00
#SBATCH --hint=compute_bound
#SBATCH --exclusive

#Carrega os módulos do sistema
rm serial_matriz_time.txt
module load compilers/gnu/7.3
module load compilers/intel/2018.2.199
eval $loadIntelLibs

#Compila o código
gcc -std=c99 serial_matriz.c -o serial_matriz

tentativas=15 #Quantas vezes o código será executado
			
for size in 1400 1550 1700 1800 #tamanho do problema
do   									
	echo -e "\n$size\t\t\c" >> "serial_matriz_time.txt"
		
	for tentativa in $(seq $tentativas) #Cria uma vetor de 1 a "tentativas"
	do
		echo -e `./serial_matriz $size`						
	done					
done
	
exit 


