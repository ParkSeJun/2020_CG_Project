#include "pch.h"
#include "..\Headers\CameraMgr.h"
#include "Camera_Debug.h"
#include "Camera_Player.h"
#include "Camera_Quartar.h"
_IMPLEMENT_SINGLETON(CCameraMgr)
CCameraMgr::CCameraMgr()
{
}


CCameraMgr::~CCameraMgr()
{
}

void CCameraMgr::Swap_Camera(CAMERA eCameraMode)
{
	m_eCameraMode = eCameraMode;
	if (m_eCameraMode != m_ePreCameraMode)
	{
		CObjectMgr::GetInstance()->Group_Release(OBJECT_CAMERA);
		switch (eCameraMode)
		{
			
		case CAMERA_DEBUG:
			IsCam = false;
			SetUp_CameraOption(eCameraMode);
			break;
		case CAMERA_QUARTAR:
			IsCam = true;
			SetUp_CameraOption(eCameraMode);
			break;
		case CAMERA_PLAYER:
			IsCam = false;
			SetUp_CameraOption(eCameraMode);
			break;
		}

		m_ePreCameraMode = eCameraMode;
	}
}

HRESULT CCameraMgr::SetUp_CameraOption(CAMERA eCameraMode)
{
	CAMERADESC		tCameraDesc;
	ZeroMemory(&tCameraDesc, sizeof(CAMERADESC));
	tCameraDesc.vEye = vec3(0.f, 0.f, 10.f);
	tCameraDesc.vAt = vec3(0.f, 0.f, 0.f);
	tCameraDesc.vAxisY = vec3(0.f, 1.f, 0.f);

	PROJDESC		tProjDesc;
	ZeroMemory(&tProjDesc, sizeof(tProjDesc));
	tProjDesc.fFovY = radians(60.f);
	tProjDesc.fAspect = _float(WINCX) / WINCY;
	tProjDesc.fNear = 0.2f;
	tProjDesc.fFar = 1000.f;

	if (eCameraMode == CAMERA_DEBUG)	// 1ÀÎÄª
	{
		CObj* pObj = CAbstractFactory<CCamera_Debug>::CreateObj();
		if (nullptr == pObj)
			return E_FAIL;
		CObjectMgr::GetInstance()->Add_Object(pObj, OBJECT_CAMERA);

		dynamic_cast<CCamera_Debug*>(pObj)->SetUp_CameraProjDesc(tCameraDesc, tProjDesc);
	}

	else if (eCameraMode == CAMERA_QUARTAR)	//Äõ
	{
		CObj* pObj = CAbstractFactory<CCamera_Player>::CreateObj();
		if (nullptr == pObj)
			return E_FAIL;
		CObjectMgr::GetInstance()->Add_Object(pObj, OBJECT_CAMERA);

		dynamic_cast<CCamera_Player*>(pObj)->SetUp_CameraProjDesc(tCameraDesc, tProjDesc);
	}
	 




	return S_OK;

}
