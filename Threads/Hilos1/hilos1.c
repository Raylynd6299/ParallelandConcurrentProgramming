#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* suma(void*);
void* resta(void*);
void* multi(void*);
void* divi(void*);

void main(){
	pthread_t t_suma,t_resta,t_multi,t_divi;	
	int* res_suma,*res_resta,*res_multi,*res_divi;
	
	printf("Ejemplo de hilos\n");

	pthread_create(&t_suma,NULL,suma,NULL);
	pthread_create(&t_resta,NULL,resta,NULL);
	pthread_create(&t_multi,NULL,multi,NULL);
	pthread_create(&t_divi,NULL,divi,NULL);
	
	pthread_join(t_suma,(void **)&res_suma);
	pthread_join(t_resta,(void **)&res_resta);
	pthread_join(t_multi,(void **)&res_multi);
	pthread_join(t_divi,(void **)&res_divi);
	
	printf("La suma es: %d \n", *res_suma);
	printf("La resta es: %d \n", *res_resta);
	printf("La multiplicacion es: %d \n", *res_multi);
	printf("La division es: %d \n", *res_divi);
		
}

void* suma(void *arg){
	int num1 = 20, num2 = 4;
	static int res;
	
	res = num1 + num2;

	pthread_exit((void*)&res);
}

void* resta(void *arg){
	int num1 = 20, num2 = 4;
	static int res;
	
	res = num1 - num2;

	pthread_exit((void*)&res);
}

void* multi(void *arg){
	int num1 = 20, num2 = 4;
	int *res = (int*) malloc(sizeof(int));
	
	(*res) = num1 * num2;

	pthread_exit((void*)res);
}

void* divi(void *arg){
	int num1 = 20, num2 = 4;
	int *res = (int*) malloc(sizeof(int));
	
	(*res) = num1 / num2;

	pthread_exit((void*)res);
}


