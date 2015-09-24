#ifndef _UTILS_H_ 
#define _UTILS_H_ 

//A circle stucture
typedef struct 
{
	int x, y;
	int r;
} Circle;

typedef struct
{
    double x;
    double y;
} vec3;

extern double distanceSquared( int x1, int y1, int x2, int y2 );

#endif