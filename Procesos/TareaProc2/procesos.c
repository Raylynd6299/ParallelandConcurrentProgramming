#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "procesamiento.h"
#include "defs.h"
#include "helper.h"


void procesoPadre(int pipefd[][2]){
	pid_t pid;
	int status;
    int res;
    int *buffer = reservarMemoria();

	for (int np=0;np < NUM_PROC;np++){
        close(pipefd[np][1]);
		pid = wait(&status);
        if((status>>8) == 0){
            read(pipefd[0][0],(void*)buffer,sizeof(int)*N);
            printf("Proceso hijo %d con pid: %d, regresa el arreglo ordenado de menor a mayor por BubbleSort \n",status>>8,pid);
            imprimirArreglo(buffer);
        }else if((status>>8) == 1){
            read(pipefd[1][0],(void*)&res,sizeof(int));
            printf("Proceso hijo %d con pid: %d, regreso que el promedio del arreglo es : %d \n",status>>8,pid,res);
        }else if((status>>8) == 2){ 
            read(pipefd[1][0],(void*)&res,sizeof(int)); 
            printf("Proceso hijo %d con pid: %d, regreso que existen %d numeros pares en el arreglo \n",status>>8,pid,res);
        }else if((status>>8) == 3){
            read(pipefd[3][0],(void*)buffer,sizeof(int)*N);
            printf("Proceso hijo %d con pid: %d, regresa el arreglo original multiplicado por %d \n",status>>8,pid,C);
            imprimirArreglo(buffer);
        }
	}
}	

void procesoHijo(int np,int* pipefd) {
	int numPares,promedio;
    int *buffer = reservarMemoria();
    read(pipefd[0],(void*)buffer,sizeof(int)*N);
    close(pipefd[0]);
	if (np == 0){
		BubbleSort(buffer);
        write(pipefd[1],(void*)buffer,sizeof(int)*N);		
	}else if(np == 1){
		promedio = obtenerPromedio(buffer);
        write(pipefd[1],(void*)&promedio,sizeof(int));		
	}else if(np == 2){
        numPares = obtenerNumPares(buffer);
        write(pipefd[1],(void*)&numPares,sizeof(int));		
    }else if(np == 3){
        MultiplicacionVectorial(buffer);
        write(pipefd[1],(void*)buffer,sizeof(int)*N);
    }
    close(pipefd[1]);
	exit(np);
}
