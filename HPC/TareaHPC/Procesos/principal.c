#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "defs.h"
#include "procesos.h"
#include "procesamiento.h"
#include "helper.h"
#include "archivos.h"

float *info,*Hann,*producto;

int main(){
    
    pid_t pid;
	register int np;
	int pipefd[NUM_PROC][2], edo_pipe;

    info = leerArchivo();
    Hann = reservarMemoria();
    producto = reservarMemoria();

    generarHann(Hann);

    imprimirArreglo(info);
    imprimirArreglo(Hann);
    guardarDatos(Hann,"Hann.dat");

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
	imprimirArreglo(producto);

    guardarDatos(producto,"resultado.dat");

    free(info);
    free(Hann);
    free(producto);
    return (0);
}