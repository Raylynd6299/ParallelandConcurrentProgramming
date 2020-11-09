#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

float* leerArchivo(){
    FILE *archivo;
    float* datos =NULL;
    datos = (float *)malloc(sizeof(float) * N);
    if (datos ==NULL){
        perror("Error al obtener espacio");
        exit(EXIT_FAILURE);
    }
    archivo = fopen("PulseSensor.dat","r");
    if (archivo == NULL){
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }
    for(int indi = 0; indi < N; indi++){
        fscanf(archivo,"%f",(datos+indi));
    }
    fclose(archivo);
    return datos;
}

void guardarDatos(float *datos,char *nombre){
	
	FILE *apArch;
	
	apArch = fopen(nombre,"w");
	if (apArch == NULL ) {
		perror("Error al abrir el archivo");
		exit(EXIT_FAILURE);		
	}
	for(int n = 0; n < N; n++ ) {
		fprintf(apArch,"%f \n",*(datos+n));
	}
	fclose(apArch);
	
}