#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "parseCmdLine.h"
#include "draw_triangle.h"
#include "mandelbrot.h"
#include "polygon.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <string.h>

#define SCREEN_WIDTH	400	
#define SCREEN_HEIGHT	600

int parseCallback(char *key, char *value, void *userInput);



/*************************************
*********verifiedIntervalAndInit******
**************************************
*verifiedIntervalAndInit se fija si la variable de la estructura de tipo infoType NO ha sido inicializada
*y verifica si pertenece al intervalo de valores correctos. En caso de ser as�, guarda el nuevO valor en la estrucutra
*
*INPUT:
*	1) isInit : bool que es verdadero si la variable a sido previamente inicializada.
*	2) parameter: variable en la que se guardar� el valor del string en float en caso de ser un input correcto.
*	3) a : extremo inferior del intervalo.
*	4) aClosed : booleano que es verdadero si el intervalo est� cerrado en a, falso si no.
*	5) b : extremo superior del intervalo.
*	6) bClosed : booleano que es verdadero si el intervalo est� cerrado en b, falso si no.
*
*OUTPUT:
*	booleando. true si el n�mero pertenece y la variable no hab�a sido previamente inicializada. false caso contrario.
*/

bool verifiedIntervalAndInit(bool isInit, double * parameter, char *value, double a, bool aClosed, double b, bool bClosed);

/******************************
*********verifiedInterval******
*******************************
*verifiedInterval se fija si un n�mero dado pertenece a un intervalo a-b dado,
*que puede ser cerrado [a,b], abierto (a,b) o derivados de estos dos.
*
*INPUT:
*	1) num : n�mero a decidir si pertenece al intervalo o no.
*	2) a : extremo inferior del intervalo.
*	3) aClosed : booleano que es verdadero si el intervalo est� cerrado en a, falso si no.
*	4) b : extremo superior del intervalo.
*	5) bClosed : booleano que es verdadero si el intervalo est� cerrado en b, falso si no.
*
*OUTPUT:
*	booleando. true si el n�mero pertenece. false si no.
*/

bool verifiedInterval(double num, double a, bool aClosed, double b, bool bClosed);


/******************************
*********verifiedData**********
*******************************
*verifiedData verifica que los datos recibidos (aquellos que se encuentran en una estructura de tipo infoType)
*sean coherentes.
*Verifica que se est� solicitando el dibujo de un fractal y que se tengan los par�metros necesarios
*para dibujar aquel fractal y que no hayan datos extra o sin sentido.
*
*INPUT:
*	1) userInput: puntero a estructura que contendr� la informaci�n a verificar.
*
*OUTPUT:
*	booleano. Falso en caso de que la informaci�n contenida sea incorrecta o sin sentido.
*	Verdadero en caso que la informaci�n sea correcta.
*/

bool verifiedData(infoType * userInput);

/******************************
*********runFractal************
*******************************
*runFractal recibe la informaci�n ya verificada del fractal que tiene que dibujar con sus par�metros correspondientes
*y dibuja el fractal apropiado.
*
*INPUT:
*	1) userInput: puntero a estructura que contendr� la informaci�n del fractal a dibujar.
*
*OUTPUT:
*	void.
*/

void runFractal(infoType * fractalInfo, ALLEGRO_DISPLAY* display);

/******************************
*********strToCapital**********
*******************************
*strToCapital convierte un string en may�scula a todos los caracteres que est�n en min�scula.
*
*INPUT:
*	1) str : string a convertir.
*
*OUTPUT:
*	void.
*/

void strToCapital(char * str);


/******************************
*********isFloatNumber**********
*******************************
*isFloatNumber verifica si un string representa a un punto flotante o no.
*ACLARACI�N: considera a "0.000" y dem�s cadenas de ceros que no sean "0" y "0.0" como incorrectas.
*
*INPUT:
*	1) str : string a verificar si representa un punto flotante o no.
*
*OUTPUT:
*	true si es punto flotante. false si no.
*/

bool isFloatNumber(char * str);


