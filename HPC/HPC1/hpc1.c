#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


#define NUM_HILOS 4
#define N 16

void * funHilo( void *arg );
int* reservarMemoria();
void llenarArreglo(int*);
void imprimirArreglo(int*);

int *A,*B,*C;
	
int main(){

	int *hilo;
	pthread_t tids[NUM_HILOS];
	int nhs[NUM_HILOS];
	register int nh;

	A = reservarMemoria();
	B = reservarMemoria();
	C = reservarMemoria();
	//D = reservarMemoria();
	llenarArreglo(A);
	llenarArreglo(B);

 	
	imprimirArreglo(A);	
	imprimirArreglo(B);	
	imprimirArreglo(C);	



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

	for( nh = 0; nh < NUM_HILOS; nh++ )
	{
		pthread_join( tids[nh], (void **)&hilo );
		printf("El hilo %d termino \n",*hilo);
	}

	imprimirArreglo(C);	
	
	free(A);
	free(B);
	free(C);

	return 0;
}
int* reservarMemoria(){
	int* mem = NULL;	
	mem = (int*)malloc(sizeof(int)*N);
	if (mem == NULL){
		perror("Error al obtener memoria...\n");
		exit(EXIT_FAILURE);
	}
	return mem;
}


void llenarArreglo(int* datos){
	for (register int n = 0;n < N;n++){
		*(datos+n) = rand()%256;	
	}
}

void imprimirArreglo(int* datos){
	for(register int n=0; n<N ; n++){
		if(!(n%16))
			printf("\n");
		printf("%3d ",*(datos+n));
	}
	printf("\n");
}

void * funHilo( void *arg ){

	int nucleo = *(int *)arg;
	int eleBloque = N / NUM_HILOS;	
	int inicio = nucleo * eleBloque;
	int fin = inicio + eleBloque;
	printf("Hilo %d en ejecución \n", nucleo);

	for(int i = inicio; i < fin ; i++ ){
		C[i] = A[i] * B[i];
	}
	pthread_exit( arg );
}


