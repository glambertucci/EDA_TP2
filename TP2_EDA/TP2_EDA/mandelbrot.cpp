#include "mandelbrot.h"


#define LIMIT 255							//Limite de iteraciones
#define OFFSET 50							//Valor para las iteraciones intermedias
#define ZEROCOLOR "black"					//Color para la profundidad cero
#define INTERMEDIATECOLOR1 "orange"			//Color de bordes
#define	INTERMEDIATECOLOR2 "white"			//Color de bordes
#define	MAXCOLOR "navy"						//Color max iteraciones

void DrawMandelbrot(Coord_t* Pi, Coord_t* Pf);
/*Función encargada de evaluar punto a punto en plano complejo establecido
recibe dos punteros a estructuras donde se contienen los puntos inicial y final
*/

void GetComplex(Coord_t* Pi, Coord_t* Pf, Coord_t* DisplayMax, Coord_t* DisplayPoint, Coord_t* result);
/*Sub funcion de DrawMandelbrot que dados los puntos que forman el plano, un punto en el display,
calcula su equivalente en el plano Recibe los puntos iniciales y finales del plano, la coordenada
máxima del display, la coordenada del display que se desea calcular, y un puntero a donde se desea guardar el resultado. */

void ColorPix(int iteration, Coord_t* DisplayPoint);
/*Funcion que da color al pixel segun la cantidad de iteraciones en ese punto. Recibe la cantidad de interaciones
y la estructura a las coordenadas del punto que se desea evaluar*/

double CalcRatio(Coord_t* Pi, Coord_t* Pf);
//Funcion que reciba dos numeros complejos que definen las esquinas opuestas
//de un plano y calcula el cuadrado del radio en el que esta encerrado el plano.


void MandelAl(infoType* myData, ALLEGRO_DISPLAY* display)
{
	al_set_target_backbuffer(display);

	Coord_t DisplayMax = { 900.0 , 700.0 };
	Coord_t Pi = { myData->x0 , myData->y0 };
	Coord_t Pf = { myData->xF , myData->yF };

	DrawMandelbrot(&Pi, &Pf);	//dibuja el fractal
	al_flip_display();			//lo muestra en pantalla
	system("PAUSE");			//Pone en pausa el sistema para mantener abierta la ventana del fractal

	al_destroy_display(display); //cierra el display y libera la memoria del mismo.

}

void DrawMandelbrot(Coord_t* Pi, Coord_t* Pf)
{
	ALLEGRO_BITMAP* bitmap = al_get_target_bitmap();
	Coord_t Num = { 0.0,0.0 };		 //Numero complejo asociado a un determinado pixel
	Coord_t DisplayPoint = { 0.0,0.0 };	 //representa las coordenadas de los pixels en display
	Coord_t result = { 0.0,0.0 };
	Coord_t DisplayMax = { (double)al_get_bitmap_width(bitmap), (double)al_get_bitmap_height(bitmap) };
	double PrevResX = 0.0;
	int row, col;
	int iteration = 0;
	double ratio = CalcRatio(Pi, Pf);
	char* color = NULL;
	al_lock_bitmap(bitmap, al_get_bitmap_format(bitmap), ALLEGRO_LOCK_WRITEONLY);

	for (row = 0; row < (DisplayMax.y); row++)				//loops para analizar punto a punto
	{
		for (col = 0; col < (DisplayMax.x); col++)
		{
			DisplayPoint.y = row;
			DisplayPoint.x = col;

			GetComplex(Pi, Pf, &DisplayMax, &DisplayPoint, &Num);		//Busca la equivalencia de puntos
			result.x = 0.0;
			result.y = 0.0;

			iteration = 0;
			while ((((result.x)*(result.x) + (result.y)*(result.y)) < ratio) && (iteration < LIMIT))
			{
				PrevResX = result.x;
				result.x = (result.x)*(result.x) - (result.y)*(result.y) + (Num.x);
				result.y = 2.0*(PrevResX)*(result.y) + (Num.y);
				iteration++;
			}
			ColorPix(iteration, &DisplayPoint);
		}
	}
	al_unlock_bitmap(bitmap);
}



void GetComplex(Coord_t* Pi, Coord_t* Pf, Coord_t* DisplayMax, Coord_t* DisplayPoint, Coord_t* result)
{
	(result->x) = (DisplayPoint->x)*(((Pf->x) - (Pi->x)) / (DisplayMax->x)) + (Pi->x);
	(result->y) = (DisplayPoint->y)*(((Pi->y) - (Pf->y)) / (DisplayMax->y)) + (Pf->y);

}


double CalcRatio(Coord_t* Pi, Coord_t* Pf)
{
	if ((((Pf->x) - (Pi->x))*((Pf->x) - (Pi->x)))< (((Pf->y) - (Pi->y))*((Pf->y) - (Pi->y))))
	{
		return (((Pf->x) - (Pi->x))*((Pf->x) - (Pi->x)));		//En caso que el eje x del plano sea el mas grande, devuelve este como radio
	}
	else
	{
		return (((Pf->y) - (Pi->y))*((Pf->y) - (Pi->y)));		//En el caso contario
	}

}

void ColorPix(int iteration, Coord_t* DisplayPoint)
{
	if (iteration == LIMIT)
	{
		al_put_pixel((DisplayPoint->x), (DisplayPoint->y), al_color_name(ZEROCOLOR));
	}
	else if ((iteration < LIMIT) && (iteration>(LIMIT - 4 * OFFSET)))
	{
		al_put_pixel((DisplayPoint->x), (DisplayPoint->y), al_color_name(INTERMEDIATECOLOR1));
	}
	else if ((iteration <= (LIMIT - 4 * OFFSET)) && (iteration>(LIMIT - 4.5 * OFFSET)))
	{
		al_put_pixel((DisplayPoint->x), (DisplayPoint->y), al_color_name(INTERMEDIATECOLOR2));
	}
	else
	{
		al_put_pixel((DisplayPoint->x), (DisplayPoint->y), al_color_name(MAXCOLOR));
	}
}