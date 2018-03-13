#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "parseCmdLine.h"

/******************************
*********verifiedInterval******
*******************************
*verifiedInterval se fija si un número dado pertenece a un intervalo a-b dado,
*que puede ser cerrado [a,b], abierto (a,b) o derivados de estos dos. 
*
*INPUT:
*	1) num : número a decidir si pertenece al intervalo o no.
*	2) a : extremo inferior del intervalo.
*	3) aClosed : booleano que es verdadero si el intervalo está cerrado en a, falso si no.
*	4) b : extremo superior del intervalo.
*	5) bClosed : booleano que es verdadero si el intervalo está cerrado en b, falso si no.
*
*OUTPUT:	
*	booleando. true si el número pertenece. false si no.
*/

bool verifiedInterval(double num, double a, bool aClosed, double b, bool bClosed);


/******************************
*********verifiedData**********
*******************************
*verifiedData verifica que los datos recibidos (aquellos que se encuentran en una estructura de tipo infoType)
*sean coherentes. 
*Verifica que se esté solicitando el dibujo de un fractal y que se tengan los parámetros necesarios
*para dibujar aquel fractal y que no hayan datos extra o sin sentido.
*
*INPUT:
*	1) userInput: puntero a estructura que contendrá la información a verificar.
*
*OUTPUT:	
*	booleano. Falso en caso de que la información contenida sea incorrecta o sin sentido. 
*	Verdadero en caso que la información sea correcta.
*/

bool verifiedData(infoType * userInput);

/******************************
*********runFractal************
*******************************
*runFractal recibe la información ya verificada del fractal que tiene que dibujar con sus parámetros correspondientes 
*y dibuja el fractal apropiado.
*
*INPUT:
*	1) userInput: puntero a estructura que contendrá la información del fractal a dibujar.
*
*OUTPUT:	
*	void.
*/

void runFractal(infoType * fractalInfo, ALLEGRO_DISPLAY* display);

/******************************
*********strToCapital**********
*******************************
*strToCapital convierte un string en mayúscula a todos los caracteres que estén en minúscula.
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
*ACLARACIÓN: considera a "0.000" y demás cadenas de ceros que no sean "0" y "0.0" como incorrectas.
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
int main (int argc, char *argv[])
{

	//CHEQUEAR QUE USERINPUT SE INICIALICE SIEMPRE TODO EN 0 Y EN FALSE!!!
	infoType userInput;
	pCallback functionPtr = &parseCallback;
	
	if(al_init())
	{												//inicializa allegro
		if (al_init_primitives_addon())
		{
			if( ( parseCmdLine(argc, argv, functionPtr, &userInput) > 0 ) && verifiedData(&userInput))
			{
				display = al_create_display(900.0, 700.0);
				if (!display)
				{
					printf(stderr, "Error: No se logró crear display.\n");
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

	
	
	return 0;
}
	

bool verifiedData(infoType * userInput){

	bool error = false;	//booleano que indicara si hubo algun error en la información
				/*no habrá ningún otra asignación de error al valor false en el resto de la función,
				por lo que si error es true en algún momento nunca dejará de serlo hasta salir de la función*/
	
	//verifico que se haya ingresado un fractal. El caso en que se haya ingresado uno incorrecto esta cubierto por parseCmdLine.
	if(userInput->type != NULL){			
		printf("No se ha indicado el tipo de fractal que se quiere dibujar!!");
		error = true;
	}
	else if( !strcmp(userInput->type, "UNIFORME") ){

		//verifico que lStart haya sido inicializada
		if(!fractalInfo->lStartInit){
			printf("lStart no ha sido inicializado.");
			error = true;			
		}
		//Elejimos NO poner else if para que al usuario le aparezcan todos los errores de input.

		//verifico que lEnd haya sido inicializada por usuario 
		if(!fractalInfo->lEndInit){
			printf("lEnd no ha sido inicializado.");
			error = true;			
		}

		//verifico que leftAngle haya sido inicializada por usuario
		if(!fractalInfo->leftAngleInit){
			printf("leftAngle no ha sido inicializado.");
			error = true;			
		}
		
		//verifico que rightAngle haya sido inicializada por usuario
		if(fractalInfo->rightAngleInit){
			printf("rightAngle no ha sido inicializado.");
			error = true;			
		}

		//verifico que lConstant no se haya inicializado, para ser coherente con el tipo e fractal requerido
		if(fractalInfo->lConstantInit){
			printf("Le ha asignado un valor a lConstant cuando UNIFORME no lo necesita!");
			error = true;
		}
		
		if(!fractalInfo->x0Init || !fractalInfo->y0Init || !fractalInfo->xFInit || !fractalInfo->yFInit){
			printf("No se han inicializado correctamente las coordenadas!");
			error = true;
		}

		
	}
	else if( !strcmp(userInput->type, "OCTOGONO") ){

		//verifico que lStart haya sido inicializada por usuario
		if(!fractalInfo->lStartInit){
			printf("lStart no ha sido inicializado.");
			error = true;			
		}

		//Elejimos NO poner else if para que al usuario le aparezcan todos los errores de input.

		//verifico que lEnd haya sido inicializada por usuario
		if(!fractalInfo->lEndInit){
			printf("lEnd no ha sido inicializado.");
			error = true;			
		}

		//verifico que lConstant haya sido inicializada
		if(!fractalInfo->lConstantInit){
			printf("lConstant no ha sido inicializado.");
			error = true;			
		}


		//verifico que los ángulos no hayan sido inicializados para que haya coherencia con el fractal que se está pidiendo
		if(fractalInfo->rAngleInit || fractalInfo->lAngleInit){
			printf("Los ángulos no pueden ser inicializados, ya que no tiene sentido con el tipo de fractal que se está pidiendo");
			error = true;
		}

		if(!fractalInfo->x0Init || !fractalInfo->y0Init || !fractalInfo->xFInit || !fractalInfo->yFInit){
			printf("No se han inicializado correctamente las coordenadas!");
			error = true;
		}
		
	}
	else if( !strcmp(userInput->type, "MANDELBROT") ){

		if(!fractalInfo->x0Init || !fractalInfo->y0Init || !fractalInfo->xFInit || !fractalInfo->yFInit){
			printf("No se han inicializado correctamente las coordenadas!");
			error = true;
		}
		//verifico que lStart NO haya sido inicializada por usuario
		if(fractalInfo->lStartInit){
			printf("lStart ha sido inicializado.");
			error = true;			
		}

		//Elejimos NO poner else if para que al usuario le aparezcan todos los errores de input.

		//verifico que lEnd NO haya sido inicializada por usuario
		if(fractalInfo->lEndInit){
			printf("lEnd ha sido inicializado.");
			error = true;			
		}

		//verifico que lConstant NO haya sido inicializada
		if(fractalInfo->lConstantInit){
			printf("lConstant ha sido inicializado.");
			error = true;			
		}


		//verifico que los ángulos no hayan sido inicializados para que haya coherencia con el fractal que se está pidiendo
		if(fractalInfo->rAngleInit || fractalInfo->lAngleInit){
			printf("Los ángulos no pueden ser inicializados, ya que no tiene sentido con el tipo de fractal que se está pidiendo");
			error = true;
		}
	}

	return error;
}


