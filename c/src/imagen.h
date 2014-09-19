#ifndef IMAGEN_H
#define IMAGEN_H

#define VALMAX 255
#include <stdlib.h>

/* Codigos de error para entrada/salida */
typedef enum codigo_error { 
  PNM_OK=0,
  PNM_ERROR_LECTURA=1,
  PNM_ARCHIVO_INEXISTENTE=2,
  PNM_ENCABEZADO_INVALIDO=3,
  PNM_DATOS_INVALIDOS=4,
  PNM_ERROR_ESCRITURA=5
} CodigoError;


const char* mensaje_error(CodigoError c);

/* Tipos de imagen representadas */
typedef enum tipo_imagen {
  GRISES=1,
  COLOR=2
} TipoImagen;

/* Pixel es un entero sin signo de al menos 32 bits */
typedef unsigned int Pixel;

/* La estructura de la imagen */
typedef struct imagen {
  TipoImagen tipo;
  int ancho;
  int alto;
  int valor_maximo;
  Pixel* pixels;
} Imagen;

int inicializar_imagen(int ancho, int alto, TipoImagen tipo, Imagen* pimg);
int duplicar_imagen(const Imagen* origen, Imagen* destino);
void destruir_imagen(Imagen* pimg);
CodigoError leer_imagen(const char* ruta, Imagen* pimg);
CodigoError escribir_imagen(const Imagen* pimg, const char* ruta);

#endif