/******************************
*********main******************
*******************************/
int main(int argc, char *argv[])
{

	//CHEQUEAR QUE USERINPUT SE INICIALICE SIEMPRE TODO EN 0 Y EN FALSE!!!
	infoType userInput;
	pCallback functionPtr = &parseCallback;
	ALLEGRO_DISPLAY *display = NULL;

	if (al_init())
	{												//inicializa allegro
		if (al_init_primitives_addon())
		{
			if ((parseCmdLine(argc, argv, functionPtr, &userInput) > 0) && verifiedData(&userInput))
			{
				display = al_create_display(900.0, 700.0);
				if (!display)
				{
					fprintf(stderr, "Error: No se logr� crear display.\n");
				}
				runFractal(&userInput, display);
			}
			else
			{
				printf("Hubo un error en el procesamiento de los datos!");
			}
		}
		else printf("Error: No se pudo inicializar las primitivas de allegro!!\n");
		al_uninstall_system();

	}
	else printf("Error: No se pudo inicializar allegro!\n");

	printf("%s", userInput.type);

	return 0;
}


bool verifiedData(infoType * userInput) {

	bool error = false;	//booleano que indicara si hubo algun error en la informaci�n
						/*no habr� ning�n otra asignaci�n de error al valor false en el resto de la funci�n,
						por lo que si error es true en alg�n momento nunca dejar� de serlo hasta salir de la funci�n*/

						//verifico que se haya ingresado un fractal. El caso en que se haya ingresado uno incorrecto esta cubierto por parseCmdLine.
	if (!strcmp(userInput->type, "ERROR")) {
		printf("No se ha indicado el tipo de fractal que se quiere dibujar!!");
		error = true;
	}
	else if (!strcmp(userInput->type, "UNIFORME")) {

		//verifico que lStart haya sido inicializada
		if (!userInput->lStartInit) {
			printf("lStart no ha sido inicializado.");
			error = true;
		}
		//Elejimos NO poner else if para que al usuario le aparezcan todos los errores de input.

		//verifico que lEnd haya sido inicializada por usuario 
		if (!userInput->lEndInit) {
			printf("lEnd no ha sido inicializado.");
			error = true;
		}

		//verifico que leftAngle haya sido inicializada por usuario
		if (!userInput->lAngleInit) {
			printf("leftAngle no ha sido inicializado.");
			error = true;
		}

		//verifico que rightAngle haya sido inicializada por usuario
		if (userInput->rAngleInit) {
			printf("rightAngle no ha sido inicializado.");
			error = true;
		}

		//verifico que lConstant no se haya inicializado, para ser coherente con el tipo e fractal requerido
		if (userInput->lConstantInit) {
			printf("Le ha asignado un valor a lConstant cuando UNIFORME no lo necesita!");
			error = true;
		}

		if (!userInput->x0Init || !userInput->y0Init || !userInput->xFInit || !userInput->yFInit) {
			printf("No se han inicializado correctamente las coordenadas!");
			error = true;
		}


	}
	else if (!strcmp(userInput->type, "POLIGONO")) {

		//verifico que lStart haya sido inicializada por usuario
		if (!userInput->lStartInit) {
			printf("lStart no ha sido inicializado.");
			error = true;
		}

		//Elejimos NO poner else if para que al usuario le aparezcan todos los errores de input.

		//verifico que lEnd haya sido inicializada por usuario
		if (!userInput->lEndInit) {
			printf("lEnd no ha sido inicializado.");
			error = true;
		}

		//verifico que lConstant haya sido inicializada
		if (!userInput->lConstantInit) {
			printf("lConstant no ha sido inicializado.");
			error = true;
		}


		//verifico que los �ngulos no hayan sido inicializados para que haya coherencia con el fractal que se est� pidiendo
		if (userInput->rAngleInit || userInput->lAngleInit) {
			printf("Los �ngulos no pueden ser inicializados, ya que no tiene sentido con el tipo de fractal que se est� pidiendo");
			error = true;
		}

		if (!userInput->x0Init || !userInput->y0Init || !userInput->xFInit || !userInput->yFInit) {
			printf("No se han inicializado correctamente las coordenadas!");
			error = true;
		}

		if (!userInput->Ninit ) {
			printf("No se ha inicializado correctamente el tipo de pol�gono");
			error = true;
		}

	}
	else if (!strcmp(userInput->type, "MANDELBROT")) {

		if (!userInput->x0Init || !userInput->y0Init || !userInput->xFInit || !userInput->yFInit) {
			printf("No se han inicializado correctamente las coordenadas!");
			error = true;
		}
		//verifico que lStart NO haya sido inicializada por usuario
		if (userInput->lStartInit) {
			printf("lStart ha sido inicializado.");
			error = true;
		}

		//Elejimos NO poner else if para que al usuario le aparezcan todos los errores de input.

		//verifico que lEnd NO haya sido inicializada por usuario
		if (userInput->lEndInit) {
			printf("lEnd ha sido inicializado.");
			error = true;
		}

		//verifico que lConstant NO haya sido inicializada
		if (userInput->lConstantInit) {
			printf("lConstant ha sido inicializado.");
			error = true;
		}


		//verifico que los �ngulos no hayan sido inicializados para que haya coherencia con el fractal que se est� pidiendo
		if (userInput->rAngleInit || userInput->lAngleInit) {
			printf("Los �ngulos no pueden ser inicializados, ya que no tiene sentido con el tipo de fractal que se est� pidiendo");
			error = true;
		}
	}

	return error;
}


