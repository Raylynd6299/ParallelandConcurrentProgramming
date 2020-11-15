#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include "defs.h"

extern int *A,*B,producto;

void procesoHijo( int np, int pipefd[] ){

	int elemBloque = N / NUM_PROC;
	int inicioBloque = np * elemBloque;
	int finBloque = inicioBloque + elemBloque; 
	int results=0;
	close( pipefd[0] );
	for(int i = inicioBloque; i < finBloque ; i++ ){
		results += A[i] * B[i];
	}
	write( pipefd[1], &results, sizeof(int) );

	close( pipefd[1] );
	exit( np );
}

void procesoPadre( int pipefd[NUM_PROC][2] ){
	
	register int np;
	pid_t pid;
	int estado, numproc;
	int res= 0;
	for( np = 0; np < NUM_PROC; np++ ){
		pid = wait(&estado);
		numproc = estado >> 8;
		close( pipefd[numproc][1] );
		read( pipefd[numproc][0], &res, sizeof(int) );
		producto += res;
		printf("Termino el proceso %d con pid: %d \n", numproc, pid);
		close( pipefd[numproc][0] );
	}
}
