#include "pch.h"
#include "MainApp.h"
#include "Shader.h"
#include "Rect.h"
#include "Cube.h"
#include "Camera_Debug.h"
#include "Obj.h"
#include "Terrain.h"

#include "Buffer_TankCol.h"
#include "Player.h"

#include "Light.h"
#include "Robot.h"


CMainApp::CMainApp()
{
}


CMainApp::~CMainApp()
{
	Release();
}

HRESULT CMainApp::Init()
{
	HWND hWnd = GetActiveWindow();
	HINSTANCE hInstC = GetModuleHandle(0);

	if (FAILED(CShaderMgr::GetInstance()->AddShader(L"Shader_Default", "../ShaderFiles/VertexShader.txt", "../ShaderFiles/FragmentShader.txt")))
		return E_FAIL;
	if (FAILED(CShaderMgr::GetInstance()->AddShader(L"Shader_Texture", "../ShaderFiles/Vertex_Shader_Texture.txt", "../ShaderFiles/Fragment_Shader_Texture.txt")))
		return E_FAIL;
	if (FAILED(CShaderMgr::GetInstance()->AddShader(L"Shader_Normal", "../ShaderFiles/Vertex_Shader_Normal.txt", "../ShaderFiles/Fragment_Shader_Normal.txt")))
		return E_FAIL;
	if (FAILED(CInputMgr::GetInstance()->Ready_Input_Device(hInstC, hWnd)))
		return E_FAIL;

	if (FAILED(SetUp_Texture_Filltering()))
		return E_FAIL;


	if (CCameraMgr::GetInstance()->SetUp_CameraOption(CAMERA_QUARTAR))
		return E_FAIL;
	if (FAILED(Create_Object()))
		return E_FAIL;


	return S_OK;
}

void CMainApp::Update(_float fTimeDelta)
{
	srand(unsigned(time(NULL)));

	if (CKeyMgr::GetInstance()->KeyDown(KEY_1))
		CCameraMgr::GetInstance()->Swap_Camera(CAMERA_DEBUG);
	else if (CKeyMgr::GetInstance()->KeyDown(KEY_2))
		CCameraMgr::GetInstance()->Swap_Camera(CAMERA_QUARTAR);
	else if (CKeyMgr::GetInstance()->KeyDown(KEY_3))
		CCameraMgr::GetInstance()->Swap_Camera(CAMERA_DEBUG);
	

	CInputMgr::GetInstance()->SetUp_InputState();
	CKeyMgr::GetInstance()->Update();
	CObjectMgr::GetInstance()->Update(fTimeDelta);
}

void CMainApp::Render()
{
	CObjectMgr::GetInstance()->Render();
}

void CMainApp::Release()
{
	CObjectMgr::GetInstance()->DestroyInstance();
	CShaderMgr::GetInstance()->DestroyInstance();
	CKeyMgr::GetInstance()->DestroyInstance();
	CCameraMgr::GetInstance()->DestroyInstance();
	CInputMgr::GetInstance()->DestroyInstance();
	CCollisionMgr::GetInstance()->DestroyInstance();
}

HRESULT CMainApp::SetUp_Texture_Filltering()
{
	return S_OK;
}

HRESULT CMainApp::Create_Object()
{
	CObj* pObj = CAbstractFactory<CLight>::CreateObj(vec3(100.f, 1000.f, 100.f), vec3(1.f, 1.f, 1.f), "Light_Default");
	if (nullptr == pObj)
		return E_FAIL;
	CObjectMgr::GetInstance()->Add_Object(pObj, OBJECT_LIGHT);

	pObj = CAbstractFactory<CPlayer>::CreateObj(vec3(65.f, 0.f, 9.3f), vec3(1.f, 1.f, 1.f), vec3(1.f, 0.f, 0.f));
	if (nullptr == pObj)
		return E_FAIL;
	CObjectMgr::GetInstance()->Add_Object(pObj, OBJECT_PLAYER);

	pObj = CAbstractFactory<CTerrain>::CreateObj();
	if (nullptr == pObj)
		return E_FAIL;
	CObjectMgr::GetInstance()->Add_Object(pObj, OBJECT_TERRAIN);

	for (int i = 0; i < 4; ++i)
	{
		pObj = CAbstractFactory<CRobot>::CreateObj(vec3(0+50*i, 0.f, 0 + 50 * i), vec3(1.f, 1.f, 1.f), vec3());
		if (nullptr == pObj)
			return E_FAIL;
		CObjectMgr::GetInstance()->Add_Object(pObj, OBJECT_MONSTER);
	}
	return S_OK;
}
