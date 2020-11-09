#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

#define NUM_HILOS 4
#define N 16

void * funHilo( void * arg );
int *A,promedio = 0;
pthread_mutex_t bloqueo;

int * reservarMemoria();
void llenarArreglo( int *datos );
void imprimirArreglo( int *datos );

int main()
{
	int *hilo;
	pthread_t tids[NUM_HILOS];
	int nhs[NUM_HILOS];
	register int nh;

	pthread_mutex_init(&bloqueo,NULL);

	A = reservarMemoria();

	llenarArreglo( A );

	imprimirArreglo( A );

	printf("Probando hilos...\n");

	for( nh = 0; nh < NUM_HILOS; nh++ )	{

		nhs[nh] = nh;
		pthread_create( &tids[nh], NULL, funHilo,(void*) &nhs[nh] );
	}

	for( nh = 0; nh < NUM_HILOS; nh++ ){

		pthread_join( tids[nh],  (void **)&hilo);
		printf("El hilo %d termino \n", *hilo );
	}
	
	printf("El promedio es: %d",promedio/N);
	pthread_mutex_destroy(&bloqueo);
	free(A);

	return 0;
}

void * funHilo( void * arg ){
	int nucleo = *(int *)arg;
	register int i;
	int suma = 0;

	printf("Hilo %d en ejecucion \n", nucleo);

	for( i = nucleo; i < N; i += NUM_HILOS ){
		suma += A[i];
	}

	pthread_mutex_lock(&bloqueo);
	promedio += suma;
	pthread_mutex_unlock(&bloqueo);

	pthread_exit( arg );
}

void imprimirArreglo( int *datos )
{
	register int i;

	for( i = 0; i < N; i++ )
	{
		if( !(i%16) )
			printf("\n");
		printf("%3d ", datos[i]);
	}
	printf("\n\n");
}

void llenarArreglo( int *datos )
{
	register int i;

	for( i = 0; i < N; i++ )
	{
		datos[i] = rand() % 256;
	}
}

int * reservarMemoria()
{
	int *mem;

	mem = (int *)malloc( N*sizeof(int) );
	if( !mem )
	{
		perror("Error al asignar memoria\n");
		exit(EXIT_FAILURE);
	}

	return mem;
}

