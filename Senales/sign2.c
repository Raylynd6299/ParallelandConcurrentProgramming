#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

#define NUM_PROC 4
#define N 128

void procesoHijo(int );
void procesoPadre(pid_t*);
void manejador(int);

int main () {
	register int np=0;
	pid_t pid[NUM_PROC];


	printf("Probando Señales...\n");
	
		if ( signal (SIGUSR1,manejador) == SIG_ERR  ){
			perror("Error en el manejador");
			exit(EXIT_FAILURE);
		}

	for(np = 0;np < NUM_PROC; np++){
		pid[np] = fork();
		if (pid[np] == -1) {
			perror("Error al crear al proceso\n");
			exit(EXIT_FAILURE);	
		}
	
		if(!pid[np]){
			procesoHijo(np);
		}
	}
	
	procesoPadre(pid);

	return 0;	

}

void manejador(int sig){
	if (sig == SIGUSR1){
		printf("señal de usuario 1 recibida en el manejador...\n");
	}
}

void procesoPadre(pid_t *pids){
	pid_t pid;
	int status;
	
	for (int np=0;np < NUM_PROC;np++){
		kill(pids[np],SIGUSR1);
			
		sleep(3);	
		pid = wait(&status);
		printf("Proceso hijo %d con pid: %d, regresa: %d \n",np,pid,status>>8);
	}
}	

void procesoHijo(int np) {
	
	printf("Proceso hijo %d ejecutando con pid: %d\n",np, getpid());	

	pause();
	printf("Se recibio una señal en el proceso hijo\n");

	exit(np);
}
