#pragma once
#include "draw_triangle.h"
double abso(double num);
//Calcula el valor absoluto, recibe y devuelve double

double square(double num);
//Caclula el cuadrado de un numero, recibe y devuelve double

double toRadian(double num);
//Transforma el angulo recibido a radianes y lo devuelve

ALLEGRO_COLOR alRandColor(void);
//Devuelve un color random de allegro

double pithagoras(point punto1, point punto2);
//aplica pitagoras.

point massCenterTriangle(point * p1, point * p2, point * p3);
//consigue el centro de masas de un triangulo, recibiendo las 3 aristas.