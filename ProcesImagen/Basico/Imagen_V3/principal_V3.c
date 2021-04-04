#include <stdio.h>
#include <stdlib.h>

#include "imagen.h"


void RGBToGray(unsigned char *imagen, unsigned char *imagenGray, uint32_t width,uint32_t height );
void GraytoRGB(unsigned char *imagen, unsigned char *imagenGray, uint32_t width,uint32_t height );
unsigned char * reservarMemoria(uint32_t width,uint32_t height);
void BrilloImagen(unsigned char *imagenGray,uint32_t width,uint32_t height);

int main() {

    bmpInfoHeader info;
    unsigned char *imagenRGB,*imagenGray;

    imagenRGB = abrirBMP( "prueba.bmp" , &info );

    imagenGray = reservarMemoria(info.width,info.height);
    RGBToGray(imagenRGB,imagenGray,info.width,info.height);
    BrilloImagen( imagenGray, info.width,info.height);
    GraytoRGB(imagenRGB, imagenGray,info.width,info.height);
    
    guardarBMP("resultado_Luminosidad_2.bmp", &info, imagenRGB);    

    free( imagenRGB );
    free( imagenGray );
    return 0;

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
    register int indiceGray = 0,indiceRGB=0;
    for( indiceGray = 0,indiceRGB=0; indiceGray < (width*height); indiceGray++,indiceRGB+=3){
        // Por promedio nivelGray = (*(imagenRGB+ indiceRGB +0) + *(imagenRGB+ indiceRGB+1) + *(imagenRGB + indiceRGB+2)) /3;
        // Por ponderacion 
        nivelGray = (30* (*(imagenRGB+ indiceRGB +0)) + 59* (*(imagenRGB+ indiceRGB+1)) + 11* (*(imagenRGB + indiceRGB+2)) ) /100;
        imagenGray[indiceGray] = nivelGray;
    }

}
