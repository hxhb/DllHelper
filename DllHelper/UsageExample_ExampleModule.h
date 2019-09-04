#pragma once
#include "DllUnknowInterface.h"


#define IExampleModule ExampleModule

// 框架接口
dll_interface_ ExampleModule : public UnknownEx
{
public:
	//游戏开始
	virtual void OnStartModule() = 0;
	virtual void OnShutdownModule() = 0;

};

static const unsigned int IID_IExampleModule = 0x01010101;

// CGameFrameSink
DECLARE_MODULE_DYNAMIC(ExampleModule)