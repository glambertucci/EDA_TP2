
#ifndef POLYGON_H
#define POLYGON_H

//*********************     BILBIOTECAS A INCLUIR ************************//
#include <corecrt_math_defines.h>
#include "general.h"

//*********************     MACROS  ************************//
#define PAUSA	0.001
#define TAM_LINEA  0.0
#define RADIANES(a) ( (a)/( 180.0/(double)M_PI) )

//*********************     ESTRUCTURAS  ************************//
typedef struct
{
	double xcord, ycord;
}punto_t;

//*********************     DECALRACIÓN DE FUNCIONES GLOBALES  ************************//
void polygon(infoType *myData);


#endif /* POLYGON_H */

