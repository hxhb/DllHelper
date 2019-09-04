#pragma once

#include <Windows.h>
#include <assert.h>

typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef unsigned long       DWORD;

#define ZeroMem(a) memset(a, 0, sizeof(a))
#define CountArray(Array) (sizeof(Array)/sizeof(Array[0]))
using FPCreateProc = void * (DWORD dwInterfaceVer);

#define CDllHelper DllHelper

template<typename T> class DllHelper
{
public:
	DWORD							m_dwVersion;						//接口版本
																		//组件属性
public:
	TCHAR							m_szCreateProc[32];					//创建函数
	TCHAR							m_szDllName[MAX_PATH];				//组件名字
																		//内核变量
public:
	HINSTANCE						m_hDllInstance;						//DLL 句柄
	T *								m_pIDllEntry;						//模块接口

public:
	//构造函数
	DllHelper(DWORD dwVersion);
	DllHelper(DWORD dwVersion, LPCTSTR pszModuleDll, LPCSTR pszCreateProc);

	//析构函数
	virtual ~DllHelper();

public:
	//创建函数
	bool OpenDll();

	//释放组件
	bool CloseDll();

public:
	//创建信息
	void SetModuleCreateInfo(LPCTSTR pszModuleDllName, LPCSTR pszCreateProc);

public:
	//指针重载
	inline T * operator->() const;
	//获取接口
	inline T * GetInterface() const;
};

//构造函数
template<typename T>
DllHelper<T>::DllHelper(DWORD dwVersion) : m_dwVersion(dwVersion)
{
	//内核信息
	m_hDllInstance = NULL;
	m_pIDllEntry = NULL;

	//组件属性
	ZeroMem(m_szCreateProc);
	ZeroMem(m_szDllName);

	return;
}

//构造函数
template<typename T>
DllHelper<T>::DllHelper(DWORD dwVersion, LPCTSTR pszModuleDll, LPCSTR pszCreateProc) : m_dwVersion(dwVersion)
{
	//内核信息
	m_hDllInstance = NULL;
	m_pIDllEntry = NULL;

	//组件属性
	lstrcpynA(m_szCreateProc, pszCreateProc, CountArray(m_szCreateProc));
	lstrcpyn(m_szDllName, pszModuleDll, CountArray(m_szDllName));

	return;
}

//析构函数
template<typename T>
DllHelper<T>::~DllHelper()
{
	CloseDll();
}

template<typename T>
bool DllHelper<T>::OpenDll()
{
	//释放组件
	CloseDll();

	//效验参数
	assert(m_szCreateProc[0] != 0);
	assert(m_szDllName[0] != 0);

	//加载模块
	m_hDllInstance = LoadLibrary(m_szDllName);
	if (m_hDllInstance == NULL)
	{
		return false;
	}

	//寻找函数
	FPCreateProc * CreateProc = (FPCreateProc *)GetProcAddress(m_hDllInstance, m_szCreateProc);
	if (CreateProc == NULL)
	{
		return false;
	}

	//创建组件
	m_pIDllEntry = (T *)CreateProc(m_dwVersion);
	if (m_pIDllEntry == NULL)
	{
		return false;
	}

	return true;
}


//释放组件
template <typename T>
bool DllHelper<T>::CloseDll()
{
	//设置变量

	//销毁对象
	if (m_pIDllEntry != NULL)
	{
		m_pIDllEntry->Release();
		m_pIDllEntry = NULL;
	}

	//释放 DLL
	if (m_hDllInstance != NULL)
	{
		FreeLibrary(m_hDllInstance);
		m_hDllInstance = NULL;
	}

	return true;
}

//创建信息
template <typename T>
void DllHelper<T>::SetModuleCreateInfo(LPCTSTR pszModuleDllName, LPCSTR pszCreateProc)
{
	//设置信息
	lstrcpyn(m_szDllName, pszModuleDllName, CountArray(m_szDllName));
	lstrcpynA(m_szCreateProc, pszCreateProc, CountArray(m_szCreateProc));

	return;
}

//指针重载
template <typename T>
inline T * DllHelper<T>::operator->() const
{
	return GetInterface();
}

//获取接口
template <typename T>
inline T * DllHelper<T>::GetInterface() const
{
	return m_pIDllEntry;
}

//组件辅助类宏
#define DECLARE_MODULE_DYNAMIC(OBJECT)																		\
class C##OBJECT##Helper : public DllHelper<I##OBJECT>														\
{																											\
public:																										\
	C##OBJECT##Helper() : DllHelper<I##OBJECT>(IID_I##OBJECT) { }											\
};

//组件辅助类宏
#define DECLARE_MODULE_HELPER(OBJECT,MODULE_DLL_NAME,CREATE_FUNCTION_NAME)									\
class C##OBJECT##Helper : public DllHelper<I##OBJECT>														\
{																											\
public:																										\
	C##OBJECT##Helper() : DllHelper<I##OBJECT>(IID_I##OBJECT,MODULE_DLL_NAME,CREATE_FUNCTION_NAME) { }		\
};