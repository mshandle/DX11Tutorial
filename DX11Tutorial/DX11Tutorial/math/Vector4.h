/********************************************************************
	created:	2013/09/24
	filename: 	D:\evad11engine\DX11Tutorial\DX11Tutorial\math\Vector4.h
	file ext:	h
	author:		wubaoqing
	
	purpose:	
*********************************************************************/


#ifndef VECTOR4_H_
#define VECTOR4_H_

class Vector4
{
public:

	Vector4();

	Vector4(const Vector4& ref);

	Vector4(float x_, float y_, float z_, float w_);

	~Vector4();

public:

	void	scale(float s);

	void	normalize();

	float	lenght();

	float	lenghtSquared();

	Vector4& operator=(const Vector4& ref);
	Vector4& operator-=(const Vector4& ref);
	Vector4& operator+=(const Vector4& ref);
	Vector4& operator*=(const float s);
	Vector4& operator/=(const float s);

public:

	float x, y, z, w;
};


Vector4 operator+( const Vector4& lef,const Vector4& ref);
Vector4 operator-( const Vector4& lef,const Vector4& ref);

Vector4 operator*( const Vector4& lef,const Vector4& ref);
Vector4 operator*( const float s,const Vector4& ref);
Vector4 operator*( const Vector4& lef,const float s);

Vector4 operator/( const Vector4& lef,const float s);

bool operator   ==( const Vector4& v1, const Vector4& v2 );
bool operator   !=( const Vector4& v1, const Vector4& v2 );
bool operator   < ( const Vector4& v1, const Vector4& v2 );

#endif//VECTOR4_H_