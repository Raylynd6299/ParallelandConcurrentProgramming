#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "defs.h"

extern float *info,*Hann,*producto;

void * funHilo( void *arg ){

	int nucleo = *(int *)arg;

	printf("Hilo %d en ejecución \n", nucleo);

	for(int i = nucleo; i < N ; i += NUM_HILOS){
		producto[i] = info[i] * Hann[i];
	}
	pthread_exit( arg );
}