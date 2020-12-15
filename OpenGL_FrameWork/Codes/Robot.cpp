#include "pch.h"
#include "..\Headers\Robot.h"
#include "Light.h"
#include "Transform.h"
#include "Buffer_RobotNor.h"
#include "Shader.h"
#include "Terrain.h"
#include "Buffer_Terrain.h"
CRobot::CRobot()
{
}


CRobot::~CRobot()
{
	Release();
}

HRESULT CRobot::Init()
{
	return S_OK;
}

HRESULT CRobot::Init(vec3 vPos, vec3 vSize, vec3 vColor)
{
	m_pBuffer = new CBuffer_RobotNor;
	m_pBuffer->Init();
	m_pTransform = new CTransform;

	m_pTransform->SetUp_Speed(0.1f, radians(0.1f));
	m_pTransform->Scaling(vSize);
	m_pTransform->Set_StateInfo(STATE_POSITION, &vPos);




	m_pTransform->SetUp_RotationY(radians(90.f));

	srand(unsigned(time(NULL)));
	int		iRandX = rand()%50+1;
	int		iRandZ = rand()%50+1;

	m_vDest = {(float)iRandX, m_pTransform->Get_StateInfo(STATE_POSITION)->y, (float)iRandZ};
	//m_vDest = {100, 1.f, 100};
	

	return S_OK;
}

int CRobot::Update(_float fTimeDelta)
{
	m_vTempPos = *m_pTransform->Get_StateInfo(STATE_POSITION);
	m_vTempPos.y = 1.f;
	float iLength = length(m_vDest - m_vTempPos);
	_float fCameraLength = 0.f;
	float fDot = 0.f;

	if (IsCam == false)
	{
		m_vCameraPos = *CObjectMgr::GetInstance()->GetObject_List(OBJECT_CAMERA)[0]->GetTransform()->Get_StateInfo(STATE_POSITION);
		m_vCameraPos.y = 1.f;

		vec3 vCameraPosbyThisPos = m_vCameraPos - *m_pTransform->Get_StateInfo(STATE_POSITION);
		fCameraLength = length(vCameraPosbyThisPos);
		vCameraPosbyThisPos = normalize(vCameraPosbyThisPos);
		vec3 vTempPos = *m_pTransform->Get_StateInfo(STATE_POSITION);
		vTempPos.y = 1.f;
		vTempPos = normalize(vTempPos);
		fDot = dot(vTempPos, vCameraPosbyThisPos);
	}
	else
	{
		m_vCameraPos = *CObjectMgr::GetInstance()->GetObject_List(OBJECT_PLAYER)[0]->GetTransform()->Get_StateInfo(STATE_POSITION);
		m_vCameraPos.y = 1.f;

		vec3 vCameraPosbyThisPos = m_vCameraPos - *m_pTransform->Get_StateInfo(STATE_POSITION);
		fCameraLength = length(vCameraPosbyThisPos);
		vCameraPosbyThisPos = normalize(vCameraPosbyThisPos);
		vec3 vTempPos = *m_pTransform->Get_StateInfo(STATE_POSITION);
		vTempPos.y = 1.f;
		vTempPos = normalize(vTempPos);
		fDot = dot(vTempPos, vCameraPosbyThisPos);
	}



	if (fCameraLength <= 20.f)
	{
		Compute_RULC();
		if (fabs(fDot) >=0.5f && fabs(fDot) <= (1.5f))
		{
			m_pTransform->Go_ToTarget(&m_vCameraPos);
		}
	}
	else
	{
		m_pTransform->Go_ToTarget(&m_vDest);
		Compute_RUL();
		if (iLength <= 3.f)
		{
			srand(unsigned(time(NULL)));
			int		iRandX = rand() % 50 + 1;
			int		iRandZ = rand() % 50 + 1;

			m_vDest = { (float)iRandX, 1.f, (float)iRandZ };
		}
	}


	CBuffer_Terrain* pTerrain = (CBuffer_Terrain*)CObjectMgr::GetInstance()->GetObject_List(OBJECT_TERRAIN)[0]->GetBuffer();
	_float fY = pTerrain->Compute_HeightOnTerrain(this->GetTransform());
	fY += 0.5f;

	_float fX = m_pTransform->Get_StateInfo(STATE_POSITION)->x;
	_float fZ = m_pTransform->Get_StateInfo(STATE_POSITION)->z;
	vec3 vPos = vec3(fX, fY, fZ);

	m_pTransform->Set_StateInfo(STATE_POSITION, &vPos);

	return 0;
}

void CRobot::Render()
{
	_uint WorldLocation = glGetUniformLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Normal")->GetShaderNum(), "matWorld");
	glUniformMatrix4fv(WorldLocation, 1, GL_FALSE, value_ptr(m_pTransform->GetMatrix()));

	_uint ViewLocation = glGetUniformLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Normal")->GetShaderNum(), "matView");
	glUniformMatrix4fv(ViewLocation, 1, GL_FALSE, &CCameraMgr::GetInstance()->Get_ViewMatrix()[0][0]);

	_uint ProjLocation = glGetUniformLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Normal")->GetShaderNum(), "matProj");
	glUniformMatrix4fv(ProjLocation, 1, GL_FALSE, &CCameraMgr::GetInstance()->Get_ProjMatrix()[0][0]);

	CObj* pObj = CObjectMgr::GetInstance()->Find_Light("Light_Default");
	if (nullptr != pObj)
	{
		_uint	LigtPosLocation = glGetUniformLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Normal")->GetShaderNum(), "vLightPos");
		glUniform3f(LigtPosLocation,
			pObj->GetTransform()->Get_StateInfo(STATE_POSITION)->x,
			pObj->GetTransform()->Get_StateInfo(STATE_POSITION)->y,
			pObj->GetTransform()->Get_StateInfo(STATE_POSITION)->z);

		_uint	LightColorLocation = glGetUniformLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Normal")->GetShaderNum(), "vLightColor");
		glUniform3f(LightColorLocation,
			dynamic_cast<CLight*>(pObj)->GetLightColor().x,
			dynamic_cast<CLight*>(pObj)->GetLightColor().y,
			dynamic_cast<CLight*>(pObj)->GetLightColor().z);
	}

	m_pBuffer->Render();
}

void CRobot::Release()
{
	SafeDelete(m_pBuffer);
	SafeDelete(m_pTransform);
}

void CRobot::Compute_RUL()
{
	vec3 vLook = m_vDest - m_vTempPos;
	vLook = normalize(vLook);

	vec3 vUp = vec3(0.f,1.f,0.f);
	vec3 vRight = cross(vUp, vLook);

	m_pTransform->Set_StateInfo(STATE_LOOK, &vLook);
	m_pTransform->Set_StateInfo(STATE_RIGHT, &vRight);
	m_pTransform->Set_StateInfo(STATE_UP, &vUp);
}

void CRobot::Compute_RULC()
{
	vec3 vLook = m_vCameraPos - m_vTempPos;
	vLook = normalize(vLook);

	vec3 vUp = vec3(0.f, 1.f, 0.f);
	vec3 vRight = cross(vUp, vLook);

	m_pTransform->Set_StateInfo(STATE_LOOK, &vLook);
	m_pTransform->Set_StateInfo(STATE_RIGHT, &vRight);
	m_pTransform->Set_StateInfo(STATE_UP, &vUp);
}

void CRobot::Follow_Object()
{
}
