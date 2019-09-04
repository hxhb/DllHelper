#include "ExmpleModuleImpl.h"
#include <stdio.h>

ExampleModuleImpl::ExampleModuleImpl()
{
	printf("ExampleModuleImpl constructor\n");
}
ExampleModuleImpl::~ExampleModuleImpl()
{
	printf("ExampleModuleImpl destructor\n");
}

void ExampleModuleImpl::Release()
{
	printf("ExampleModuleImpl Release\n");
	delete this;
}	
void* ExampleModuleImpl::QueryInterface(DWORD dwQueryVer)
{
	return static_cast<IExampleModule*>(this);
}

void ExampleModuleImpl::OnStartModule()
{
	printf("ExampleModuleImpl OnStartModule\n");
}
void ExampleModuleImpl::OnShutdownModule()
{
	printf("ExampleModuleImpl OnShutdownModule\n");
}

extern "C" _declspec(dllexport) void * ExportDllClass(DWORD dwQueryVer)
{
	ExampleModuleImpl *Inst = new ExampleModuleImpl();
	return Inst->QueryInterface(dwQueryVer);
}