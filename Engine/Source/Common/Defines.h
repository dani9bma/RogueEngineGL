#pragma once

#include "../utils/Log.h"

#include <d3d11.h>
#include <d3dcompiler.h>
#include <winerror.h>

static EAString GetHRError(HRESULT hr)
{
	switch (hr)
	{
	case E_ABORT:
		return "Operation Aborted";
	case E_ACCESSDENIED:
		return "Access Denied";
	case E_FAIL:
		return "Unspecified Failure";
	case E_HANDLE:
		return "Handle is not valid";
	case E_INVALIDARG:
		return "One or more arguments are not valid";
	case E_NOINTERFACE:
		return "No such interface supported";
	case E_NOTIMPL:
		return "Not Implemented";
	case E_OUTOFMEMORY:
		return "Failed to allocate necessary memory";
	case E_POINTER:
		return "Pointer is not valid";
	case E_UNEXPECTED:
		return "Unexpected Failure";
	default:
		return "Unknown Error";
	}
}

static void CheckD3D(HRESULT hr, int line, EAString file)
{
	if(FAILED(hr))
	{
		LOG_P(Skel::LogLevel::Error, Skel::LogModule::Rendering, "%s at line: %d - %s", GetHRError(hr), line, file.c_str());
		__debugbreak();
	}
}

#define Check(x) \
{	\
HRESULT hr = x;\
CheckD3D(hr, __LINE__, __FILE__);\
}	\

#define ReleaseCOM(x) \
	if(x)	\
	{	\
		x->Release(); \
		x = nullptr; \
	}	\
	
#define Assert(x) \
		if(!(x)) LOG_P(Skel::LogLevel::Error, Skel::LogModule::Rendering, "Assertion Failed at %d - %s", __LINE__, __FILE__);


#define FORCEINLINE __forceinline									/* Force code to be inline */
#define FORCENOINLINE __declspec(noinline)							/* Force code to NOT be inline */