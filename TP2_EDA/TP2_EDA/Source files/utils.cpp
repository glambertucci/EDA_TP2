#include "utils.h"

ALLEGRO_COLOR alRandColor(void)
{
	return al_map_rgb(rand() % 256, rand() % 256, rand() % 256);
}
double pithagoras(point p1, point p2)
{
	return sqrt(square(p1.xcoord - p2.xcoord) + square(p1.ycoord - p2.ycoord));
}

point massCenterTriangle(point * p1, point * p2, point * p3)
{
	point massCenter;
	massCenter.xcoord = (p1->xcoord + p2->xcoord + p3->xcoord) / 3.0;
	massCenter.ycoord = (p1->ycoord + p2->ycoord + p3->ycoord) / 3.0;
	return massCenter;
}

double abso(double num)
{
	double end;
	if (num > 0)
		end = num;
	else
		end = -num;
	return end;
}
double toRadian(double num)
{
	return (num*3.141592 / 180);
}
double square(double num1)
{
	return num1 * num1;
}