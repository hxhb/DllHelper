#include "UsageExample_ExampleModule.h"
#include <stdio.h>
#define DH(a) C##a##Helper


int main()
{
	DH(ExampleModule) ExportDllInstance;
	ExportDllInstance.SetModuleCreateInfo("ExampleModuleImpl.dll", "ExportDllClass");

	bool load_success = ExportDllInstance.OpenDll();
	if (load_success)
	{
		ExportDllInstance.m_pIDllEntry->OnStartModule();
	}
	else
	{
		printf("error code: %d", GetLastError());
		
	} 
	
	if (load_success)
		ExportDllInstance.CloseDll();
	
	system("pause");

	
}