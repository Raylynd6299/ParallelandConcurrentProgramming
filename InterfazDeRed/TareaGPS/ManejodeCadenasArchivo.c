#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Estructura GPS
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

gps* ProcesarCadena(char *Cadena);
char* LeerArchivo(FILE *Archivo,long* Tam);

void main(){
    FILE *Archivo;
	char *Texto;
	long TamTexto;
    int Ret;
    gps *Res = NULL;
    Texto = (char*)malloc(sizeof(char)*100);

	if((Archivo = fopen("nmea.txt","r")) == NULL){
		perror("Error al abrir el Archivo");
		exit(EXIT_FAILURE);
	}
    
    // Texto = LeerArchivo(Archivo,&TamTexto);

    // printf("%s\n",Texto);
    // printf("Hay %ld Caracteres",TamTexto);
    char* pivote=NULL;
    printf("\n");
    while(fgets(Texto,100,Archivo)){
        Res = ProcesarCadena(Texto);
        if (Res != NULL){
            printf("%s\n",Texto);
            printf("llego : UTCPosition->>>>>%s\n",Res->UTCPosition);
            printf("llego : Latitud->>>>>%s\n",Res->Latitud);
            printf("llego : NoS->>>>>%s\n",Res->NoS);
            printf("llego : Longitude->>>>>%s\n",Res->Longitude);
            printf("llego : EoW->>>>>%s\n",Res->EoW);
            printf("llego : GPSQuality->>>>>%s\n",Res->GPSQuality);
            printf("llego : NumoSatile->>>>>%s\n",Res->NumoSatile);
            printf("llego : horizontalDilution->>>>>%s\n",Res->horizontalDilution);
            printf("llego : AntenaAltitude->>>>>%s\n",Res->AntenaAltitude);
            printf("llego : UnitsoAntenna->>>>>%s\n",Res->UnitsoAntenna);
            printf("llego : Geoidal->>>>>%s\n",Res->Geoidal);
            printf("llego : UnitsoGeoidal->>>>>%s\n",Res->UnitsoGeoidal);
            printf("llego : AgeoDifferential->>>>>%s\n",Res->AgeoDifferential);
            printf("llego : DifferentialID->>>>>%s\n",Res->DifferentialID);

        }
    }
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
                printf("%s---%ld\n",aux2,strlen(aux2));
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

char* LeerArchivo(FILE *Archivo,long* Tam){
    char *Texto;
    char letra = 'a';
	long indice = 0;
	long TamTexto = 40;

    Texto = (char *)malloc(sizeof(char)*TamTexto);

    //Obtenemos toda la informacion 
	while ( (letra = (char)fgetc(Archivo)) != EOF ){
		if(indice < TamTexto){
            Texto[indice] = letra;
            indice++;
		}else{
			Texto = (char*)realloc((void*)Texto, sizeof(char)*(TamTexto+20));
			TamTexto += 20;
            Texto[indice] = letra;
            indice++;
		}
	}
    Texto[indice] = '\0';

    *Tam = indice;

    return Texto;
}