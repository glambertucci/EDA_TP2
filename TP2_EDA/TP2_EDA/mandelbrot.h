#ifndef MANDELBROT_H
#define MANDELBROT_H

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro_color.h>
#include "allegro5/allegro5.h"

#ifndef _COORD_T 
#define _COORD_T
typedef struct { //Estructura para uso de coordenadas.
	double x;
	double y;
}Coord_t;
#endif /* _COORD_T */

/* Función principal para la creacón del fractal. recibe un puntero a la estructura del tipo infoType
y el puntero a display. Muestra en pantalla el resultado.
*/
void MandelAl(infoType* myData, ALLEGRO_DISPLAY* display);

#endif /* MANDELBROT_H */