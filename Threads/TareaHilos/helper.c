#include <stdlib.h>
#include <stdio.h>
#include "defs.h"


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
		printf("%3d ",*(datos+n));
	}
	printf("\n");
}