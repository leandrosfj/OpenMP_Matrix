#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

void print(int** matriz, int n_size);

int main(int argc, char* argv[])
{
	
	int n_size;  
  	int **A, **B, **C;
 	int i,j,r;
	srand(0); 
	struct timeval start, stop;

	n_size = strtol(argv[1], NULL, 10);
   	
	//aloca as matrizes
	A = (int **)malloc(n_size * sizeof(int*));
	B = (int **)malloc(n_size * sizeof(int*));
	C = (int **)malloc(n_size * sizeof(int*));

	for (i=0; i<n_size; i++)
  	{
    	A[i] = (int *)malloc(n_size * sizeof(int));
    	B[i] = (int *)malloc(n_size * sizeof(int));
    	C[i] = (int *)malloc(n_size * sizeof(int));
	}

	//preenche as matrizes
  	for (i=0; i<n_size; i++)
  	{			
    	for (j=0; j<n_size; j++)
    	{
      		A[i][j] = rand()%10;
      		B[i][j] = rand()%10;
      		C[i][j] = 0;
   		}
	}

	gettimeofday(&start, NULL);

	//multiplicação das matrizes
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

	gettimeofday(&stop, NULL);                  

  	//Abre o arquivo txt
   	char arquivo[] = "serial_matriz_time.txt";
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
