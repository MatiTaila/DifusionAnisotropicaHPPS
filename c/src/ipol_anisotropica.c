#include <stdio.h>
#include "imagen.h"

#define SIGMA 0.05
#define LAMBDA 0.08
#define NITER 75

float difusionIteration(int i, int j,int width, int height, int current,float* subIn){
	double dW, dE, dN, dS, gDw, gDe, gDn, gDs;

	int west  = ((j-1)<0)?i*width:i*width+j-1;
	int east  = ((j+1)>(width-1))?i*width+width-1:i*width+j+1;
	int north = ((i-1)<0)?j:(i-1)*width+j;
	int south = ((i+1)>(height-1))?(height-1)*width+j:(i+1)*width+j;

	dW = (double)(subIn[west]-subIn[current]);
	dE = (double)(subIn[east]-subIn[current]);
	dN = (double)(subIn[north]-subIn[current]);
	dS = (double)(subIn[south]-subIn[current]);

	gDn = 1/(1+(dN/SIGMA)*(dN/SIGMA));
	gDs = 1/(1+(dS/SIGMA)*(dS/SIGMA));
	gDe = 1/(1+(dE/SIGMA)*(dE/SIGMA));
	gDw = 1/(1+(dW/SIGMA)*(dW/SIGMA));

	return subIn[current] + ( LAMBDA * (gDn*(double)dN + gDs*(double)dS + 
				gDe*(double)dE + gDw*(double)dW) );
}

void difusionAnisotropicaGrises(Imagen* imIn, Imagen* imOut){
	int iter, i, j, current, width, height;
	float* aux;
	width  = imIn->ancho;
	height = imIn->alto;

	float* subIn  = malloc(width*height*sizeof(float));
	float* subOut = malloc(width*height*sizeof(float));

	for(i=0;i<width*height;i++)
		subIn[i] = (double)imIn->pixels[i]/VALMAX;

	for(iter=0;iter<NITER;iter++)
	{
		for(i=0;i<height;i++)
			for(j=0;j<width;j++){
				current = i*width+j;
				subOut[current] = difusionIteration(i, j, width, height, current, subIn);
			}
		aux = subIn;
		subIn = subOut;
		subOut = aux;
		/*
		for(i=0;i<width*height;i++)
			imIn->pixels[i] = imOut->pixels[i];
		*/
	}
	for(i=0;i<width*height;i++)
		imOut->pixels[i] = (Pixel)VALMAX*subIn[i];

	free(subIn);
	free(subOut);
}

void difusionAnisotropica(Imagen* imIn, Imagen* imOut){
	if(imIn->tipo==GRISES)
		difusionAnisotropicaGrises(imIn,imOut);
	else{
		Imagen aux, R, G, B;
		inicializar_imagen(imIn->ancho, imIn->alto, GRISES, &aux);
		inicializar_imagen(imIn->ancho, imIn->alto, GRISES, &R);
		inicializar_imagen(imIn->ancho, imIn->alto, GRISES, &G);
		inicializar_imagen(imIn->ancho, imIn->alto, GRISES, &B);
		int i;
		/* CANAL R */
		for(i=0;i<imIn->ancho*imIn->alto;i++)
			aux.pixels[i] = (imIn->pixels[i] >> 16) & 0xff;
		difusionAnisotropicaGrises(&aux,&R);
		/* CANAL G */
		for(i=0;i<imIn->ancho*imIn->alto;i++)
			aux.pixels[i] = (imIn->pixels[i] >> 8) & 0xff;
		difusionAnisotropicaGrises(&aux,&G);
		/* CANAL R */
		for(i=0;i<imIn->ancho*imIn->alto;i++)
			aux.pixels[i] = imIn->pixels[i] & 0xff;
		difusionAnisotropicaGrises(&aux,&B);

		for(i=0;i<imIn->ancho*imIn->alto;i++)
			imOut->pixels[i] = (R.pixels[i] << 16) + (G.pixels[i] << 8) + B.pixels[i]  ;

		destruir_imagen(&aux);
		destruir_imagen(&R);
		destruir_imagen(&G);
		destruir_imagen(&B);
	}
}

int main(int argc, char* argv[]){

	if (argc<3){
		printf("Llamada incorrecta. Se debe llamar de la siguiente forma:\n./difusionAnisotropica rutaArchivoEntrada rutaArchivoSalida\n");
		return 1;
	}

	CodigoError ce;
	Imagen imIn, imOut;
	
	if ( (ce = leer_imagen(argv[1], &imIn)) ) {
	 	printf("Error al leer imagen: %d\n", ce);
	 	return 1;
	}
	if ( duplicar_imagen(&imIn, &imOut) ){
		printf("Error al duplicar imagen\n");
		return 1;
	}

	difusionAnisotropica(&imIn, &imOut);
	
	ce = escribir_imagen(&imOut, argv[2]);

	destruir_imagen(&imIn);
	destruir_imagen(&imOut);
	
	return 0;
}