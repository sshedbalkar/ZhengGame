#include "math.h"

bool math::CircleOnCircle( float x0, float y0, float r0, 
						float x1, float y1, float r1,
						float* colliding_x, float* colliding_y )
{
	float distance_sq = ( x0 - x1 )*(x0 - x1 ) + ( y0 - y1 )*(y0 - y1 );
	if ( distance_sq < ( r0 + r1 ) * ( r0 + r1 ) )
	{
		if ( colliding_x && colliding_y )
		{
			float distance = sqrt(distance_sq);
			float colliding_distance = r0 + r1 - distance;
			*colliding_x = colliding_distance * ( x0 - x1 ) / distance;
			*colliding_y = colliding_distance * ( y0 - y1 ) / distance;
		}
		return true;
	}
	return false;
}

bool math::CircleOnRectangle( float x0, float y0, float r0,
						float x1, float y1, float w1, float h1,
						float* colliding_x, float* colliding_y )
{
	float x, y;
	float xr0 = x1 - w1 / 2.0f, xr1 = xr0 + w1;
	float yr0 = y1 - h1 / 2.0f, yr1 = yr0 + h1;
	if ( x0 < xr0 ) x = xr0;
	else if ( x0 > xr1 ) x = xr1;
	else x = x0;
	if ( y0 < yr0 ) y = yr0;
	else if ( y0 > yr1 ) y = yr1;
	else y = y0;

	if ( (x-x0)*(x-x0)+(y-y0)*(y-y0) < r0*r0 )
	{
		if ( colliding_x && colliding_y )
		{
			float distance = sqrt((x-x0)*(x-x0)+(y-y0)*(y-y0));
			float colliding_distance = r0 - distance;

			*colliding_x = colliding_distance*(x0 - x)/distance;
			*colliding_y = colliding_distance*(y0 - y)/distance;
		}
		return true;
	}
	else return false;
}

#include <iostream>
bool math::RectangleOnRectangle( float x0, float y0, float w0, float h0,
							float x1, float y1, float w1, float h1,
							float* colliding_x, float* colliding_y )
{

	if ( x0 - w0/2.0f >= x1 + w1/2.0f ) return false;
	if ( x0 + w0/2.0f <= x1 - w1/2.0f ) return false;
	if ( y0 - h0/2.0f >= y1 + h1/2.0f ) return false;
	if ( y0 + h0/2.0f <= y1 - h1/2.0f ) return false;

	if ( colliding_x && colliding_y )
	{
		*colliding_x = x0 > x1 ? 
			x1 + w1/2.0f - x0 + w0/2.0f : x1 - w1/2.0f - x0 - w0/2.0f;
		*colliding_y = y0 > y1 ? 
			y1 + h1/2.0f - y0 + h0/2.0f : y1 - h1/2.0f - y0 - h0/2.0f;

	}

	return true;

}
