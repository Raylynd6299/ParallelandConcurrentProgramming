#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_PROC 4
#define N 16

void proceso_padre( int pipefd[NUM_PROC][2] );
void proceso_hijo( int np, int pipefd[] );
int* reservarMemoria();
void llenarArreglo(int* );
void imprimirArreglo(int* datos);

int *A,promedio=0;


int main() {

	pid_t pid;
	register int np;
	int pipefd[NUM_PROC][2], edo_pipe;

	A = reservarMemoria();
	
	llenarArreglo(A);
	
	imprimirArreglo(A);
	
	
	printf("Probando procesos...\n");

	for( np = 0; np < NUM_PROC; np++ ) 	{
		edo_pipe = pipe( &pipefd[np][0] );
		if( edo_pipe == -1 ){
			perror("Error al crear la tuberia...\n");
			exit(EXIT_FAILURE);
		}

		pid = fork();
		if( pid == -1 ){
			perror("Error al crear el proceso...\n");
			exit(EXIT_FAILURE);
		}
		if( !pid )	{
			proceso_hijo( np, &pipefd[np][0] );
		}
	}
	proceso_padre( pipefd );
	printf("El promedio es: %d",promedio/N);
	free(A);
	
	return 0;
}

void proceso_padre( int pipefd[NUM_PROC][2] ) {

	register int np;
	pid_t pid;
	int estado, numproc;
	int elemeBloque = N/NUM_PROC;
	int inicio;
	int sum=0;
	for( np = 0; np < NUM_PROC; np++ ) 	{

		pid = wait(&estado);
		numproc = estado >> 8;
		close( pipefd[numproc][1] );
		read( pipefd[numproc][0], &sum, sizeof(int) );
		promedio +=sum;
		printf("Termino el proceso %d con pid: %d \n", numproc, pid);
		close( pipefd[numproc][0] );
	}
}


void proceso_hijo( int np, int pipefd[] ) {

	int elemBloque = N / NUM_PROC;
	int inicioBloque = np * elemBloque;
	int finBloque = inicioBloque + elemBloque; 
	
	close( pipefd[0] );
	for(int i = inicioBloque; i < finBloque ; i++ ){
		promedio += A[i];
	}

	write( pipefd[1],&promedio, sizeof(int) );

	close( pipefd[1] );
	exit( np );
}

int* reservarMemoria(){
	int* mem = NULL;	
	mem = (int*)malloc(sizeof(int)*N);
	if (mem == NULL){
		perror("Error al obtener memoria...\n");
		exit(EXIT_FAILURE);
	}
	return mem;
}
void llenarArreglo(int* datos){
	for (register int n = 0;n < N;n++){
		*(datos+n) = rand()%256;	
	}
}

void imprimirArreglo(int* datos){
	for(register int n=0; n<N ; n++){
		if(!(n%16))
			printf("\n");
		printf("%5d ",*(datos+n));
	}
	printf("\n");
}
