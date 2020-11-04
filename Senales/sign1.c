#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#define EVER 1

void manejador(int sig);

int main(){
	printf("estoy esperando una señal");
	if ( signal(SIGINT,manejador) == SIG_ERR  ) {
		perror("Error en el manejador de SIGINT ");
		exit(EXIT_FAILURE);
	}
	if ( signal(SIGTERM,manejador) == SIG_ERR  ) {
		perror("Error en el manejador de SIGINT ");
		exit(EXIT_FAILURE);
	}

	for(;EVER;)
		pause();
	return 0;
}

void manejador(int sig){
	if (sig == SIGINT)
		printf("No voy a termiinar .... \n");
	else if (sig == SIGTERM)
		printf("Que no entiendes que No voy a termiinar .... \n");
}
