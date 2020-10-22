#include "defs.h"
#include <stdio.h>


void BubbleSort(int* datos){
	int aux;
	for(int p = 0;p < N; p++){
		for(int i = 0; i < N-1 ; i++ ){
			if( *(datos+i) > *(datos+i+1)){
				aux = *(datos+i);
				*(datos+i) = *(datos+i+1);
				*(datos+i+1) = aux;
			}
		}
	}
}

void MultiplicacionVectorial(int* datos){
	for (int i = 0; i<N;i++){
		(*(datos+i)) = (*(datos+i)) * C;
	}
}

int obtenerPromedio(int* datos){
    int prom = 0;
    for (int i = 0; i < N; i++){
        prom += *(datos+i);
    }
	prom /= N;
	return prom;
}

int obtenerNumPares(int* datos){
    int numPares=0;
    for (int i = 0; i<N; i++){
		if(*(datos+i) %2 == 0){
			numPares++;		
        }
	}
	return numPares;
}