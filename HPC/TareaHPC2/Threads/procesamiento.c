#include <math.h>
#include "defs.h"

void generarHann(float *hann) {
	
	float a0 = 0.5, a1 = 0.5;
	register int n;
	
	for(n = 0; n < N ; n ++ ) {
		*(hann+n) = a0 - a1*(cosf( (2*M_PI*n)/(N-1) ));
    }
}