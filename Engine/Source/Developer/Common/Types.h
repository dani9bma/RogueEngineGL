#pragma once
#include <cstdint>
#include "EASTL/string.h"
#include "EASTL/shared_ptr.h"
#include "EASTL/unique_ptr.h"
#include "EASTL/vector.h"

typedef signed char			int8;
typedef short				int16;
typedef int					int32;
typedef long long			int64;

typedef unsigned char		byte;
typedef unsigned short		uint16;
typedef unsigned int		uint;
typedef unsigned long long	uint64;


typedef eastl::string		EAString;

template<typename T>
using EASharedPtr = eastl::shared_ptr<T>;

template<typename T>
using EAVector = eastl::vector<T>;

template<typename T>
using EAUniquePtr = eastl::unique_ptr<T>;

template<typename T, typename...Args>
EASharedPtr<T> EAMakeShared(Args &&...args)
{
	return eastl::make_shared<T>(std::forward<Args>(args)...);
}
template<typename T, typename...Args>
EAUniquePtr<T> EAMakeUnique(Args &&...args)
{
	return eastl::make_unique<T>(std::forward<Args>(args)...);
}

//Operator Declaration
inline void* __cdecl operator new[](size_t size, const char*, int, unsigned, const char*, int)
{
	return new uint8_t[size];
}

inline void * __cdecl operator new[](unsigned int size, unsigned int, unsigned int, char const *, int, unsigned int, char const *, int)
{
	return new uint8_t[size];
}