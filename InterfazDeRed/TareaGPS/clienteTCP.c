#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PUERTO 5000
#define TAM_BUFFER 100
#define DIR_IP "127.0.0.1"

typedef struct GPS{
    char *UTCPosition;
    char *Latitud;
    char *NoS;
    char *Longitude;
    char *EoW;
    char *GPSQuality;
    char *NumoSatile;
    char *horizontalDilution;
    char *AntenaAltitude;
    char *UnitsoAntenna;
    char *Geoidal;
    char *UnitsoGeoidal;
    char *AgeoDifferential;
    char *DifferentialID;
}gps;

int main(int argc, char **argv){

	int tamano_direccion, sockfd;
	struct sockaddr_in direccion_servidor;
	char leer_mensaje[TAM_BUFFER];
	int numRes=0;
	gps *Res;
	memset (&direccion_servidor, 0, sizeof(direccion_servidor));
	direccion_servidor.sin_family = AF_INET;
	direccion_servidor.sin_port = htons(PUERTO);


	if( inet_pton(AF_INET, DIR_IP, &direccion_servidor.sin_addr) <= 0 ){
		perror("Ocurrio un error al momento de asignar la direccion IP");
		exit(1);
	}

	printf("Creando Socket ....\n");
	if( (sockfd = socket (AF_INET, SOCK_STREAM, 0)) < 0 ){
		perror("Ocurrio un problema en la creacion del socket");
		exit(1);
	}


	printf ("Estableciendo conexion ...\n");
	if( connect(sockfd, (struct sockaddr *)&direccion_servidor, sizeof(direccion_servidor) ) < 0){
		perror ("Ocurrio un problema al establecer la conexion");
		exit(1);
	}


	printf ("Recibiendo Numero de Respuestas ...\n");
	if (read (sockfd, &numRes, sizeof(int)) < 0){	
		perror ("Ocurrio algun problema al recibir datos del cliente");
		exit(1);
	}

	for (int opciones = 0; opciones < numRes; opciones++){
		for(int datos = 0; datos < 5; datos++){
			if (read (sockfd, leer_mensaje, TAM_BUFFER) < 0){	
				perror ("Ocurrio algun problema al recibir datos del cliente");
				exit(1);
			}
			printf("%s\n",leer_mensaje);
			memset(leer_mensaje,0,TAM_BUFFER);
		}
	}
	
	printf ("Cerrando la aplicacion cliente\n");

	/*
	*	Cierre de la conexion
	*/
	
	close(sockfd);

	return 0;
}
	
