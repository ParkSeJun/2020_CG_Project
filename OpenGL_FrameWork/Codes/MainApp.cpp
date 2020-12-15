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
#include "Food.h"


CMainApp::CMainApp()
{
}


CMainApp::~CMainApp()
{
	Release();
}

HRESULT CMainApp::Init()
{
	srand(unsigned(time(NULL)));

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
	if (CKeyMgr::GetInstance()->KeyDown(KEY_1))
		CCameraMgr::GetInstance()->Swap_Camera(CAMERA_DEBUG);
	else if (CKeyMgr::GetInstance()->KeyDown(KEY_2))
		CCameraMgr::GetInstance()->Swap_Camera(CAMERA_QUARTAR);
	else if (CKeyMgr::GetInstance()->KeyDown(KEY_3))
		CCameraMgr::GetInstance()->Swap_Camera(CAMERA_DEBUG);
	else if (CKeyMgr::GetInstance()->KeyDown(KEY_R))
	{
		CObjectMgr::GetInstance()->Release();
		Create_Object();
		CCameraMgr::GetInstance()->SetUp_CameraOption(CAMERA_QUARTAR);
	}


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

float GetRandom(int min, int max)
{
	int r = (rand() % (max - min + 1)) + min;
	int r2 = rand() % 10;
	return (float)(r * 10 + r2) / 10.f;
}

HRESULT CMainApp::Create_Object()
{
	CObj* pObj = CAbstractFactory<CLight>::CreateObj(vec3(100.f, 1000.f, 100.f), vec3(1.f, 1.f, 1.f), "Light_Default");
	if (nullptr == pObj)
		return E_FAIL;
	CObjectMgr::GetInstance()->Add_Object(pObj, OBJECT_LIGHT);

	pObj = CAbstractFactory<CPlayer>::CreateObj(vec3(65.f, 0.f, 9.3f), vec3(0.1f, 0.1f, 0.1f), vec3(1.f, 1.f, 1.f));
	if (nullptr == pObj)
		return E_FAIL;
	CObjectMgr::GetInstance()->Add_Object(pObj, OBJECT_PLAYER);

	pObj = CAbstractFactory<CTerrain>::CreateObj();
	if (nullptr == pObj)
		return E_FAIL;
	CObjectMgr::GetInstance()->Add_Object(pObj, OBJECT_TERRAIN);

	const int robotSpawnCount = 10;
	float* randomPoints = new float[robotSpawnCount * 2];
	for (int i = 0; i < robotSpawnCount * 2; ++i)
	{
		if (i % 2 == 0)
			randomPoints[i] = GetRandom(48, 78);
		else
			randomPoints[i] = GetRandom(52, 76);
	}

	for (int i = 0; i < robotSpawnCount; ++i)
	{
		float rx = randomPoints[i * 2];
		float rz = randomPoints[i * 2 + 1];
		pObj = CAbstractFactory<CRobot>::CreateObj(vec3(rx, 0.f, rz), vec3(1.f, 1.f, 1.f), vec3());
		if (nullptr == pObj)
			return E_FAIL;
		CObjectMgr::GetInstance()->Add_Object(pObj, OBJECT_MONSTER);
	}

	for (int i = 4; i < 123; i += 12)
	{
		for (int j = 4; j < 123; j += 12)
		{
			pObj = CAbstractFactory<CFood>::CreateObj(vec3((float)j, 0.f, (float)i), vec3(1.f, 1.f, 1.f), vec3(1.f, 1.f, 0.f));
			if (nullptr == pObj)
				return E_FAIL;
			CObjectMgr::GetInstance()->Add_Object(pObj, OBJECT_FOOD);
		}
	}

	return S_OK;
}
