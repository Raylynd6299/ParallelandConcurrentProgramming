#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "defs.h"
#include "helper.h"
#include "procesos.h"



int main () {
	register int np=0;
	pid_t pid;
	int* datos;
	int pipefd[NUM_PROC][2],estado;

	printf("Tarea2 de Procesos");	

	srand(getpid());
	datos = reservarMemoria();	
	llenarArreglo(datos);
	imprimirArreglo(datos);

	for(int npi = 0; npi < NUM_PROC ;npi++){
		estado = pipe(pipefd[npi]);	
		if (estado == -1 ){
			perror("Error al crear el pipe\n");
			exit(EXIT_FAILURE);	
		}
	}

	for(np = 0;np < NUM_PROC; np++){
		pid = fork();
		if (pid == -1) {
			perror("Error al crear al proceso\n");
			exit(EXIT_FAILURE);	
		}
	
		if(!pid){
			write(pipefd[np][1],(void *)datos,sizeof(int)*N);
			procesoHijo(np,pipefd[np]);
		}
	}
	procesoPadre(pipefd);
	free(datos);
	return 0;	

}
