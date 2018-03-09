#include "draw_triangle.h"
#include "utils.h"

static void triangle_fractal_recursion(point point1, point point2, point point3, double lEnd);
//Es llamada opr triangle fractal, es la funcion recursiva


void triangle_fractal(infoType * myData)
{
	double topAngle = 180 - abso(myData->leftAngle) - myData->rightAngle;
	double lenghtRightSide, lenghtLeftSide;
	point leftPoint, topPoint, rightPoint;//Los puntos del triangulo 

	leftPoint.xcoord = myData->x0;
	leftPoint.ycoord = myData->y0;
	rightPoint.xcoord = myData->x0 + myData->lStart;
	rightPoint.ycoord = myData->y0;
	//coordenadas de los dos primeros puntos
	lenghtLeftSide = sin(toRadian(myData->rightAngle)) *myData->lStart / sin(toRadian(topAngle));
	if (myData->leftAngle == 90.0) {
		topPoint.xcoord = myData->x0;
		topPoint.ycoord = myData->y0 - myData->lStart * tan(toRadian(abso(myData->rightAngle)));
	}//calculo el punto superior
	else {
		topPoint.xcoord = myData->x0 + lenghtLeftSide * cos(toRadian(abso(myData->leftAngle)));
		topPoint.ycoord = myData->y0 - lenghtLeftSide * sin(toRadian(abso(myData->leftAngle)));
	}

	al_draw_triangle(myData->x0, myData->y0, rightPoint.xcoord, rightPoint.ycoord, topPoint.xcoord, topPoint.ycoord, al_map_rgb(213, 38, 181), THICC);
	al_flip_display();

	triangle_fractal_recursion(leftPoint, rightPoint, topPoint, myData->lEnd);

}

void triangle_fractal_recursion(point p1, point p2, point p3, double lEnd)
{
	point massCenter = massCenterTriangle(&p1, &p2, &p3);
	ALLEGRO_COLOR actualColor = alRandColor();

	if (pithagoras(p1, massCenter) <= lEnd || pithagoras(p2, massCenter) <= lEnd || pithagoras(p3, massCenter) <= lEnd)
		return;

	al_draw_line(p1.xcoord, p1.ycoord, massCenter.xcoord, massCenter.ycoord, actualColor, THICC);
	al_draw_line(p2.xcoord, p2.ycoord, massCenter.xcoord, massCenter.ycoord, actualColor, THICC);
	al_draw_line(p3.xcoord, p3.ycoord, massCenter.xcoord, massCenter.ycoord, actualColor, THICC);//dibujo al centro desde cada esquina
	al_rest(0.01);//para que se aprecie la progrecion
	al_flip_display();
	triangle_fractal_recursion(p1, p2, massCenter, lEnd);//los 3 triangulos formados
	triangle_fractal_recursion(p1, p3, massCenter, lEnd);
	triangle_fractal_recursion(p2, p3, massCenter, lEnd);

}
