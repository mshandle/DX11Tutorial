#ifndef _ENGINEBASE_H_
#define _ENGINEBASE_H_

#include <map>
typedef unsigned int uint32;


struct FastLessCompare
{
	bool operator() (const std::string& a, const std::string& b) const
	{
		const std::string::size_type la = a.length();
		const std::string::size_type lb = b.length();
		if (la == lb)
			return (memcmp(a.c_str(), b.c_str(), la*sizeof(std::string::value_type)) < 0);
		return (la < lb);
	}
};

template<typename _Ty>
class StringHashMap : public std::map<std::string, _Ty,FastLessCompare>
{
};

#define  SAFE_DELETE(X) if(NULL != X){delete X; X = NULL;}
#define  SAFE_RELEASE(X) if(NULL !=X){X->Release();X = NULL; }
typedef unsigned __int64	uint64;


inline bool almostEqual( const float f1, const float f2, const float epsilon = 0.0004f )
{
	return fabsf( f1 - f2 ) < epsilon;
}

inline bool almostEqual( const double d1, const double d2, const double epsilon = 0.0004 )
{
	return fabs( d1 - d2 ) < epsilon;
}

inline bool almostZero( const float f, const float epsilon = 0.0004f )
{
	return f < epsilon && f > -epsilon;
}

inline bool almostZero( const double d, const double epsilon = 0.0004 )
{
	return d < epsilon && d > -epsilon;
}

template<typename T>
inline bool almostEqual( const T& c1, const T& c2, const float epsilon = 0.0004f )
{
	if( c1.size() != c2.size() )
		return false;
	typename T::const_iterator iter1 = c1.begin();
	typename T::const_iterator iter2 = c2.begin();
	for( ; iter1 != c1.end(); ++iter1, ++iter2 )
		if( !almostEqual( *iter1, *iter2, epsilon ) )
			return false;
	return true;
}



#define RW_DECLARE_PROPERTY(varType,varName,FunName)\
	varType	FunName(void){return varName;}\
	void	FunName(varType FunNamae##Vlue){varName =FunNamae##Vlue; }\

#define	R_DECLARE_PROPERTY(varType,varName,FunName)\
		varType	FunName(void){return varName;}\


#endif//_ENGINEBASE_H_