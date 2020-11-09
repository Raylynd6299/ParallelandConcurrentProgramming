#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "defs.h"
#include "procesos.h"
#include "procesamiento.h"
#include "helper.h"
#include "archivos.h"

float *info,*Hann,*producto;

int main(){

    int *hilo;
	pthread_t tids[NUM_HILOS];
	int nhs[NUM_HILOS];
	register int nh;

    info = leerArchivo();
    Hann = reservarMemoria();
    producto = reservarMemoria();

    generarHann(Hann);

    //imprimirArreglo(info);
    //imprimirArreglo(Hann);
    guardarDatos(Hann,"Hann.dat");

    printf("Tarea de Hilos...\n");

    for( nh = 0; nh < NUM_HILOS; nh++ ){
		nhs[nh] = nh;
		pthread_create( &tids[nh] , NULL, funHilo, (void *)&nhs[nh] );
	}

    for( nh = 0; nh < NUM_HILOS; nh++ ){
		pthread_join( tids[nh], (void **)&hilo );
		printf("El hilo %d termino \n",*hilo);
	}

    //imprimirArreglo(producto);

    guardarDatos(producto,"resultado.dat");

    free(info);
    free(Hann);
    free(producto);
    return 0;
}

