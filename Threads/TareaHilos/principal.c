#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>


#include "defs.h"
#include "helper.h"
#include "hilos.h"

int *datos;
int promedio,pares,primos;
pthread_mutex_t bloqueo;

int main () {
	pthread_t threadsArray[NUM_THREAD];	
	int hilosNum[NUM_THREAD];

	printf("Tarea de Hilos");	

	srand(getpid());
	datos = reservarMemoria();	
	llenarArreglo(datos);
	imprimirArreglo(datos);

	pthread_mutex_init(&bloqueo,NULL);

	for(int numTh = 0; numTh < NUM_THREAD; numTh++){
		hilosNum[numTh] = numTh;
		pthread_create((threadsArray+numTh),NULL,funcThread,(void *)(hilosNum+numTh));
	}

	for(int numTh = 0; numTh < NUM_THREAD; numTh++){
		pthread_join(*(threadsArray+numTh),NULL);
	}
	
	printf("El resultado de ordenar el arreglo por el Hilo 0 es:\n");
	imprimirArreglo(datos);
	printf("El promedio del arreglo es %d fue calculado por el Hilo 1 \n",promedio);
	printf("En el arreglo hay %d numeros Pares esto fue calculado por el Hilo 2 \n",pares);
	printf("En el arreglo hay %d numeros Primos esto fue calculado por el Hilo 3 \n",primos);

	
	free(datos);
	pthread_mutex_destroy(&bloqueo);
	return 0;	

}
