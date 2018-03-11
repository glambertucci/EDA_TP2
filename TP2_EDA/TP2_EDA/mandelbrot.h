#ifndef MANDELBROT_H
#define MANDELBROT_H

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro_color.h>
#include "allegro5/allegro5.h"
#define LIMIT 255
#define OFFSET 50

#ifndef _COORD_T 
#define _COORD_T
typedef struct { //Estructura para uso de coordenadas.
	double x;
	double y;
}Coord_t;
#endif /* _COORD_T */

/* Función principal de inicialización del display para la interfaz allegro, 
recibe dos estructuras que contienen las coordenadas x e y de los puntos inicial y final
entre los cuales definen el plano a analizar. Muestra en pantalla el resultado.
*/
int MandelAl(Coord_t pi, Coord_t pf);

#endif /* MANDELBROT_H */