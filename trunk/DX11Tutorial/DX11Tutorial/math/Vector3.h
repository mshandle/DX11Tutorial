/********************************************************************
	created:	2013/09/24
	filename: 	D:\evad11engine\DX11Tutorial\DX11Tutorial\math\Vector3.h
	file ext:	h
	author:		wubaoqing
	
	purpose:	
*********************************************************************/


#ifndef VECTOR3_H_
#define VECTOR3_H_



class Vector3 
{
public:

	Vector3();

	Vector3(const Vector3& ref);

	Vector3(float x, float y, float z);

	~Vector3();

public:
	void	scale(float s);

	void	normalize();

	float	lenght();

	float	lenghtSquared();

	Vector3& operator=(const Vector3& ref);
	Vector3& operator-=(const Vector3& ref);
	Vector3& operator+=(const Vector3& ref);
	Vector3& operator*=(const float s);
	Vector3& operator/=(const float s);
public:

	float x;

	float y;

	float z;

};


Vector3 operator+( const Vector3& lef,const Vector3& ref);
Vector3 operator-( const Vector3& lef,const Vector3& ref);

Vector3 operator*( const Vector3& lef,const Vector3& ref);
Vector3 operator*( const float s,const Vector3& ref);
Vector3 operator*( const Vector3& lef,const float s);

Vector3 operator/( const Vector3& lef,const float s);

bool operator   ==( const Vector3& v1, const Vector3& v2 );
bool operator   !=( const Vector3& v1, const Vector3& v2 );
bool operator   < ( const Vector3& v1, const Vector3& v2 );

#endif//VECTOR3_H_