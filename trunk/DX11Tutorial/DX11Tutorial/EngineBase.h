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

#define  SAFE_RELEASE(X) if(NULL != X){delete X; X = NULL;}

typedef unsigned __int64	uint64;

#endif//_ENGINEBASE_H_