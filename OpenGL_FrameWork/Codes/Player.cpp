#include "pch.h"
#include "..\Headers\Player.h"
#include "Buffer_TankCol.h"
#include "Transform.h"
#include "Shader.h"
#include "Terrain.h"
#include "Buffer_Terrain.h"
#include "Bullet.h"
#include "Light.h"
CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
	Release();
}

HRESULT CPlayer::Init()
{
	m_pBuffer = new CBuffer_TankCol;
	m_pBuffer->Init();
	m_pTransform = new CTransform;

	m_pTransform->SetUp_Speed(0.1f, radians(0.1f));
	vec3 vPos = { 0.f,0.f,0.f };
	m_pTransform->Set_StateInfo(STATE_POSITION, &vPos);

	//m_pTransform->Scaling(vec3(0.5f, 0.5f, 0.5f));
	return S_OK;
}

HRESULT CPlayer::Init(vec3 vPos, vec3 vSize, vec3 vColor)
{
	m_pBuffer = new CBuffer_TankCol;
	m_pBuffer->Init();
	m_pTransform = new CTransform;

	m_pTransform->SetUp_Speed(0.3f, radians(0.25f));
	m_pTransform->Set_StateInfo(STATE_POSITION, &vPos);
	dynamic_cast<CBuffer_TankCol*>(m_pBuffer)->SetColor(vColor);
	m_pTransform->Scaling(vSize);




	m_pTransform->SetUp_RotationY(radians(180.f));

	return S_OK;
}

int CPlayer::Update(_float fTimeDelta)
{
	
	if (CKeyMgr::GetInstance()->KeyPressing(KEY_LBUTTON))
		m_pTransform->RotationY(10.f);
	else if (CKeyMgr::GetInstance()->KeyPressing(KEY_RBUTTON))
		m_pTransform->RotationY(-10.f);

	if (CKeyMgr::GetInstance()->KeyDown(KEY_SHIFT))
	{
		vec3 vPos = *m_pTransform->Get_StateInfo(STATE_POSITION);

		CObj* pObj = CAbstractFactory<CBullet>::CreateObj(vPos, vec3(1.f, 1.f, 1.f), vec3(1.f, 1.f, 0.f));
		if (nullptr == pObj)
			return 0;
		pObj->GetTransform()->SetMatrix(m_pTransform->GetMatrix());
		CObjectMgr::GetInstance()->Add_Object(pObj, OBJECT_BULLET);
	}

	CBuffer_Terrain* pTerrain = (CBuffer_Terrain*)CObjectMgr::GetInstance()->GetObject_List(OBJECT_TERRAIN)[0]->GetBuffer();

	if (CKeyMgr::GetInstance()->KeyPressing(KEY_SPACE))
	{
		vec3 forward = m_pTransform->Get_Straight();
		CTransform* tempTransform = new CTransform;
		tempTransform->Set_StateInfo(STATE_POSITION, &forward);
		_float forwardHeight = pTerrain->Compute_HeightOnTerrain(tempTransform);

		if (forwardHeight == 19.5f)
			m_pTransform->Go_Straight();
	}

	_float fY = pTerrain->Compute_HeightOnTerrain(this->GetTransform());


	vec3* curPos = this->GetTransform()->Get_StateInfo(STATE_POSITION);;
	char ch[256];
	sprintf(ch, "Player (%g, %g, %g), Terrain Y%g", curPos->x, curPos->y, curPos->z, fY);
	glutSetWindowTitle(ch);
	fY += 0.5f;

	_float fX = m_pTransform->Get_StateInfo(STATE_POSITION)->x;
	_float fZ = m_pTransform->Get_StateInfo(STATE_POSITION)->z;
	vec3 vPos = vec3(fX, fY, fZ);

	m_pTransform->Set_StateInfo(STATE_POSITION, &vPos);
	return 0;
}

void CPlayer::Render()
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

void CPlayer::Release()
{
	SafeDelete(m_pBuffer);
	SafeDelete(m_pTransform);
}
