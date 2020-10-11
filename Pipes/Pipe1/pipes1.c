#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_PROC 4

void procesoHijo(int,int* );
void procesoPadre(int*);

int main () {
	register int np=0;
	pid_t pid;
	int pipefd[2],estado;
	printf("Probando Procesos...\n");
	
	estado = pipe(pipefd);	
	if (estado == -1 ){
		perror("Error al crear el pipe\n");
		exit(EXIT_FAILURE);	
	}
	for(np = 0;np < NUM_PROC; np++){
		pid = fork();
		if (pid == -1) {
			perror("Error al crear al proceso\n");
			exit(EXIT_FAILURE);	
		}
	
		if(!pid){
			
			procesoHijo(np,pipefd);
		}
	}
	
	procesoPadre(pipefd);
	return 0;	

}

void procesoPadre(int *pipefd){
	pid_t pid;
	int status,numproc,res;
	for (register int np=0;np < NUM_PROC;np++){
		pid = wait(&status);
		read(pipefd[0],&res,sizeof(int));
		numproc = status >> 8;
		if (numproc == 0){
			printf("Termino el proceso %d, \n",numproc);	
			printf("La suma %d \n",res);
		}else if(numproc == 1){
			printf("Termino el proceso %d, \n",numproc);	
			printf("La resta %d \n",res);
		}else if(numproc == 2){
			printf("Termino el proceso %d, \n",numproc);	
			printf("La multi %d \n",res);
		}else if(numproc == 3){
			printf("Termino el proceso %d, \n",numproc);	
			printf("La divi %d \n",res);
		}
		printf("Proceso hijo %d con pid: %d, regresa: %d \n",np,pid,status>>8);
	}
}	

void procesoHijo(int np,int* pipefd) {
	int resta,numero1 =20, numero2=4,suma,multi,divi;
	close(pipefd[0]);
	if (np == 0){
		suma = numero1 +numero2;
		write( pipefd[1] , (void*)&suma , sizeof(int) );
		close(pipefd[1]);
	}else if(np == 1){
		resta = numero1-numero2;		
		write( pipefd[1] , (void*)&resta , sizeof(int) );
		close(pipefd[1]);
	}else if(np == 2){
		multi = numero1 * numero2;
		write( pipefd[1] , (void*)&multi , sizeof(int) );
		close(pipefd[1]);
	}else{
		divi = numero1 / numero2;
		write( pipefd[1] , (void*)&divi , sizeof(int) );
		close(pipefd[1]);
	}
	exit(np);
}
