#include "defs.h"
#include <stdio.h>


int buscarMayor(int* datos){
	int mayor = *datos;
	for(int i = 1;i<N;i++){
		if(*(datos+i) > mayor){
			mayor = *(datos+i);
		}
	}
	return mayor;
}

int buscarMenor(int* datos){
	int menor = *datos;

	for (int i = 1; i<N;i++){
		if(*(datos+i) < menor){
			menor = *(datos+i);
		}
	}
	return menor;
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