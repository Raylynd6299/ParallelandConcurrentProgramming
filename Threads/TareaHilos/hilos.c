#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "procesamiento.h"
#include "defs.h"
#include "helper.h"

extern int *datos;
extern int promedio,pares,primos;
extern pthread_mutex_t bloqueo;

void* funcThread(void *arg){
	int tipohilo = *(int*)arg;
	
	if(tipohilo == 0){
        pthread_mutex_lock(&bloqueo);
		BubbleSort(datos);
        pthread_mutex_unlock(&bloqueo);
	}else if(tipohilo == 1){
        pthread_mutex_lock(&bloqueo);
		promedio = obtenerPromedio(datos);
        pthread_mutex_unlock(&bloqueo);
	}else if(tipohilo == 2){
        pthread_mutex_lock(&bloqueo);
		pares = obtenerNumPares(datos);
        pthread_mutex_unlock(&bloqueo);
	}else if(tipohilo == 3){
        pthread_mutex_lock(&bloqueo);
		primos = obtenerNumPrimos(datos);
        pthread_mutex_unlock(&bloqueo);
	}

	pthread_exit(arg);
}