#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MUESTRAS  512

void generaSeno(float[]);
void guardarDatos (float[]) ;

int main() {
	float seno[MUESTRAS];
	generaSeno( seno );
	guardarDatos( seno );

	return 0;
}

void guardarDatos(float datos[]){
	
	FILE *apArch;
	
	apArch = fopen("seno.dat","w");
	if (apArch == NULL ) {
		perror("Error al abrir el archivo");
		exit(EXIT_FAILURE);		
	}
	for(int n = 0; n < MUESTRAS; n++ ) {
		fprintf(apArch,"%f \n",datos[n]);
	}
	fclose(apArch);
	
}

void generaSeno(float seno[]) {
	
	float f = 1000, fs = 45000;
	register int n;
	// Lenguaje C tiene 3 especificadores de acceso:
	// register : Incarle al compilador que reserve un registro para almacenar la variable en lugar de una direccion de memoria.
	// static   : Se usa para declarar variables locales con alcance global. Su valor no se pierde cuando sale de la funcion.
	// extern   : Se usa cuando tengo un programa en varios modulos y necesito utilizar una variable en un modulo X que ha sido declarada en un modulo Y
	

	for(n = 0; n < MUESTRAS ; n ++ ) {
		seno[n] = sinf( 2*M_PI*f*n/fs);
	}

}
