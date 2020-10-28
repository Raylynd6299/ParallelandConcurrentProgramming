#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_HILOS 4

void * funHilo( void *arg );
int res_sum,res_res,res_mul,res_div;
int contador = 0;

int main(){

	register int nh;
	pthread_t tids[NUM_HILOS];
	int *hilo, nhs[NUM_HILOS];

	printf("Ejemplo de hilos\n");

	for( nh = 0; nh < NUM_HILOS; nh++ )
	{
		nhs[nh] = nh;
		//nhs[0] = 0;
		//nhs[1] = 1;
		//nhs[2] = 2;
		//nhs[3] = 3;
		pthread_create( &tids[nh] , NULL, funHilo, (void *)&nhs[nh] );
	}

	for( nh = 0; nh < NUM_HILOS; nh++ ){
		pthread_join( tids[nh], (void **)&hilo );
			printf("Hilo %d terminado \n", *hilo);
	}

	return 0;
}

void * funHilo( void *arg ){
	int nh = *(int *)arg;
	register int i = 0;
	contador ++;

	printf("Hilo %d en ejecución con contador %d \n", nh,contador);
	
	while((--i));
	//sleep(1);

	printf("Hilo %d en ejecución con contador %d \n", nh,contador);
	
	pthread_exit( arg );
}


