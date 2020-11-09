#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include "defs.h"

extern float *info,*Hann,*producto;

void procesoHijo( int np, int pipefd[] ){

	int elemBloque = N / NUM_PROC;
	int inicioBloque = np * elemBloque;
	int finBloque = inicioBloque + elemBloque; 

	close( pipefd[0] );
	for(int i = inicioBloque; i < finBloque ; i++ ){
		producto[i] = info[i] * Hann[i];
	}

	write( pipefd[1], producto+inicioBloque, sizeof(float)*elemBloque );

	close( pipefd[1] );
	exit( np );
}

void procesoPadre( int pipefd[NUM_PROC][2] ){
	
	register int np;
	pid_t pid;
	int estado, numproc;
	int elemeBloque = N/NUM_PROC;
	int inicio;
	for( np = 0; np < NUM_PROC; np++ ){

		pid = wait(&estado);
		numproc = estado >> 8;
		close( pipefd[numproc][1] );
		inicio = numproc * elemeBloque;
		read( pipefd[numproc][0], producto+inicio, sizeof(float)*elemeBloque );
		printf("Termino el proceso %d con pid: %d \n", numproc, pid);
		close( pipefd[numproc][0] );
	}
}
