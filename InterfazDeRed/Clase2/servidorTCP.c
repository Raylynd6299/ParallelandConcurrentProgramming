#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <signal.h>


#define PUERTO 			5000	//Número de puerto asignado al servidor
#define COLA_CLIENTES 	5 		//Tamaño de la cola de espera para clientes
#define TAM_BUFFER 		100
#define EVER 1

// Definicion de Funciones
void manejador(int);
void proceso_cliente(int);
void iniServidor();
void iniSignals();

int sockfd;

int main(int argc, char **argv){
	pid_t pid;
   	int  cliente_sockfd;

	iniSignals();

	iniServidor();
   	
	for(;EVER;){
		printf ("En espera de peticiones de conexión ...\n");
		if( (cliente_sockfd = accept(sockfd, NULL, NULL)) < 0 )	{
			perror("Ocurrio algun problema al atender a un cliente");
			exit(1);
		}
		pid = fork();
		if (!pid){
			/*
			*	Inicia la transferencia de datos entre cliente y servidor
			*/

			proceso_cliente(cliente_sockfd);
		}
	}
	
	printf("Concluimos la ejecución de la aplicacion Servidor \n");
	

   	close (sockfd);

	return 0;
}


void iniSignals(){
	if(signal(SIGCHLD,manejador) == SIG_ERR){
		perror("Error en el manejador");
		exit(EXIT_FAILURE);
	}
	if(signal(SIGINT,manejador) == SIG_ERR){
		perror("Error en el manejador");
		exit(EXIT_FAILURE);
	}
}
void iniServidor(){

   	struct sockaddr_in direccion_servidor; 

	memset (&direccion_servidor, 0, sizeof (direccion_servidor));	
   	direccion_servidor.sin_family 		= AF_INET;
   	direccion_servidor.sin_port 		= htons(PUERTO);
   	direccion_servidor.sin_addr.s_addr 	= INADDR_ANY;


   	printf("Creando Socket ....\n");
   	if( (sockfd = socket (AF_INET, SOCK_STREAM, 0)) < 0 ){
		perror("Ocurrio un problema en la creacion del socket");
		exit(1);
   	}


   	printf("Configurando socket ...\n");
   	if( bind(sockfd, (struct sockaddr *) &direccion_servidor, sizeof(direccion_servidor)) < 0 ){
		perror ("Ocurrio un problema al configurar el socket");
		exit(1);
   	}

	
   	printf ("Estableciendo la aceptacion de clientes...\n");
	if( listen(sockfd, COLA_CLIENTES) < 0 ){
		perror("Ocurrio un problema al crear la cola de aceptar peticiones de los clientes");
		exit(1);
   	}

}

void proceso_cliente(int cliente_sockfd){

	char leer_mensaje[TAM_BUFFER];

	printf("Se aceptó un cliente, atendiendolo \n");
	if( read (cliente_sockfd, &leer_mensaje, TAM_BUFFER) < 0 ){
		perror ("Ocurrio algun problema al recibir datos del cliente");
		exit(1);
	}
	printf ("El cliente nos envio el siguiente mensaje: \n %s \n", leer_mensaje);

	if( write (cliente_sockfd, "Bienvenido cliente", 19) < 0 ){
		perror("Ocurrio un problema en el envio de un mensaje al cliente");
		exit(1);
	}

	/*
	*	Cierre de las conexiones
	*/

	//kill(getppid(),SIGUSR1);
	close (cliente_sockfd);
	exit(0);
}

void manejador(int sig){
	int estado;
	pid_t pid;
	if (sig == SIGCHLD){
		printf("señal de usuario 1 recibida en el manejador...\n");
		pid = wait(&estado);
		printf("Termino la conexion\n");
	}
	if (sig == SIGINT){
		printf("Programa Terminando");
		close(sockfd);
		exit(EXIT_SUCCESS);
	}
}