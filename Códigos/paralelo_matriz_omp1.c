/*
 *	Multiplicacao de matrizes em OpenMP
 *	
 *	Codigo 1 - OpenMP utilizando #pragma omp for
 *
 *	Leandro S. Ferreira
 *	Lucas F Lucena
 *
 */

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <omp.h>


void print(int** matriz, int n_size);

int main(int argc, char* argv[]) 
{

	int m_threads, n_size;  
    int **A, **B, **C;
	int i,j,r;
	srand(0);
	struct timeval start, stop;

   	m_threads = strtol(argv[1], NULL, 10);
   	n_size = 	strtol(argv[2], NULL, 10);

	//Aloca as matrizes
	A = (int **)malloc(n_size * sizeof(int*));
	B = (int **)malloc(n_size * sizeof(int*));
	C = (int **)malloc(n_size * sizeof(int*));
	
	for (i=0; i<n_size; i++)
	{
    	A[i] = (int *)malloc(n_size * sizeof(int));
    	B[i] = (int *)malloc(n_size * sizeof(int));
    	C[i] = (int *)malloc(n_size * sizeof(int));
	}

	#pragma omp parallel num_threads(m_threads) default(none) shared(A, B, C, n_size, start, stop) private(i, j, r)
	{	
		//Preenche as matrizes
		#pragma omp for schedule(static) 
		for (i=0; i<n_size; i++)
		{			
      		for (j=0; j<n_size; j++)
      		{
         		A[i][j] = rand()%10;
         		B[i][j] = rand()%10;
         		C[i][j] = 0;
   			}
		}
		#pragma omp barrier

		//Tempo Inicial
		#pragma omp single
		{
			gettimeofday(&start, NULL);
		}

		//Calcula matriz C	
		#pragma omp for schedule(static) 
		for (i=0; i<n_size; i++)
		{
    		for (j=0; j<n_size; j++)
    		{	
        		for(r=0; r<n_size; r++)
        		{
        			C[i][j] += A[i][r] * B[r][j];
        		}       	 
    		}

   		}
   		#pragma omp barrier

   		//Tempo final
   		#pragma omp single
		{
			gettimeofday(&stop, NULL);
		}
	}                               

   	//Abre o arquivo txt
   	char arquivo[] = "paralelo_matriz_time1.txt";
    FILE *fp;     
    fp = fopen(arquivo, "a");                 
       
    //Salva o tempo de execução na tabela
    if (fp == NULL) exit(1);
    else 
    {
		fprintf(fp, "%.3f\t", (stop.tv_sec + stop.tv_usec*1e-6)-(start.tv_sec + start.tv_usec*1e-6));
        fclose(fp);     
    }

    print(A, n_size);

	//Libera matrizes
	for (i=0; i<n_size; i++)
	{
    	free(A[i]);
		free(B[i]);
		free(C[i]);
	}

	free(A);
	free(B);
	free(C);

	return 0;
}

void print(int** matriz, int n_size)
{
	for (int i=0; i<n_size; i++)
	{
    	for (int j=0; j<n_size; j++)
    	{
        	printf("%d \t",matriz[i][j]);
		}

		printf("\n");
	}

	printf("\n");
}
