#pragma once

#include "../DllHelper/UsageExample_ExampleModule.h"

class ExampleModuleImpl:public IExampleModule
{
public:
	ExampleModuleImpl();
protected:
	~ExampleModuleImpl();

public:
	virtual void Release()override;
	virtual void* QueryInterface(DWORD dwQueryVer)override;

public:
	virtual void OnStartModule()override;
	virtual void OnShutdownModule()override;
};