#include "pch.h"
#include "..\Headers\Camera_Quartar.h"
#include "Shader.h"
#include "Transform.h"

CCamera_Quartar::CCamera_Quartar()
{
}


CCamera_Quartar::~CCamera_Quartar()
{
	Release();
}

HRESULT CCamera_Quartar::Init()
{
	m_matView = mat4(1.f);
	m_matProj = mat4(1.f);

	ZeroMemory(&m_tProjDesc, sizeof(PROJDESC));
	ZeroMemory(&m_tCameraDesc, sizeof(CAMERADESC));

	m_pTransform = new CTransform;

	m_pTransform->SetUp_Speed(0.5f, radians(5.f));
	m_pTransform->Set_StateInfo(STATE_POSITION, &vec3(0.f, 50.f, 0.f));


	return S_OK;
}

int CCamera_Quartar::Update(_float fTimeDelta)
{
	Compute_RUL();
	SetCursorPos(400, 300);
	
	if (CKeyMgr::GetInstance()->KeyPressing(KEY_UP))
		m_pTransform->Go_Up();
	if (CKeyMgr::GetInstance()->KeyPressing(KEY_RIGHT))
		m_pTransform->Go_Right();
	if (CKeyMgr::GetInstance()->KeyPressing(KEY_DOWN))
		m_pTransform->Go_Down();
	if (CKeyMgr::GetInstance()->KeyPressing(KEY_LEFT))
		m_pTransform->Go_Left();

	_long	MouseMove = 0;

	if (MouseMove = CInputMgr::GetInstance()->Get_DIMouseMove(DIM_X))
		m_pTransform->RotationY(-MouseMove * 0.1f);

	if (MouseMove = CInputMgr::GetInstance()->Get_DIMouseMove(DIM_Y))
	{
		vec3 Axis = *m_pTransform->Get_StateInfo(STATE_RIGHT);
		m_pTransform->Rotation_Axis(-(MouseMove) * 0.1f, &Axis);
	}

	Invalidate_ViewProjMatrix();
	return 0;
}

void CCamera_Quartar::Render()
{
}

void CCamera_Quartar::Release()
{
	SafeDelete(m_pTransform);
}

void CCamera_Quartar::Compute_RUL()
{
	vec3 vRight, vUp, vLook;
	
	vLook = vec3(0.f,1.f,0.f);
	vUp = vec3(0.f,0.f,-1.f);
	vRight = vec3(-1.f, 0.f,0.f);

	 
	m_pTransform->Set_StateInfo(STATE_RIGHT, &vRight);
	m_pTransform->Set_StateInfo(STATE_UP, &vUp);
	m_pTransform->Set_StateInfo(STATE_LOOK, &vLook);
}