void runFractal(infoType * fractalInfo, ALLEGRO_DISPLAY* display)
{

	bool error = false;

	if (!strcmp(fractalInfo->type, "UNIFORME"))
		triangle_fractal(fractalInfo);

	else if (!strcmp(fractalInfo->type, "POLIGONO"))
	{
		polygon(fractalInfo);
	}
	else if (!strcmp(fractalInfo->type, "MANDELBROT"))
	{
		MandelAl(fractalInfo, display);
	}
}


bool verifiedInterval(double num, double a, bool aClosed, double b, bool bClosed) {

	bool verified = false;

	if (aClosed) {
		if (bClosed)
			verified = ((num >= a) && (num <= b));

		else
			verified = ((num >= a) && (num < b));
	}
	else {
		if (bClosed)
			verified = ((num > a) && (num <= b));
		else
			verified = ((num > a) && (num < b));
	}

	//printf("\n Es verified es:%d\n", verified);
	//printf("\n num es:%d\n", num);
	return verified;

}

int parseCallback(char *key, char *value, void *userInput)
{



	bool validInput = false;
	infoType *myData = (infoType *)userInput;

	//si recibe opci�n
	if (key != NULL)
	{

		//paso a capital letters a la key y al value para comparar cualquier manera de escribir el input. 
		//(ejemplo: "UniForme" y "uniforme" se leer�an "UNIFORME" indistintamente)
		strToCapital(key);
		strToCapital(value);

		printf("%s\n", key);
		printf("%s\n", value);

		if (!strcmp(key, "TYPE"))
		{

			if (!strcmp(value, "UNIFORME"))
			{
				strcpy_s(myData->type, "UNIFORME");
				validInput = true;
			}
			else if (!strcmp(value, "POLIGONO"))
			{
				strcpy_s(myData->type, "POLIGONO");
				validInput = true;
			}
			else if (!strcmp(value, "MANDELBROT"))
			{
				strcpy_s(myData->type, "MANDELBROT");
				validInput = true;
			}
			else
			{
				strcpy_s(myData->type, "ERROR");
				printf("Par�metro incorrecto!");
			}
		}
		else if (!strcmp(key, "LSTART"))
		{

			//verifico que lStart no haya sido inicializada por usuario y pertenezca a (0, 100]	
			validInput = verifiedIntervalAndInit(myData->lStartInit, &myData->lStart, value, 0, false, 100, true);
			if (validInput == true)
			{
				myData->lStartInit++;
				myData->lStart=atof(value);
			}

			//printf("\nValidinput:%d\n", validInput);

		}
		else if (!strcmp(key, "N")) {

			//verifico que el numero de lados del pol�gono no haya sido inicializada por usuario y pertenezca a (0, 100]	
			validInput = verifiedIntervalAndInit(myData->Ninit, &myData->N, value, 0, false,100, true);
			if (validInput == true)
			{
				myData->Ninit++;
				myData->N = atof(value);
			}
		}
		else if (!strcmp(key, "LEND")) {
			//verifico que lEnd no haya sido inicializada por usuario y  pertenezca a (0, 100)
			validInput = verifiedIntervalAndInit(myData->lEndInit, &myData->lEnd, value, 0, false, 100, false);
			
			if (validInput == true)
			{
				myData->lEndInit++;
				myData->lEnd = atof(value);

			}
		}
		else if (!strcmp(key, "LCONSTANT")) {
			//verifico que lConstant no haya sido inicializada y pertenezca a (0,1)
			validInput = verifiedIntervalAndInit(myData->lConstantInit, &myData->lConstant, value, 0, false, 1, false);

			if (validInput == true)
			{
				myData->lConstantInit++;
				myData->lConstant =atof(value);

			}
		}
		else if (!strcmp(key, "LEFTANGLE")) {
			//verifico que leftAngle no haya sido inicializada por usuario y  pertenezca a [-90,0]	
			validInput = verifiedIntervalAndInit(myData->lAngleInit, &myData->leftAngle, value, -90, true, 0, true);

			if (validInput == true)
			{
				myData->lAngleInit++;
				myData->leftAngle = atof(value);
			}

		}
		else if (!strcmp(key, "RIGHTANGLE")) {
			//verifico que rightAngle no haya sido inicializada por usuario y  pertenezca a [0,90]	
			validInput = verifiedIntervalAndInit(myData->rAngleInit, &myData->rightAngle, value, 0, true, 90, true);

			if (validInput == true)
			{
				myData->rAngleInit++;
				myData->rightAngle = atof(value);
			}
		}
		else if (!strcmp(key, "X0")) {
			//verifico que x0 no haya sido inicializado y pertenezca al interior de la pantalla
			validInput = verifiedIntervalAndInit(myData->x0Init, &myData->x0, value, 0, false, SCREEN_WIDTH, false);
			if (validInput == true)
			{
				myData->x0Init++;
				myData->x0 = atof(value);
			}
		}
		else if (!strcmp(key, "Y0")) {
			//verifico que y0 no haya sido inicializado y pertenezca al interior de la pantalla
			validInput = verifiedIntervalAndInit(myData->y0Init, &myData->y0, value, 0, false, SCREEN_HEIGHT, false);

			if (validInput == true)
			{
				myData->y0Init++;
				myData->y0 = atof(value);
			}
		}
		else if (!strcmp(key, "XF")) {
			//verifico que xF no haya sido inicializado y pertenezca al interior de la pantalla
			validInput = verifiedIntervalAndInit(myData->xFInit, &myData->xF, value, 0, false, SCREEN_WIDTH, false);
			if (validInput == true)
			{
				myData->xFInit++;
				myData->xF = atof(value);
			}
		}
		else if (!strcmp(key, "YF")) {
			//verifico que yF no haya sido inicializado y pertenezca al interior de la pantalla
			validInput = verifiedIntervalAndInit(myData->yFInit, &myData->yF, value, 0, false, SCREEN_HEIGHT, false);
			
			if (validInput == true)
			{
				myData->yFInit++;
				myData->yF = atof(value);
			}
		}
		else {
			validInput = false;
			printf("Hay variables que han sido inicializadas m�s de una vez o que no pertenecen al rango de intervalos correcto!");
		}
	}
	
	printf("\nValidinput:%d\n", validInput);
	return validInput;


}


