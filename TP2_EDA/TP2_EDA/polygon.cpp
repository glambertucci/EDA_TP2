
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <math.h>
#include "input_manage_verification.h"//data types
#include "polygon.h"

#define DISPLAY_X 1080
#define DISPLAY_Y 800
#define LENGTH 200
#define POLIGONO 5


/*
int main(int argc, char ** argv)
{
	ALLEGRO_DISPLAY *display = NULL;
	punto_t puntoinicial[8];
	double xCenter = DISPLAY_X / 2, yCenter = DISPLAY_Y / 2;
	int lStart = LENGTH;
	int contador;
	double lConst = 0.4, lEnd = 2;
	int polygonType = POLIGONO;



	if (al_init())
	{
		if (al_init_primitives_addon())
		{
			display = al_create_display(DISPLAY_X, DISPLAY_Y);
			if (display)
			{
				//Le ponemos el nombre a la ventana.
				al_set_window_title(display, "Poligono regular");
				al_clear_to_color(al_map_rgb(0, 0, 0));

				recursive_polygon(xCenter, yCenter, lStart, lConst, lEnd, polygonType);

				//Esperamos 10.
				al_rest(10.0);

				//Destruimos el display para no generar memory leaks.
				al_destroy_display(display);

			}
			else
				fprintf(stderr, "failed to create display1!\n");

			//Cerramos apropiadamente el addon de primitives.
			al_shutdown_primitives_addon();
		}
	}
	//The end.
	return 0;
}*/


void recursive_polygon(double xi, double yi, double lStart, double lConst, double lEnd, unsigned int gradoPoligono, unsigned int angle);

//**************                        DIBUJAR_POLIGONO           ***********************/
/*
*Función encargada de dibujar el fractal del polígono. Se dibuja el políono central  luego ir dibujando la versión
*acotada en los vértices, asi hasta completar los mismos. Esto último se hace desde la función recursiva, la principal 
*sólo imprime el polígono central.
*Se puede tomar polígonos regulares desde 3 lados hasta 15, más allá de ese valor ya no se aprecia realmente
*ninguna diferencia por lo que se decido a acotarlo.
*
*INPUT
*La función recibe un puntero a una estructura donde estan los datos ya verificados para la construccipon del fractal.
*
*OUTPUT
*void
*/

void polygon(infoType * myData)
{
	double xi= (myData->xo);    //Guardo la información recibida mediante la estrcutura
	double yi= (myData->yo); , 
	double lStart= (myData->lStart);
	double lConst= (myData->lConst);
	double lEnd= (myData->lEnd);
	unsigned int gradoPoligono = (myData->N);
	
	
	if (lStart <= lEnd) //Caso base
		return;

	int contador;  //Contador para moverme dentro del arreglo de puntos
	double apotema = (lStart * gradoPoligono) / (16 * (sqrt(2) - 1)); //se calcula la distancia del centro de la figura al centro de un lado
	double angulo = (180.0 * (gradoPoligono - 2.0)) / gradoPoligono;//se calcula el ángulo interno caracteríscio del polígono
	
	//Creo con memoria dinámica un arreglo para ir guardando los puntos de dibujo a medida que los voy necesitando
	punto_t *puntos_de_dibujo =(punto_t *) malloc((gradoPoligono + 2) * sizeof(punto_t)); 
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

	for (contador = 0; contador < gradoPoligono; contador++)//Recursión
		recursive_polygon(puntos_de_dibujo[contador].xcord, puntos_de_dibujo[contador].ycord, lStart * lConst, lConst, lEnd, gradoPoligono,angulo); 

	free(puntos_de_dibujo);
}

void recursive_polygon (double xi, double yi, double lStart, double lConst, double lEnd, unsigned int gradoPoligono, unsigned int angle)
{

	if (lStart <= lEnd) //Caso base
		return;

	int contador;  //Contador para moverme dentro del arreglo de puntos
	double apotema = (lStart * gradoPoligono) / (16 * (sqrt(2) - 1)); //se calcula la distancia del centro de la figura al centro de un lado

																	//Creo con memoria dinámica un arreglo para ir guardando los puntos de dibujo a medida que los voy necesitando
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

	for (contador = 0; contador < gradoPoligono; contador++)//Recursión
		recursive_polygon(puntos_de_dibujo[contador].xcord, puntos_de_dibujo[contador].ycord, lStart * lConst, lConst, lEnd, gradoPoligono, angulo);

	free(puntos_de_dibujo);

}

/* Main de prueba aislada del triangulo
int main(void)
{

srand(time(NULL));//seedeamos el main para poder llamar a rand()

al_init();
al_init_primitives_addon();
al_init_image_addon();

ALLEGRO_DISPLAY *diplay=al_create_display(1000,600);
triangle_fractal(0.0,400.0,50,60,300,20.0);

}
*/

/* Main pruebas aislado polygono


int main(int argc, char ** argv)
{
ALLEGRO_DISPLAY *display = NULL;
point_t puntoinicial[8];
double xCenter = DISPLAY_X/2,yCenter = DISPLAY_Y/2;
int lStart = LENGTH;
int contador;
double lConst = 0.6, lEnd = 20;
int polygonType = POLIGONO;



if(al_init())
{
if(al_init_primitives_addon())
{
display = al_create_display(DISPLAY_X, DISPLAY_Y);
if(display)
{
//Le ponemos el nombre a la ventana.
al_set_window_title(display,"Poligono regular");
al_clear_to_color(al_map_rgb (0,0,0));

draw_polygon (xCenter, yCenter, lStart, polygonType, lConst, lEnd);

//Esperamos 10.
al_rest(10.0);

//Destruimos el display para no generar memory leaks.
al_destroy_display(display);

}
else
fprintf(stderr, "failed to create display1!\n");

//Cerramos apropiadamente el addon de primitives.
al_shutdown_primitives_addon();
}
}
//The end.
return 0;
}


*/

