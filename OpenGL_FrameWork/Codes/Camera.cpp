#include "pch.h"
#include "..\Headers\Camera.h"
#include "Transform.h"

CCamera::CCamera()
{
}


CCamera::~CCamera()
{
}


HRESULT CCamera::SetUp_CameraProjDesc(const CAMERADESC & CameraDesc, const PROJDESC & ProjDesc)
{
	m_tCameraDesc = CameraDesc;
	m_tProjDesc = ProjDesc;
	SetUp_ViewProjMatrieces();
	return S_OK;
}

void CCamera::Invalidate_ViewProjMatrix()
{
	//m_matView = lookAt(m_tCameraDesc.vEye, m_tCameraDesc.vAt, m_tCameraDesc.vAxisY);
	m_matView = m_pTransform->Get_Matrix_Inverse();
	CCameraMgr::GetInstance()->Set_ViewMatrix(m_matView);
	CCameraMgr::GetInstance()->Set_ProjMatrix(m_matProj);
}

HRESULT CCamera::SetUp_ViewProjMatrieces()
{
	//n
	vec3		vLook;
	//vLook = m_tCameraDesc.vAt - m_tCameraDesc.vEye;
	vLook = m_tCameraDesc.vEye - m_tCameraDesc.vAt;
	vLook = normalize(vLook);

	//u
	vec3		vRight;
	vRight = cross(m_tCameraDesc.vAxisY, vLook);
	vRight = normalize(vRight);


	//v
	vec3		vUp;
	vUp = cross(vLook, vRight);
	vUp = normalize(vUp);

	m_pTransform->Set_StateInfo(STATE_RIGHT, &vRight);
	m_pTransform->Set_StateInfo(STATE_UP, &vUp);
	m_pTransform->Set_StateInfo(STATE_LOOK, &vLook);
	m_pTransform->Set_StateInfo(STATE_POSITION, &m_tCameraDesc.vEye);

	m_matProj = perspective(m_tProjDesc.fFovY, m_tProjDesc.fAspect, m_tProjDesc.fNear, m_tProjDesc.fFar);

	Invalidate_ViewProjMatrix();

	return NOERROR;
}
