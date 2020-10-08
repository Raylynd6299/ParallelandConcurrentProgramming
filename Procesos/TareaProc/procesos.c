#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "procesamiento.h"
#include "defs.h"


void procesoPadre(){
	pid_t pid;
	int status;
	for (int np=0;np < NUM_PROC;np++){
		pid = wait(&status);
        if(np == 0){
            printf("Proceso hijo %d con pid: %d, regresa como el como numero mayor del arreglo: %d \n",np,pid,status>>8);
        }else if(np == 1){
            printf("Proceso hijo %d con pid: %d, regresa como numero menor del arreglo: %d \n",np,pid,status>>8);
        }else if(np == 2){  
            printf("Proceso hijo %d con pid: %d, regresa como promedio: %d \n",np,pid,status>>8);
        }else{
            printf("Proceso hijo %d con pid: %d, regresa que existen %d numeros pares en el arreglo \n",np,pid,status>>8);
        }
	}
}	

void procesoHijo(int np,int* datos) {
	int mayor,menor,numPares,promedio;
    
	if (np == 0){
		mayor = buscarMayor(datos);
		exit(mayor);
	}else if(np == 1){
		menor = buscarMenor(datos);
		exit(menor);
	}else if(np == 2){
        promedio = obtenerPromedio(datos);
        exit(promedio);
    }else if(np == 3){
        numPares = obtenerNumPares(datos);
        exit(numPares);
    }
	exit(np);
}
