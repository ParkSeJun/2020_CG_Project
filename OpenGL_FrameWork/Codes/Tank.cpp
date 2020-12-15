#include "pch.h"
#include "..\Headers\Tank.h"
#include "Buffer_TankCol.h"
#include "Shader.h"
#include "Transform.h"
#include "Cube.h"
#include "Terrain.h"
#include "Buffer_Terrain.h"

CTank::CTank()
{
}


CTank::~CTank()
{
	Release();
}

HRESULT CTank::Init()
{
	m_pBuffer = new CBuffer_TankCol;
	m_pBuffer->Init();
	m_pTransform = new CTransform;

	m_pTransform->SetUp_Speed(0.1f, radians(0.1f));
	vec3 vPos = {0.f,0.f,0.f};
	m_pTransform->Set_StateInfo(STATE_POSITION, &vPos);

	m_pTransform->Scaling(vec3(0.5f, 0.5f, 0.5f));
	return S_OK;
}

HRESULT CTank::Init(vec3 vPos, vec3 vSize, vec3 vColor)
{
	m_pBuffer = new CBuffer_TankCol; 
	m_pBuffer->Init();
	m_pTransform = new CTransform;

	m_pTransform->SetUp_Speed(0.1f, radians(90.f));

	return S_OK;
}

int CTank::Update(_float fTimeDelta)
{
	if (CKeyMgr::GetInstance()->KeyPressing(KEY_LBUTTON))
		m_pTransform->RotationY(10.f);
	else if (CKeyMgr::GetInstance()->KeyPressing(KEY_RBUTTON))
		m_pTransform->RotationY(-10.f);

	if (CKeyMgr::GetInstance()->KeyPressing(KEY_SPACE))
		m_pTransform->Go_Straight();

	CBuffer_Terrain* pTerrain = (CBuffer_Terrain*)CObjectMgr::GetInstance()->GetObject_List(OBJECT_TERRAIN)[0]->GetBuffer();
	_float fY =pTerrain->Compute_HeightOnTerrain(this->GetTransform());

	_float fX = m_pTransform->Get_StateInfo(STATE_POSITION)->x;
	_float fZ = m_pTransform->Get_StateInfo(STATE_POSITION)->z;
	vec3 vPos = vec3(fX, fY, fZ);
	
	m_pTransform->Set_StateInfo(STATE_POSITION, &vPos);
	return 0;
}

void CTank::Render()
{
	_uint WorldLocation = glGetUniformLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Default")->GetShaderNum(), "matWorld");
	glUniformMatrix4fv(WorldLocation, 1, GL_FALSE, value_ptr(m_pTransform->GetMatrix()));

	_uint ViewLocation = glGetUniformLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Default")->GetShaderNum(), "matView");
	glUniformMatrix4fv(ViewLocation, 1, GL_FALSE, &CCameraMgr::GetInstance()->Get_ViewMatrix()[0][0]);

	_uint ProjLocation = glGetUniformLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Default")->GetShaderNum(), "matProj");
	glUniformMatrix4fv(ProjLocation, 1, GL_FALSE, &CCameraMgr::GetInstance()->Get_ProjMatrix()[0][0]);
	m_pBuffer->Render();
}

void CTank::Release()
{
	SafeDelete(m_pBuffer);
	SafeDelete(m_pTransform);
}
