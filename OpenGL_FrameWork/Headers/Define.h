#pragma once

#define WINCX 800
#define WINCY 600

#define PURE =0

#define PI 3.141592f

#define ERR_MSG(message)						\
MessageBox(g_hWnd, message, L"Error!", MB_OK);

#define NO_COPY(ClassName)						\
private:										\
	ClassName(const ClassName& _Obj);			\
	ClassName& operator=(const ClassName& _Obj);

#define _DECLARE_SINGLETON(ClassName)			\
		NO_COPY(ClassName)						\
public:											\
	static ClassName* GetInstance()				\
	{											\
		if(nullptr == m_pInstance)				\
			m_pInstance = new ClassName;		\
		return m_pInstance;						\
	}											\
	void DestroyInstance()						\
	{											\
		if(m_pInstance)							\
		{										\
			delete m_pInstance;					\
			m_pInstance = nullptr;				\
		}										\
	}											\
private:										\
	static ClassName*	m_pInstance;			

#define _IMPLEMENT_SINGLETON(ClassName)			\
ClassName* ClassName::m_pInstance = nullptr;

#define GET_INSTANCE(ClassName)					\
ClassName::GetInstance()