void runFractal(infoType * fractalInfo, ALLEGRO_DISPLAY* display)
{

	bool error = false;
	Coord_t pi;
	Coord_t pf;
	if( !strcmp(userInput->type, "UNIFORME") )
		triangle_fractal(&fractalInfo);

	else if( !strcmp(userInput->type, "OCTOGONO") )
	{
		//FALTA LA DE GERMO!!!
	}
	else if( !strcmp(userInput->type, "MANDELBROT") )
	{
		MandelAl(&fractalInfo, display);
	}
}


bool verifiedInterval(double num, double a, bool aClosed, double b, bool bClosed){

	bool verified = false;

	if(aClosed){
		if(bClosed)
			verified = ( (num >= a) && (num <= b) );
		
		else
			verified = ( (num >= a) && (num < b) );	
	}
	else{
		if(bClosed)
			verified = ( (num > a) && (num <= b) );
		else 
			verified = ( (num > a) && (num < b) );
	}	

	return verified;

}

int parseCallback(char *key, char *value, void *userInput)
{

	

	bool validInput = false;		
	infoType *myData = (infoType *) userInput;	
	interval_t intervalo;
	//si recibe opción
	if (key != NULL){

		//paso a capital letters a la key y al value para comparar cualquier manera de escribir el input. 
		//(ejemplo: "UniForme" y "uniforme" se leerían "UNIFORME" indistintamente)
		strToCapital(key);
		strToCapital(value);

		if(!strcmp(key, "TYPE")){

			if (!strcmp(value, "UNIFORME")){
				myData->type = "UNIFORME";
				validInput = true;
			}
			else if(!strcmp(value, "OCTOGONO")){
				myData->type = "OCTOGONO";
				validInput = true;
			}
			else if(!strcmp(value, "MANDELBROT")){
				myData->type = "MANDELBROT";
				validInput = true;
			}
			else	
				printf("Parámetro incorrecto!");
		}
		else if(!strcmp(key, "LSTART")){
			
			//verifico que lStart no haya sido inicializada por usuario y pertenezca a (0, 100]	
			validInput = verifiedIntervalAndInit(myData->lStartInit, &myData->lStart, value, 0, false, 100, true);
			
		}
		else if(!strcmp(key, "LEND")){
			//verifico que lEnd no haya sido inicializada por usuario y  pertenezca a (0, 100)
			validInput = verifiedIntervalAndInit(myData->lEndInit, &myData->lEnd, value, 0, false, 100, false);
		}
		else if(!strcmp(key, "LCONSTANT")){
			//verifico que lConstant no haya sido inicializada y pertenezca a (0,1)
			validInput = verifiedIntervalAndInit(myData->lConstantInit, &myData->lConstant, value, 0, false, 1, false);
		}
		else if(!strcmp(key, "LEFTANGLE")){
			//verifico que leftAngle no haya sido inicializada por usuario y  pertenezca a [-90,0]	
			validInput = verifiedIntervalAndInit(myData->lAngleInit, &myData->lAngle, value, -90, true, 0, true);
		
		}
		else if(!strcmp(key, "RIGHTANGLE")){
			//verifico que rightAngle no haya sido inicializada por usuario y  pertenezca a [0,90]	
			validInput = verifiedIntervalAndInit(myData->rAngleInit, &myData->rAngle, value, 0, true, 90, true);			
		}
		else if(!strcmp(key, "X0")){
			//verifico que x0 no haya sido inicializado y pertenezca al interior de la pantalla
			validInput = verifiedIntervalAndInit(myData->x0Init, &myData->x0, value, 0, false, SCREEN_WIDTH, false);
		}
		else if(!strcmp(key, "Y0")){
			//verifico que y0 no haya sido inicializado y pertenezca al interior de la pantalla
			validInput = verifiedIntervalAndInit(myData->y0Init, &myData->y0, value, 0, false, SCREEN_HEIGHT, false);
		}
		else if(!strcmp(key, "XF"){
			//verifico que xF no haya sido inicializado y pertenezca al interior de la pantalla
			validInput = verifiedIntervalAndInit(myData->xFInit, &myData->xF, value, 0, false, SCREEN_WIDTH, false);
		}
		else if(!strcmp(key, "YF")){
			//verifico que yF no haya sido inicializado y pertenezca al interior de la pantalla
			validInput = verifiedIntervalAndInit(myData->yFInit, &myData->yF, value, 0, false, SCREEN_HEIGHT, false);
		}
		else{ 
			validInput = false;
			printf("Hay variables que han sido inicializadas más de una vez o que no pertenecen al rango de intervalos correcto!");
		}
	}  

	return validInput;	 
	

}


void strToCapital(char * str){

	int i = 0;
   
   	while(str[i]) {
      		str[i] = toupper(str[i]);
      		i++;
   	}

}


bool isFloatNumber(char * str){

	bool isNumeric;
	int i = 0;
	if(!atof(str)){
		if(!strcmp(str, "0.0") || !strcmp(str, "0"))			//no admitimos "cosas raras" como "0.0000"
			isNumeric = true;
		else	
			isNumeric = false;			
	}
	else
		isNumeric = true;
	
	return isNumeric;
}
/*************************************
*********verifiedIntervalAndInit******
**************************************
*verifiedIntervalAndInit se fija si la variable de la estructura de tipo infoType NO ha sido inicializada
*y verifica si pertenece al intervalo de valores correctos. En caso de ser así, guarda el nuevO valor en la estrucutra
*
*INPUT:
*	1) isInit : bool que es verdadero si la variable a sido previamente inicializada.
*	2) parameter: variable en la que se guardará el valor del string en float en caso de ser un input correcto.
*	3) a : extremo inferior del intervalo.
*	4) aClosed : booleano que es verdadero si el intervalo está cerrado en a, falso si no.
*	5) b : extremo superior del intervalo.
*	6) bClosed : booleano que es verdadero si el intervalo está cerrado en b, falso si no.
*
*OUTPUT:	
*	booleando. true si el número pertenece y la variable no había sido previamente inicializada. false caso contrario.
*/

bool verifiedIntervalAndInit(bool isInit,double * parameter, char *value, double a, double b, bool aClosed, bool bClosed);

bool verifiedIntervalAndInit(bool isInit,double * parameter, char *value, double a, double b, bool aClosed, bool bClosed){

	bool validInput = false;

	if(!isInit && isFloatNumber(value) && verifiedInterval(atof(value), a, aClosed, b, bClosed)){
		*parameter = atof(value);
		validInput = true;
	}

	return validInput;	
}


