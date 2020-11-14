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


// Definicion de Funciones
void manejador(int);
void proceso_cliente(int);
void iniServidor();
void iniSignals();
gps** ObtenerDatos();
void AsignarCampo(gps* Datos,char* Cadena,int flag);
gps* ProcesarCadena(char *Cadena);

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
gps* ProcesarCadena(char *Cadena){
    gps *Datos=NULL;
    int ind = 0;
    int flag = 0;
    char *aux =NULL;
    //char aux2[100];
    char *aux2 = NULL;
    char *ayu =NULL;

    if (strncmp("$GPGGA",Cadena,6) == 0){
        aux = (char*)realloc(aux,strlen(Cadena)-7);
        memcpy(aux,Cadena+7,strlen(Cadena)-7);
        Datos = (gps*)malloc(sizeof(gps));
        if (Datos == NULL){
            perror("Error al solicitar memoria");
            exit(EXIT_FAILURE);
        }

        while (aux[ind] != '\0'){
            if(aux[ind] == ',' || aux[ind] == '\n'){
                aux2 = (char *)realloc(aux2,strlen(aux));
                memset(aux2,0,strlen(aux));
                memcpy(aux2,aux,ind);
                AsignarCampo(Datos,aux2,flag);
                flag += 1;
                //volvemos a asignar a aux la cadena sin lo asignado
                memset(aux2,0,strlen(aux2));
                memcpy(aux2,aux+ind+1,strlen(aux)-ind-1);
                memset(aux,0,strlen(aux));
                memcpy(aux,aux2,strlen(aux2));
                if ((ayu = (char*)realloc(aux,strlen(aux))) != NULL)aux = ayu;
                ind =0;
            }else{
                ind++;
            }
        }

    }  
    free(ayu);
    free(aux2);
    return Datos;
}
gps** ObtenerDatos(int* Tam){
	FILE *Archivo;
	gps **Res = NULL;
	gps *aux =NULL;
	char *Texto;
	int NumRes=3;
	int ind=0;
	Texto = (char *)malloc(sizeof(char)*100);
	Res = (gps**)malloc(sizeof(gps*)*NumRes);

	if((Archivo = fopen("nmea.txt","r")) == NULL){
		perror("Error al abrir el Archivo");
		exit(EXIT_FAILURE);
	}

	while(fgets(Texto,100,Archivo)){
        aux = ProcesarCadena(Texto);
        if (aux != NULL){
			if (ind < NumRes){
				Res[ind] = aux;
				ind++;
			}else{
				Res = (gps**)realloc(Res,sizeof(gps*)*(NumRes+3));
				NumRes += 3;
				Res[ind] = aux;
				ind++;
			}
        }
    }
	*Tam = ind;
	return Res;
}
void AsignarCampo(gps* Datos,char* Cadena,int flag){
    switch (flag){
        case 0:
            Datos->UTCPosition = (char*)malloc(sizeof(char)*strlen(Cadena));
            memcpy(Datos->UTCPosition,Cadena,strlen(Cadena));
            break;                
        case 1:
            Datos->Latitud = (char*)malloc(sizeof(char)*strlen(Cadena));
            memcpy(Datos->Latitud,Cadena,strlen(Cadena));
            break;
        case 2:
            Datos->NoS = (char*)malloc(sizeof(char)*strlen(Cadena));
            memcpy(Datos->NoS,Cadena,strlen(Cadena));
            break;
        case 3:
            Datos->Longitude = (char*)malloc(sizeof(char)*strlen(Cadena));
            memcpy(Datos->Longitude,Cadena,strlen(Cadena));
            break;
        case 4:
            Datos->EoW = (char*)malloc(sizeof(char)*strlen(Cadena));
            strcpy(Datos->EoW,Cadena);
            break;
        case 5:
            Datos->GPSQuality = (char*)malloc(sizeof(char)*strlen(Cadena));
            memcpy(Datos->GPSQuality,Cadena,strlen(Cadena));
            break;
        case 6:
            Datos->NumoSatile = (char*)malloc(sizeof(char)*strlen(Cadena));
            memcpy(Datos->NumoSatile,Cadena,strlen(Cadena));
            break;
        case 7:
            Datos->horizontalDilution = (char*)malloc(sizeof(char)*strlen(Cadena));
            memcpy(Datos->horizontalDilution,Cadena,strlen(Cadena));
            break;
        case 8:
            Datos->AntenaAltitude = (char*)malloc(sizeof(char)*strlen(Cadena));
            memcpy(Datos->AntenaAltitude,Cadena,strlen(Cadena));
            break;
        case 9:
            Datos->UnitsoAntenna = (char*)malloc(sizeof(char)*strlen(Cadena));
            memcpy(Datos->UnitsoAntenna,Cadena,strlen(Cadena));
            break;
        case 10:
            Datos->Geoidal = (char*)malloc(sizeof(char)*strlen(Cadena));
            memcpy(Datos->Geoidal,Cadena,strlen(Cadena));
            break;
        case 11:
            Datos->UnitsoGeoidal = (char*)malloc(sizeof(char)*strlen(Cadena));
            memcpy(Datos->UnitsoGeoidal,Cadena,strlen(Cadena));
            break;
        case 12:
            Datos->AgeoDifferential = (char*)malloc(sizeof(char)*strlen(Cadena));
            memcpy(Datos->AgeoDifferential,Cadena,strlen(Cadena));
            break;
        case 13:
            Datos->DifferentialID = (char*)malloc(sizeof(char)*strlen(Cadena));
            memcpy(Datos->DifferentialID,Cadena,strlen(Cadena));
            break;
        }
}
void proceso_cliente(int cliente_sockfd){
	gps **Resultado=NULL;
	int Tam=0;
	char leer_mensaje[TAM_BUFFER];

	Resultado = ObtenerDatos(&Tam);
	//Enviando el numero de Resultados
	if( write (cliente_sockfd, &Tam, sizeof(int)) < 0 ){
		perror("Ocurrio un problema en el envio de un mensaje al cliente");
		exit(1);
	}
	printf("Listo\n");
	for(int item=0;item<Tam;item++){
		
		if( write (cliente_sockfd, Resultado[item]->UTCPosition, strlen(Resultado[item]->UTCPosition)) < 0 ){
			perror("Ocurrio un problema en el envio de un mensaje al cliente");
			exit(1);
		}
		if( write (cliente_sockfd, Resultado[item]->Latitud, strlen(Resultado[item]->Latitud)) < 0 ){
			perror("Ocurrio un problema en el envio de un mensaje al cliente");
			exit(1);
		}
		if( write (cliente_sockfd, Resultado[item]->NoS, strlen(Resultado[item]->NoS)) < 0 ){
			perror("Ocurrio un problema en el envio de un mensaje al cliente");
			exit(1);
		}
		if( write (cliente_sockfd, Resultado[item]->Longitude, strlen(Resultado[item]->Longitude)) < 0 ){
			perror("Ocurrio un problema en el envio de un mensaje al cliente");
			exit(1);
		}
		if( write (cliente_sockfd, Resultado[item]->EoW, strlen(Resultado[item]->EoW)) < 0 ){
			perror("Ocurrio un problema en el envio de un mensaje al cliente");
			exit(1);
		}
	}

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