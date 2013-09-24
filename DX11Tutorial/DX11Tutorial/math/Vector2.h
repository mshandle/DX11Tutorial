/********************************************************************
	created:	2013/09/23
	filename: 	D:\evad11engine\DX11Tutorial\DX11Tutorial\math\Vector2.h
	file ext:	h
	author:		wubaoqing
	
	purpose:	
*********************************************************************/

#ifndef VECTOR2_H_
#define VECTOR2_H_

class Vector2
{
public:

	Vector2();
	
	Vector2(float x, float y);

	Vector2(const Vector2& ref);

public:
	void	scale(float s);

	void	normalize();

	float	lenght();

	float	lenghtSquared();

	Vector2& operator=(const Vector2& ref);
	Vector2& operator-=(const Vector2& ref);
	Vector2& operator+=(const Vector2& ref);
	Vector2& operator*=(const float s);
	Vector2& operator/=(const float s);

public:


	float x, y;

};
Vector2 operator+( const Vector2& lef,const Vector2& ref);
Vector2 operator-( const Vector2& lef,const Vector2& ref);

Vector2 operator*( const Vector2& lef,const Vector2& ref);
Vector2 operator*( const float s,const Vector2& ref);
Vector2 operator*( const Vector2& lef,const float s);

Vector2 operator/( const Vector2& lef,const float s);

bool operator   ==( const Vector2& v1, const Vector2& v2 );
bool operator   !=( const Vector2& v1, const Vector2& v2 );
bool operator   < ( const Vector2& v1, const Vector2& v2 );

#endif//VECTOR2_H_