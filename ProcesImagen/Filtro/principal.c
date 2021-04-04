#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imagen.h"
#define DIMASK 5


void RGBToGray(unsigned char *imagen, unsigned char *imagenGray, uint32_t width,uint32_t height );
void GraytoRGB(unsigned char *imagen, unsigned char *imagenGray, uint32_t width,uint32_t height );
unsigned char * reservarMemoria(uint32_t width,uint32_t height);
void BrilloImagen(unsigned char *imagenGray,uint32_t width,uint32_t height);
void FiltroPasaBajas(unsigned char *imagenGray, unsigned char *imagenFiltro, uint32_t width,uint32_t height );
void FiltroPasaBajas_Gaussiano(unsigned char *imagenGray, unsigned char *imagenFiltro, uint32_t width,uint32_t height );


int main() {

    bmpInfoHeader info;
    unsigned char *imagenRGB,*imagenGray,*imagenFiltro;

    imagenRGB = abrirBMP( "prueba.bmp" , &info );

    imagenGray = reservarMemoria(info.width,info.height);
    imagenFiltro = reservarMemoria(info.width,info.height);
    memset(imagenFiltro,255,info.height*info.width);

    RGBToGray(imagenRGB,imagenGray,info.width,info.height);
    //BrilloImagen( imagenGray, info.width,info.height);
    //FiltroPasaBajas(imagenGray,imagenFiltro,info.width,info.height);
    FiltroPasaBajas_Gaussiano(imagenGray,imagenFiltro,info.width,info.height);
    GraytoRGB(imagenRGB, imagenFiltro,info.width,info.height);
    
    guardarBMP("resultado_filtro.bmp", &info, imagenRGB);    

    free( imagenRGB );
    free( imagenGray );
    free( imagenFiltro );
    return 0;

}

void FiltroPasaBajas(unsigned char *imagenGray, unsigned char *imagenFiltro, uint32_t width,uint32_t height ){
    //Quita las zonas de alta frecuencia(Bordes)
    int mascara[DIMASK*DIMASK] = {
        1,1,1,
        1,1,1,
        1,1,1
    },indicei,indicem,conv;
    for(register int y = 0; y <= height-DIMASK; y++){
        for(register int x = 0;x <= width-DIMASK; x++){
            indicem=0;
            conv=0;
            for(int ym = 0;ym < DIMASK; ym++){
                for(int xm = 0;xm <DIMASK; xm++){
                    indicei = (y+ym) * width +(x+ xm);
                    conv += imagenGray[indicei] + mascara[indicem++];
                }
            }
            conv = conv / 9;
            indicei = (y+1)*width +(x+1);
            imagenFiltro[indicei] = conv;
        }
    }
}
void FiltroPasaBajas_Gaussiano(unsigned char *imagenGray, unsigned char *imagenFiltro, uint32_t width,uint32_t height ){
    //Quita las zonas de alta frecuencia(Bordes)
    int KernerGaussiano[DIMASK*DIMASK] = {
        1, 4, 7, 4,1,
        4,20,33,20,4,
        7,33,54,33,7,
        4,20,33,20,4,
        1, 4, 7, 4,1,
    },indicei,indicem,conv;
    for(register int y = 0; y <= height-DIMASK; y++){
        for(register int x = 0;x <= width-DIMASK; x++){
            indicem=0;
            conv=0;
            for(int ym = 0;ym < DIMASK; ym++){
                for(int xm = 0;xm <DIMASK; xm++){
                    indicei = (y+ym) * width +(x+ xm);
                    conv += imagenGray[indicei] + KernerGaussiano[indicem++];
                }
            }
            conv = conv /330;
            indicei = (y+1)*width +(x+1);
            imagenFiltro[indicei] = conv;
        }
    }
}


void BrilloImagen(unsigned char *imagenGray,uint32_t width,uint32_t height){
    for(register int indiceGray = 0; indiceGray < (width*height); indiceGray++){
        if(imagenGray[indiceGray] + 10 > 255){
            imagenGray[indiceGray] = 255;
        }else{
            imagenGray[indiceGray] += 10;
        }
        
             
    }   
}

unsigned char * reservarMemoria(uint32_t width,uint32_t height){
    unsigned char *imagen;
    imagen = (unsigned char*) malloc( width * height * sizeof(unsigned char));
    if (imagen == NULL){
        perror("Error al asignr memoria");
        exit(EXIT_FAILURE);
    }
    return imagen;    
}        
void GraytoRGB(unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width,uint32_t height ){
         for(register int indiceGray = 0,indiceRGB=0; indiceGray < (width*height); indiceGray++,indiceRGB+=3){
             imagenRGB[indiceRGB] = imagenGray[indiceGray];
             imagenRGB[indiceRGB+1] = imagenGray[indiceGray];
             imagenRGB[indiceRGB+2] = imagenGray[indiceGray];
         }   
}


void RGBToGray(unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width,uint32_t height ){
    unsigned char nivelGray;
     
        for(register int indiceGray = 0,indiceRGB=0; indiceGray < (width*height); indiceGray++,indiceRGB+=3){
            // Por promedio nivelGray = (*(imagenRGB+ indiceRGB +0) + *(imagenRGB+ indiceRGB+1) + *(imagenRGB + indiceRGB+2)) /3;
            // Por ponderacion 
            nivelGray = (30* (*(imagenRGB+ indiceRGB +0)) + 59* (*(imagenRGB+ indiceRGB+1)) + 11* (*(imagenRGB + indiceRGB+2)) ) /100;
            imagenGray[indiceGray] = nivelGray;
        }

}
