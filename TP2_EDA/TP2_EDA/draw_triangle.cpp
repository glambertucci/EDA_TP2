#include "draw_triangle.h"
#include "utils.h"


void triangle_fractal(double xstart, double ystart, double leftAngle, double rightAngle, double lStart, double lEnd)
{
	double topAngle = 180 - abso(leftAngle) - rightAngle; 
	double lenghtRightSide, lenghtLeftSide;
	point leftPoint, topPoint, rightPoint;//Los puntos del triangulo 

	leftPoint.xcoord = xstart;
	leftPoint.ycoord = ystart;
	rightPoint.xcoord = xstart + lStart;
	rightPoint.ycoord = ystart;
	//coordenadas de los dos primeros puntos
	lenghtLeftSide = sin(toRadian(rightAngle)) *lStart / sin(toRadian(topAngle)); 
	if (leftAngle == 90.0) {
		topPoint.xcoord = xstart;
		topPoint.ycoord = ystart - lStart * tan(toRadian(abso(rightAngle)));
	}//calculo el punto superior
	else {
		topPoint.xcoord = xstart + lenghtLeftSide * cos(toRadian(abso(leftAngle)));
		topPoint.ycoord = ystart - lenghtLeftSide * sin(toRadian(abso(leftAngle)));
	}

	al_draw_triangle(xstart, ystart, rightPoint.xcoord, rightPoint.ycoord, topPoint.xcoord, topPoint.ycoord, al_map_rgb(213, 38, 181), THICC);
	al_flip_display();

	triangle_fractal_recursion(leftPoint, rightPoint, topPoint, lEnd);

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
