#pragma once

#include <d3dx9.h>

#define PI 3.1415926535897932384626f
typedef D3DXVECTOR2 Vector2;
typedef D3DXVECTOR3 Vector3;
typedef D3DXVECTOR4 Vector4;
typedef D3DXMATRIX	Matrix4x4;
#define Vector2Length			D3DXVec2Length
#define Vector3Length			D3DXVec3Length
#define Vector2LengthSq			D3DXVec2LengthSq
#define Vector3LengthSq			D3DXVec3LengthSq
#define MatrixMultiply			D3DXMatrixMultiply
#define MatrixTranslation		D3DXMatrixTranslation
#define MatrixRotation			D3DXMatrixRotationZ
#define MatrixScaling			D3DXMatrixScaling

namespace math
{
	bool CircleOnCircle( float x0, float y0, float r0, 
						 float x1, float y1, float r1,
						 float* colliding_x, float* colliding_y );

	bool CircleOnRectangle( float x0, float y0, float r0,
							float x1, float y1, float w1, float h1,
							float* colliding_x, float* colliding_y );

	bool RectangleOnRectangle( float x0, float y0, float w0, float h0,
							   float x1, float y1, float w1, float h1,
							   float* colliding_x, float* colliding_y );
};
