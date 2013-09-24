#include "Base/EngineBase.h"
#include "Vector2.h"

Vector2::Vector2():
		x(0.0f),
		y(0.0f)
{
	
}

Vector2::Vector2( float x_, float y_ )
{
	this->x = x_;
	this->y = y_;
}

Vector2::Vector2( const Vector2& ref )
{
	this->x = ref.x;
	this->y = ref.y;
}

void Vector2::scale( float s )
{
	this->x = x * s;
	this->y = y * s;
}

void Vector2::normalize()
{
	const float fL = lenght();
	this->x /= fL;
	this->y /= fL;
}

float Vector2::lenght()
{
	const float lengtSq = lenghtSquared();

	 return (lengtSq > 0) ?  sqrtf( lengtSq ) : 0.f;
}

float Vector2::lenghtSquared()
{
	return x*x + y*y;
}


Vector2& Vector2::operator-=(const Vector2& ref)
{
	this->x -=ref.x;
	this->y -=ref.y;
	return *this;

}
Vector2& Vector2::operator+=(const Vector2& ref)
{
	this->x +=ref.x;
	this->y +=ref.y;
	return *this;
}

Vector2& Vector2::operator*=(const float s)
{
	this->x *= s;
	this->y *= s;

	return *this;
}


Vector2& Vector2::operator/=(const float s)
{
	this->x /= s;
	this->y /= s;

	return *this;
}

Vector2& Vector2::operator=( const Vector2& ref )
{
	this->x = ref.x;
	this->y = ref.y;
	return *this;
}

Vector2 operator+( const Vector2& lef,const Vector2& ref)
{
	Vector2 re;
	re.x = lef.x + ref.x;
	re.y = lef.y + ref.y;
	return re;
}
Vector2 operator-( const Vector2& lef,const Vector2& ref)
{
	Vector2 re;
	re.x = lef.x - ref.x;
	re.y = lef.y - ref.y;
	return re;
}

Vector2 operator*( const Vector2& lef,const Vector2& ref)
{
	Vector2 re;
	re.x = lef.x * ref.x;
	re.y = lef.y * ref.y;
	return re;
}
Vector2 operator*( const float s,const Vector2& ref)
{
	Vector2 re;
	re.x = s * ref.x;
	re.y = s* ref.y;
	return re;
}
Vector2 operator*( const Vector2& lef,const float s)
{
	Vector2 re;
	re.x = s * lef.x;
	re.y = s* lef.y;
	return re;
}

Vector2 operator/( const Vector2& lef,const float s)
{
	Vector2 re;
	re.x =  lef.x / s;
	re.y =  lef.y / s;
	return re;
}

bool operator   ==( const Vector2& v1, const Vector2& v2 )
{
	return (v1.x == v2.x)&& (v1.y == v2.y);

}
bool operator   !=( const Vector2& v1, const Vector2& v2 )
{
	return (v1.x != v2.x)||(v1.y != v2.y);
}
bool operator   < ( const Vector2& v1, const Vector2& v2 )
{
	if(v1.x < v2.x) return true;
	if(v1.x > v2.x) return false;

	if(v1.y < v2.y)return true;

	return false;
}