void strToCapital(char * str) 
{

	int i = 0;

	while (str[i]) {
		str[i] = toupper(str[i]);
		i++;
	}

}


bool isFloatNumber(char * str) {

	bool isNumeric;
	int i = 0;
	if (!atof(str)) {
		if (!strcmp(str, "0.0") || !strcmp(str, "0"))			//no admitimos "cosas raras" como "0.0000"
			isNumeric = true;
		else
			isNumeric = false;
	}
	else
		isNumeric = true;
	//printf("\n Es numerico es:%d\n", isNumeric);
	return isNumeric;
}
/*************************************
*********verifiedIntervalAndInit******
**************************************
*verifiedIntervalAndInit se fija si la variable de la estructura de tipo infoType NO ha sido inicializada
*y verifica si pertenece al intervalo de valores correctos. En caso de ser as�, guarda el nuevO valor en la estrucutra
*
*INPUT:
*	1) isInit : bool que es verdadero si la variable a sido previamente inicializada.
*	2) parameter: variable en la que se guardar� el valor del string en float en caso de ser un input correcto.
*	3) a : extremo inferior del intervalo.
*	4) aClosed : booleano que es verdadero si el intervalo est� cerrado en a, falso si no.
*	5) b : extremo superior del intervalo.
*	6) bClosed : booleano que es verdadero si el intervalo est� cerrado en b, falso si no.
*
*OUTPUT:
*	booleando. true si el n�mero pertenece y la variable no hab�a sido previamente inicializada. false caso contrario.
*/


bool verifiedIntervalAndInit(bool isInit, double * parameter, char *value, double a, bool aClosed, double b, bool bClosed) {

	bool validInput = false;
	bool i;

	if (!isInit && isFloatNumber(value) && verifiedInterval(atof(value), a, aClosed, b, bClosed)) {
		*parameter = atof(value);
		validInput = true;
		//printf("\nValidinput:%d\n", validInput);
	}
	/*
	i = isFloatNumber(value);
	printf("\nisFloatNumber(value):%d\n", i);

	i = verifiedInterval(atof(value), a, aClosed, b, bClosed);
	printf("\nerifiedInterval:%d\n", i);

	printf("\nisInit:%d\n", isInit);
	*/
	return validInput;
}


