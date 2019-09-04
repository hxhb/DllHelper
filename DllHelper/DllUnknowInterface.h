#pragma once
#include "DllHelper.h"

#ifndef dll_interface_
#define dll_interface_ struct
#endif

#define IUnknownEx UnknownEx

//基础接口
dll_interface_ UnknownEx
{
	//释放对象
	virtual void Release() = 0;

//接口查询
virtual void * QueryInterface(DWORD dwQueryVer) = 0;
};
