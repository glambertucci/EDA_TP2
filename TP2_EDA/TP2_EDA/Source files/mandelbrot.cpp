#include "mandelbrot.h"

void DrawMandelbrot(Coord_t* P0, Coord_t* Pf);
/*Función encargada de evaluar punto a punto en plano complejo establecido
recibe dos punteros a estructuras donde se contienen los puntos inicial y final
*/

void GetComplexNum(Coord_t* P0, Coord_t* Pf, Coord_t* DisplayMax, Coord_t* DisplayPoint, Coord_t* result);
/*Sub funcion de DrawMandelbrot que dados los puntos que forman el plano, un punto en el display,
calcula su equivalente en el plano Recibe los puntos iniciales y finales del plano, la coordenada
máxima del display, la coordenada del display que se desea calcular, y un puntero a donde se desea guardar el resultado. */

void AnalyzeColor(int iteration, Coord_t* DisplayDot);
/*Funcion que da color al pixel segun la cantidad de iteraciones en ese punto. Recibe la cantidad de interaciones
y la estructura a las coordenadas del punto que se desea evaluar*/

double CalculatePlaneRatio(Coord_t* P0, Coord_t* Pf);
//Funcion que reciba dos numeros complejos que definen las esquinas opuestas
//de un plano y calcula el cuadrado del radio en el que esta encerrado el plano.


int MandelAl(infoType * myData) {

	Coord_t pi;   //Guardo la información recibida mediante la estrcutura
	Coord_t pf;
	pi.x = fractalInfo.x0;
	pi.y = fractalInfo.y0;
	pf.x = fractalInfo.xF;
	pf.y = fractalInfo.yF;

	ALLEGRO_DISPLAY *  display = NULL;

	display = al_create_display(900.0 , 700.0); // crea el display
	if (!display)
	{
		fprintf(stderr, "Error: No se logro crear el display.\n");
		return -1;
	}
	al_set_target_backbuffer(display);

	Coord_t DisplayMax = { 900.0 , 700.0};
	Coord_t P0 = { pi.x , pi.y };
	Coord_t Pf = { pf.x , pf.y };

	DrawMandelbrot(&P0, &Pf);	//dibuja el fractal
	al_flip_display();			//lo muestra en pantalla
	system("PAUSE");			//Pone en pausa el sistema para mantener abierta la ventana del fractal

	al_destroy_display(display); //cierra el display y libera la memoria del mismo.

	return (EXIT_SUCCESS);
}

void DrawMandelbrot(Coord_t* P0, Coord_t* Pf)
{
	ALLEGRO_BITMAP* bitmap = al_get_target_bitmap();
	Coord_t Number = { 0.0,0.0 };		 //Numero complejo asociado a un determinado pixel
	Coord_t DisplayDot = { 0.0,0.0 };	 //representa las coordenadas de los pixels en display
	Coord_t result = { 0.0,0.0 };
	Coord_t DisplayMax = { (double)al_get_bitmap_width(bitmap), (double)al_get_bitmap_height(bitmap) };
	double PreviousResultX = 0.0;
	int row;
	int col;
	int iteration = 0;
	double ratio = CalculatePlaneRatio(P0, Pf);
	char* color = NULL;
	al_lock_bitmap(bitmap, al_get_bitmap_format(bitmap), ALLEGRO_LOCK_WRITEONLY);

	for (row = 0; row < (DisplayMax.y); row++)				//loops para analizar punto a punto
	{
		for (col = 0; col < (DisplayMax.x); col++)
		{
			DisplayDot.y = row;
			DisplayDot.x = col;

			GetComplexNum(P0, Pf, &DisplayMax, &DisplayDot, &Number);		//Busca la equivalencia de puntos
			result.x = 0.0;
			result.y = 0.0;

			iteration = 0;
			while ((((result.x)*(result.x) + (result.y)*(result.y)) < ratio) && (iteration < LIMIT))
			{
				PreviousResultX = result.x;
				result.x = (result.x)*(result.x) - (result.y)*(result.y) + (Number.x);
				result.y = 2.0*(PreviousResultX)*(result.y) + (Number.y);
				iteration++;
			}
			AnalyzeColor(iteration, &DisplayDot);
		}
	}
	al_unlock_bitmap(bitmap);
}



void GetComplexNum(Coord_t* P0, Coord_t* Pf, Coord_t* DisplayMax, Coord_t* DisplayPoint, Coord_t* result)
{
	(result->x) = (DisplayPoint->x)*(((Pf->x) - (P0->x)) / (DisplayMax->x)) + (P0->x);
	(result->y) = (DisplayPoint->y)*(((P0->y) - (Pf->y)) / (DisplayMax->y)) + (Pf->y);

}



double CalculatePlaneRatio(Coord_t* P0, Coord_t* Pf)
{
	if ((((Pf->x) - (P0->x))*((Pf->x) - (P0->x)))< (((Pf->y) - (P0->y))*((Pf->y) - (P0->y))))
	{
		return (((Pf->x) - (P0->x))*((Pf->x) - (P0->x)));		//En caso que el eje x del plano sea el mas grande, devuelve este como radio
	}
	else
	{
		return (((Pf->y) - (P0->y))*((Pf->y) - (P0->y)));		//En el caso contario
	}

}

void AnalyzeColor(int iteration, Coord_t* DisplayDot)
{
	if (iteration == LIMIT)
			{
				al_put_pixel((DisplayDot->x), (DisplayDot->y), al_color_name("black"));
			}
			else if ((iteration < LIMIT) && (iteration>(LIMIT - OFFSET)))
			{
				al_put_pixel((DisplayDot->x), (DisplayDot->y), al_color_name("orange"));
			}
			else if ((iteration <= (LIMIT - OFFSET)) && (iteration>(LIMIT - 2 * OFFSET)))
			{
				al_put_pixel((DisplayDot->x), (DisplayDot->y), al_color_name("orange"));
			}
			else if ((iteration <= (LIMIT - 2 * OFFSET)) && (iteration>(LIMIT - 3 * OFFSET)))
			{
				al_put_pixel((DisplayDot->x), (DisplayDot->y), al_color_name("orange"));
			}
			else if ((iteration <= (LIMIT - 3 * OFFSET)) && (iteration>(LIMIT - 4 * OFFSET)))
			{
				al_put_pixel((DisplayDot->x), (DisplayDot->y), al_color_name("orange"));
			}
			else if ((iteration <= (LIMIT - 4 * OFFSET)) && (iteration>(LIMIT - 4.5 * OFFSET)))
			{
				al_put_pixel((DisplayDot->x), (DisplayDot->y), al_color_name("white"));
			}
			else
			{
				al_put_pixel((DisplayDot->x), (DisplayDot->y), al_color_name("navy"));
			}
}