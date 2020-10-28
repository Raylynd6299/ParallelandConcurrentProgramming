#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_HILOS 4

void * funHilo( void *arg );
int res_sum,res_res,res_mul,res_div;
int num1 = 20, num2 = 4;

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
		if (*hilo == 0){
			printf("Resultado: %d \n", res_sum);
		}else if (*hilo == 1){
			printf("Resultado: %d \n", res_res);
		}else if (*hilo == 2){
			printf("Resultado: %d \n", res_mul);
		}else if (*hilo == 3){
			printf("Resultado: %d \n", res_div);
		}
	}

	return 0;
}

void * funHilo( void *arg ){
	int nh = *(int *)arg;



	printf("Hilo %d en ejecución \n", nh);
	if( nh == 0 )
		res_sum = num1 + num2;
	else if( nh == 1 )
		res_res = num1 - num2;
	else if( nh == 2 )
		res_mul = num1 * num2;
	else if( nh == 3 )
		res_div = num1 / num2;

	pthread_exit( arg );
}


