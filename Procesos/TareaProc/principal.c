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

	printf("Tarea de Procesos");	

	srand(getpid());
	datos = reservarMemoria();	
	llenarArreglo(datos);
	imprimirArreglo(datos);
	for(np = 0;np < NUM_PROC; np++){
		pid = fork();
		if (pid == -1) {
			perror("Error al crear al proceso\n");
			exit(EXIT_FAILURE);	
		}
	
		if(!pid){
			procesoHijo(np,datos);
		}
	}
	procesoPadre();
	free(datos);
	return 0;	

}
