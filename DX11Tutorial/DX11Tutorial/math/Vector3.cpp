#include <math.h>
#include "Vector3.h"

Vector3::Vector3()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

Vector3::Vector3( const Vector3& ref )
{
	this->x = ref.x;
	this->y = ref.y;
	this->z = ref.z;
}

Vector3::Vector3( float x_, float y_, float z_ )
{
	this->x = x_;
	this->y = y_;
	this->z = z_;
}

Vector3::~Vector3()
{

}

void Vector3::scale( float s )
{
	this->x /= s;
	this->y /= s;
	this->z /= s;
}

float Vector3::lenght()
{
	const float lengtSq = lenghtSquared();

	return (lengtSq > 0) ?  sqrtf( lengtSq ) : 0.f;
}

float Vector3::lenghtSquared()
{
	return x*x + y*y + z*z;
}

void Vector3::normalize()
{
	const float FL = lenght();

	this->x /= FL;
	this->y /= FL;
	this->z /= FL;
}


Vector3& Vector3::operator=( const Vector3& ref )
{
	this->x = ref.x;
	this->y = ref.y;
	this->z = ref.z;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& ref)
{
	this->x -= ref.x;
	this->y -= ref.y;
	this->z -= ref.z;
	return *this;
}
Vector3& Vector3::operator+=(const Vector3& ref)
{
	this->x += ref.x;
	this->y += ref.y;
	this->z += ref.z;
	return *this;
}
Vector3& Vector3::operator*=(const float s)
{
	this->x *= s;
	this->y *= s;
	this->z *= s;
	return *this;
}
Vector3& Vector3::operator/=(const float s)
{
	this->x /= s;
	this->y /= s;
	this->z /= s;
	return *this;
}

Vector3 operator+( const Vector3& lef,const Vector3& ref)
{
	Vector3 res;
	res.x = lef.x + ref.x; 
	res.y = lef.y + ref.y; 
	res.z = lef.z + ref.z; 
	return res;
}
Vector3 operator-( const Vector3& lef,const Vector3& ref)
{
	Vector3 res;
	res.x = lef.x - ref.x; 
	res.y = lef.y - ref.y; 
	res.z = lef.z - ref.z; 
	return res;
}

Vector3 operator*( const Vector3& lef,const Vector3& ref)
{
	Vector3 res;
	res.x = lef.x * ref.x; 
	res.y = lef.y * ref.y; 
	res.z = lef.z * ref.z; 
	return res;
}
Vector3 operator*( const float s,const Vector3& ref)
{
	Vector3 res;
	res.x = s * ref.x; 
	res.y = s * ref.y; 
	res.z = s * ref.z; 
	return res;
}
Vector3 operator*( const Vector3& lef,const float s)
{
	Vector3 res;
	res.x = lef.x * s; 
	res.y = lef.y * s; 
	res.z = lef.z * s; 
	return res;
}

Vector3 operator/( const Vector3& lef,const float s)
{
	Vector3 res;
	res.x = lef.x / s; 
	res.y = lef.y / s; 
	res.z = lef.z / s; 
	return res;
}

bool operator   ==( const Vector3& v1, const Vector3& v2 )
{
	return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z);
}
bool operator   !=( const Vector3& v1, const Vector3& v2 )
{
	return (v1.x != v2.x) || (v1.y != v2.y) || (v1.z != v2.z);
}
bool operator   < ( const Vector3& v1, const Vector3& v2 )
{
	if(v1.x < v2.x) return true;
	if(v1.x > v2.x) return false;

	if(v1.y < v2.y) return true;
	if(v1.y > v2.y) return false;

	if(v1.z < v2.z) return true;

	return false;
}