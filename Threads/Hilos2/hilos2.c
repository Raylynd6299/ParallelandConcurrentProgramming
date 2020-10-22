#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREAD 4

void* funcThread(void*);

void main(){
	pthread_t threadsArray[NUM_THREAD];	
	int hilosNum[NUM_THREAD],*resul[NUM_THREAD];
	
	printf("Ejemplo de hilos2\n");

	for(int numTh = 0; numTh < NUM_THREAD; numTh++){
		hilosNum[numTh] = numTh;
		pthread_create((threadsArray+numTh),NULL,funcThread,(void *)(hilosNum+numTh));
	}
	
	for(int numTh = 0; numTh < NUM_THREAD; numTh++){
		pthread_join(*(threadsArray+numTh),(void **)&(*(resul+numTh)));
	}
	
	for(int numTh = 0; numTh < NUM_THREAD; numTh++){
		printf("El resultado del hilos %d es: %d \n",numTh,*(*(resul+numTh)));
	}
			
}

void* funcThread(void *arg){
	int tipohilo = *(int*)arg;
	int num1 = 20, num2 = 4;
	int *res = (int *)malloc(sizeof(int));
	
	if(tipohilo == 0){
		(*res) = num1 + num2;
	}else if(tipohilo == 1){
		*res = num1 - num2;
	}else if(tipohilo == 2){
		*res = num1 * num2;
	}else if(tipohilo == 3){
		*res = num1 / num2;
	}

	pthread_exit((void*)res);
}
