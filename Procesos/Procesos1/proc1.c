#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main () {
	float num1 = 45,num2 = 13,suma,resta;
	pid_t pid;
	int status;

	printf("Probando Procesos...\n");
	
	pid = fork();
	if (pid == -1) {
		perror("Error al crear al proceso\n");
		exit(EXIT_FAILURE);	
	}
	
	if(!pid){
		printf("Proceso hijo ejecutando con PID: %d...\n",getpid());
		suma = num1 + num2;
		printf("El Resultado es: %f \n",suma);
		exit(3);
	}else{
		printf("Proceso Padre con PID: %d \n",getpid());
		resta = num1 -num2;
		printf("La resta es: %f \n",resta);
		pid = wait(&status);
		printf("Proceso terminado con pid: %d y estado: %d\n",pid,status>>8);
	}
}
