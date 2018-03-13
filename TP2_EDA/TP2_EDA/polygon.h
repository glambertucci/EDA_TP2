/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   draw_fractals.h
* Author: r2d2
*
* Created on March 18, 2016, 10:41 PM
*/

#ifndef DRAW_FRACTALS_H
#define DRAW_FRACTALS_H
#include <corecrt_math_defines.h>


#define PAUSA	0.001
#define TAM_LINEA  0.0

#define RADIANES(a) ( (a)/( 180.0/(double)M_PI) )
#define ABS(x) ((x)<0?(-(x)):(x))
#define SQUARE(x) ((x)*(x))

void polygon(infoType *myData);
#endif /* DRAW_FRACTALS_H */

