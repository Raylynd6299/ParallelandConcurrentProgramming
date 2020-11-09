#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

float* reservarMemoria(){
	float* mem = NULL;	
	mem = (float*)malloc(sizeof(float)*N);
	if (mem == NULL){
		perror("Error al obtener memoria...\n");
		exit(EXIT_FAILURE);
	}
	return mem;
}

void imprimirArreglo(float* datos){
	for(register int n=0; n<N ; n++){
		if(!(n%16))
			printf("\n");
		printf("%0.3f ",*(datos+n));
	}
	printf("\n");
}
