//*********************     BILBIOTECAS A UTILIZAR  ************************//
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <math.h>
#include "input_manage_verification.h"//data types
#include "polygon.h"


//*********************           MACROS          ************************//
#define DISPLAY_X 1080
#define DISPLAY_Y 800
#define LENGTH 200
#define POLIGONO 5

//*********************     DECLARACI�N DE FUNCIONES LOCALES  ************************//

//Funci�n encargada de la recursividad ddel pol�gono
static void recursive_polygon(double xi, double yi, double lStart, double lConst, double lEnd, unsigned int gradoPoligono, unsigned int angle);


//*********************     DEFINICI�N DE FUNCIONES GLOBALES  ************************//

//**************                        POLYGON            ***********************/
/*
*Funci�n encargada de dibujar el fractal del pol�gono. Se dibuja el pol�ono central  para luego ir dibujando la versi�n
*acotada en los v�rtices, asi hasta completar los mismos. 
*Se puede tomar pol�gonos regulares desde 3 lados hasta 15, m�s all� de ese valor ya no se aprecia realmente
*ninguna diferencia por lo que se decido a acotarlo.
*
*INPUT
*La funci�n recibe un puntero a una estructura donde estan los datos ya verificados para la construccipon del fractal.
*
*OUTPUT
*void
*/

void polygon(infoType * myData)
{
	double xi = (myData->x0);    //Guardo la informaci�n recibida mediante la estrcutura
	double yi = (myData->y0);
	double lStart = (myData->lStart);
	double lConst = (myData->lConstant);
	double lEnd = (myData->lEnd);
	unsigned int gradoPoligono = (myData->N);

	double angulo = (180.0 * (gradoPoligono - 2.0)) / gradoPoligono;//se calcula el �ngulo interno caracter�scio del pol�gono

	recursive_polygon(xi, yi, lStart, lConst, lEnd, gradoPoligono,angulo);
}


//*********************     DEFINICI�N DE FUNCIONES LOCALES  ************************//

static void recursive_polygon(double xi, double yi, double lStart, double lConst, double lEnd, unsigned int gradoPoligono, unsigned int angulo)
{
	if (lStart <= lEnd) //Caso base
		return;

	unsigned int contador;  //Contador para moverme dentro del arreglo de puntos
	double apotema = (lStart * gradoPoligono) / (16 * (sqrt(2) - 1)); //se calcula la distancia del centro de la figura al centro de un lado

	//Creo con memoria din�mica un arreglo para ir guardando los puntos de dibujo a medida que los voy necesitando
	punto_t *puntos_de_dibujo = (punto_t *)malloc((gradoPoligono + 2) * sizeof(punto_t));
	if (!puntos_de_dibujo)
	{
		printf("No se pudo alocar memoria \n");
		return;
	}
	puntos_de_dibujo[0].xcord = apotema + xi;
	puntos_de_dibujo[0].ycord = yi - lStart / 2;
	puntos_de_dibujo[1].xcord = puntos_de_dibujo[0].xcord;
	puntos_de_dibujo[1].ycord = yi + lStart / 2;


	for (contador = 0; contador < gradoPoligono; contador++)
	{	//Se recalculan el nuevo par de puntos
		puntos_de_dibujo[contador + 1].xcord = puntos_de_dibujo[contador].xcord - lStart * sin(RADIANES((180 - angulo)*(contador + 1)));
		puntos_de_dibujo[contador + 1].ycord = puntos_de_dibujo[contador].ycord - lStart * cos(RADIANES((180 - angulo)*(contador + 1)));

		puntos_de_dibujo[contador + 2].xcord = puntos_de_dibujo[contador + 1].xcord + lStart * sin(RADIANES((180 - angulo)*(contador + 1)));
		puntos_de_dibujo[contador + 2].ycord = puntos_de_dibujo[contador + 1].ycord + lStart * cos(RADIANES((180 - angulo)*(contador + 1)));

		al_draw_line(puntos_de_dibujo[contador].xcord, puntos_de_dibujo[contador].ycord, puntos_de_dibujo[contador + 1].xcord, puntos_de_dibujo[contador + 1].ycord, al_map_rgb(rand() % 250, rand() % 250, rand() % 250), TAM_LINEA);

	}
	al_flip_display();
	al_rest(PAUSA);

	for (contador = 0; contador < gradoPoligono; contador++)//Recursi�n
		recursive_polygon(puntos_de_dibujo[contador].xcord, puntos_de_dibujo[contador].ycord, lStart * lConst, lConst, lEnd, gradoPoligono,angulo);

	free(puntos_de_dibujo);
}
