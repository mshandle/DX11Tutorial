#include "Vector4.h"
#include <math.h>

Vector4::Vector4():
		x(0.0f),
		y(0.0f),
		z(0.0f),
		w(0.0f)
{

}

Vector4::Vector4( const Vector4& ref )
{
	this->x = ref.x;
	this->y = ref.y;
	this->z = ref.z;
	this->w = ref.w;
}

Vector4::Vector4( float x_, float y_, float z_, float w_ )
{
	this->x = x_;
	this->y = y_;
	this->z = z_;
	this->w = w_;
}

Vector4::~Vector4()
{

}

void Vector4::scale( float s )
{
	this->x *= s;
	this->y *= s;
	this->z *= s;
	this->w *= s;
}

void Vector4::normalize()
{
	const float FL = lenght();

	this->x /= FL;
	this->y /= FL;
	this->z /= FL;
	this->w /= FL;
}

float Vector4::lenght()
{
	const float lengtSq = lenghtSquared();

	return (lengtSq > 0) ?  sqrtf( lengtSq ) : 0.f;
}

float Vector4::lenghtSquared()
{
	return (x*x + y*y + z*z + w*w);
}

Vector4& Vector4::operator=( const Vector4& ref )
{
	this->x = ref.x;
	this->y = ref.y;
	this->z = ref.z;
	this->w = ref.w;
	return *this;
}


Vector4& Vector4::operator+=( const Vector4& ref )
{
	this->x += ref.x;
	this->y += ref.y;
	this->z += ref.z;
	this->w += ref.w;
	return *this;
}

Vector4& Vector4::operator-=( const Vector4& ref )
{
	this->x -= ref.x;
	this->y -= ref.y;
	this->z -= ref.z;
	this->w -= ref.w;
	return *this;
}


Vector4& Vector4::operator*=( const float s)
{
	this->x *= s;
	this->y *= s;
	this->z *= s;
	this->w *= s;
	return *this;
}


Vector4& Vector4::operator/=( const float s)
{
	this->x /= s;
	this->y /= s;
	this->z /= s;
	this->w /= s;
	return *this;
}


Vector4 operator+( const Vector4& lef,const Vector4& ref)
{
	Vector4 res;
	res.x = lef.x + ref.x; 
	res.y = lef.y + ref.y; 
	res.z = lef.z + ref.z; 
	res.w = lef.w + ref.w;
	return res;
}
Vector4 operator-( const Vector4& lef,const Vector4& ref)
{
	Vector4 res;
	res.x = lef.x - ref.x; 
	res.y = lef.y - ref.y; 
	res.z = lef.z - ref.z; 
	res.w = lef.w - ref.w;
	return res;
}

Vector4 operator*( const Vector4& lef,const Vector4& ref)
{
	Vector4 res;
	res.x = lef.x * ref.x; 
	res.y = lef.y * ref.y; 
	res.z = lef.z * ref.z; 
	res.w = lef.w * ref.w;
	return res;
}
Vector4 operator*( const float s,const Vector4& ref)
{
	Vector4 res;
	res.x = s * ref.x; 
	res.y = s * ref.y; 
	res.z = s * ref.z; 
	res.w = s * ref.w;
	return res;
}
Vector4 operator*( const Vector4& lef,const float s)
{
	Vector4 res;
	res.x = lef.x * s; 
	res.y = lef.y * s; 
	res.z = lef.z * s;
	res.w = lef.w * s;
	return res;
}

Vector4 operator/( const Vector4& lef,const float s)
{
	Vector4 res;
	res.x = lef.x / s; 
	res.y = lef.y / s; 
	res.z = lef.z / s;
	res.w = lef.w / s;
	return res;
}

bool operator   ==( const Vector4& v1, const Vector4& v2 )
{
	return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z) && (v1.w == v2.w);
}
bool operator   !=( const Vector4& v1, const Vector4& v2 )
{
	return (v1.x != v2.x) || (v1.y != v2.y) || (v1.z != v2.z) || (v1.w != v2.w);
}
bool operator   < ( const Vector4& v1, const Vector4& v2 )
{
	if(v1.x < v2.x) return true;
	if(v1.x > v2.x) return false;

	if(v1.y < v2.y) return true;
	if(v1.y > v2.y) return false;

	if(v1.z < v2.z) return true;
	if(v1.z > v2.z) return false;

	if(v1.w < v2.w) return true;

	return false;
}