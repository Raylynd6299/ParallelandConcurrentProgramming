#include <stdio.h>
#include "archivos.h"
#include "procesamiento.h"
#include "defs.h"

int main() {
	float seno[MUESTRAS]; 
    
	generaSeno( seno );
	guardarDatos( seno );

	return 0;
}