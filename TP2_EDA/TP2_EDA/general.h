#ifndef GENERAL_H


#define	GENERAL_H



typedef struct {

	char type[20]={0};
	double lStart = 0;
	double lEnd = 0;
	double leftAngle = 0;
	double rightAngle = 0;
	double lConstant = 0;
	double x0 = 0;
	double y0 = 0;
	double xF = 0;
	double yF= 0;
	double N= 0; //Grado del polígono

	bool lStartInit = 0;
	bool lEndInit = 0;
	bool lAngleInit = 0;
	bool rAngleInit = 0;
	bool lConstantInit = 0;
	bool x0Init = 0;
	bool y0Init = 0;
	bool xFInit = 0;
	bool yFInit = 0;
	bool Ninit = 0;
	
}infoType;


#endif