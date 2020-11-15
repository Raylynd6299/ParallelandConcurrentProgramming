#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "defs.h"
#include "procesos.h"
#include "helper.h"
#include "archivos.h"

int *A,*B,producto;

int main(){
    
    pid_t pid;
	register int np;
	int pipefd[NUM_PROC][2], edo_pipe;

    A = reservarMemoria();
	B = reservarMemoria();
    llenarArreglo(A);
	llenarArreglo(B);
	imprimirArreglo(A);
	imprimirArreglo(B);

    printf("Tarea de Procesos...\n");

    for( np = 0; np < NUM_PROC; np++ )	{

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

		if( !pid ){
			procesoHijo( np, &pipefd[np][0] );
		}
	}

    procesoPadre( pipefd );
	printf("El producto punto es:%d",producto);

    free(A);
    free(B);
    return (0);
}