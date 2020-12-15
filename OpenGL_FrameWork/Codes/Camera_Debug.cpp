#include "pch.h"
#include "..\Headers\Camera_Debug.h"
#include "Shader.h"
#include "Transform.h"

CCamera_Debug::CCamera_Debug()
{
}


CCamera_Debug::~CCamera_Debug()
{
}

HRESULT CCamera_Debug::Init()
{
	m_matView = mat4(1.f);
 	m_matProj = mat4(1.f);

	ZeroMemory(&m_tProjDesc, sizeof(PROJDESC));
	ZeroMemory(&m_tCameraDesc, sizeof(CAMERADESC));

	m_pTransform = new CTransform;

	m_pTransform->SetUp_Speed(0.5f, radians(5.f));

	return S_OK;
}

int CCamera_Debug::Update(_float fTimeDelta)
{
	SetCursorPos(400, 300);

	if (CKeyMgr::GetInstance()->KeyPressing(KEY_UP))
		m_pTransform->Go_Straight();
	if (CKeyMgr::GetInstance()->KeyPressing(KEY_RIGHT))
		m_pTransform->Go_Right();
	if (CKeyMgr::GetInstance()->KeyPressing(KEY_DOWN))
		m_pTransform->BackWard();
	if (CKeyMgr::GetInstance()->KeyPressing(KEY_LEFT))
		m_pTransform->Go_Left();

	_long	MouseMove = 0;

	if (MouseMove = CInputMgr::GetInstance()->Get_DIMouseMove(DIM_X))
		m_pTransform->RotationY(-MouseMove*0.1f);

	if (MouseMove = CInputMgr::GetInstance()->Get_DIMouseMove(DIM_Y))
	{	
		vec3 Axis = *m_pTransform->Get_StateInfo(STATE_RIGHT);
		m_pTransform->Rotation_Axis(-(MouseMove) * 0.1f, &Axis);
	}


	if (CKeyMgr::GetInstance()->KeyPressing(KEY_RETURN))
		m_pTransform->RotationY(1);
	//if (CKeyMgr::GetInstance()->KeyPressing(KEY_R))
	//{
	//	mat4 mattemp = mat4(1.f);
	//	vec3 vAxis = vec3(0.f, 1.f, 0.f);
	//	m_pTransform->Rotaion_Rev(mattemp, &vAxis);
	//}
	vec3 vUp, vPos, vLook;
	vUp = *m_pTransform->Get_StateInfo(STATE_UP);
	vLook = *m_pTransform->Get_StateInfo(STATE_LOOK);
	vPos = *CObjectMgr::GetInstance()->GetObject_List(OBJECT_PLAYER)[0]->GetTransform()->Get_StateInfo(STATE_POSITION);


	Invalidate_ViewProjMatrix();
	return 0;
}

void CCamera_Debug::Render()
{
}

void CCamera_Debug::Release()
{
	SafeDelete(m_pTransform);
}
