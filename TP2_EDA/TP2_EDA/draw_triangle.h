#pragma once
typedef struct
{
	double xcoord, ycoord;
}point;
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>

#define REST_TIME	0.01//tiempo de descanso entre cada escritura, lo uso para que se aprecie la construccion del fractal
#define THICC  2 //tamaño de la linea
void triangle_fractal(double xstart, double ystart, double leftAngle, double rightAngle, double lStart, double lEnd);
//Dibuja el primer triangulo y comienza la recursividad, consigue los 3 puntos del triangulo a partir de las condiciones iniciales.
//recibe las coordenadas donde comienza el fractal (xstart, ystart) y los angulos iniciales (left angle y right angle), la longitud del cateto inicial, y la final la cual indica el final de la recursion
// el left angle tiene que tener un rango de -90 a 0, y el right angle de 90 a 0; claramente no pudiendo ser ambos 90 a la ves
void triangle_fractal_recursion(point point1, point point2, point point3, double lEnd);
//Es llamada opr triangle fractal, es la funcion recursiva







