#include "pch.h"
#include "..\Headers\Food.h"
#include "Light.h"
#include "Transform.h"
#include "Buffer_FoodCol.h"
#include "Shader.h"
#include "Buffer_Terrain.h"

CFood::CFood()
{
}


CFood::~CFood()
{
	Release();
}

HRESULT CFood::Init()
{
	isDie = false;
	return S_OK;
}
HRESULT CFood::Init(vec3 vPos, vec3 vSize, vec3 vColor)
{
	m_pBuffer = new CBuffer_FoodCol;
	m_pBuffer->Init();
	m_pTransform = new CTransform;

	m_pTransform->SetUp_Speed(0.0f, radians(0.0f));
	m_pTransform->Scaling(vSize);
	m_pTransform->Set_StateInfo(STATE_POSITION, &vPos);
	//dynamic_cast<cbuffer_food*>(m_pBuffer)->SetColor(vColor);	//주석 풀면 오류남

	CBuffer_Terrain* pTerrain = (CBuffer_Terrain*)CObjectMgr::GetInstance()->GetObject_List(OBJECT_TERRAIN)[0]->GetBuffer();
	CTransform* tempTransform = new CTransform;
	tempTransform->Set_StateInfo(STATE_POSITION, &vPos);
	_float fY = pTerrain->Compute_HeightOnTerrain(this->GetTransform());

	if (fY != 19.5f)
		return S_FALSE;

	fY += 1.f;

	vPos.y = fY;
	m_pTransform->Set_StateInfo(STATE_POSITION, &vPos);

	//m_pTransform->SetUp_RotationY(radians(90.f));

	isDie = false;

	return S_OK;
}

int CFood::Update(_float fTimeDelta)
{


	return 0;
}

void CFood::Render()
{
	if (isDie)
		return;

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

void CFood::Die()
{
	isDie = true;

	PlaySound(TEXT(FOOD_SOUND_FILE), NULL, SND_ASYNC);
}

bool CFood::IsDie()
{
	return isDie;
}

void CFood::Release()
{
	SafeDelete(m_pBuffer);
	SafeDelete(m_pTransform);
}