#include "pch.h"
#include "..\Headers\InputMgr.h"

_IMPLEMENT_SINGLETON(CInputMgr)
CInputMgr::CInputMgr()
{
	
}


CInputMgr::~CInputMgr()
{
	m_pKeyBoard->Release();
	m_pMouse->Release();
	m_pSDK->Release();

}

HRESULT CInputMgr::Ready_Input_Device(HINSTANCE hInst, HWND hWnd)
{
	if (FAILED(DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pSDK, nullptr)))
		return E_FAIL;

	if (FAILED(Ready_KeyBoard(hWnd)))
		return E_FAIL;

	if (FAILED(Ready_Mouse(hWnd)))
		return E_FAIL;

	return NOERROR;
}

void CInputMgr::SetUp_InputState()
{
	if (nullptr == m_pKeyBoard)
		return;
	if (nullptr == m_pMouse)
		return;

	m_pKeyBoard->GetDeviceState(256, m_KeyState);

	m_pMouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_MouseState);
}

HRESULT CInputMgr::Ready_KeyBoard(HWND hWnd)
{
	if (FAILED(m_pSDK->CreateDevice(GUID_SysKeyboard, &m_pKeyBoard, nullptr)))
		return E_FAIL;
	if (FAILED(m_pKeyBoard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY)))
		return E_FAIL;
	if (FAILED(m_pKeyBoard->SetDataFormat(&c_dfDIKeyboard)))
		return E_FAIL;
	m_pKeyBoard->Acquire();

	return NOERROR;
}

HRESULT CInputMgr::Ready_Mouse(HWND hWnd)
{
	if (FAILED(m_pSDK->CreateDevice(GUID_SysMouse, &m_pMouse, nullptr)))
		return E_FAIL;
	if (FAILED(m_pMouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
		return E_FAIL;
	if (FAILED(m_pMouse->SetDataFormat(&c_dfDIMouse)))
		return E_FAIL;
	m_pMouse->Acquire();

	return NOERROR;
}
