#include "pch.h"

#include "Buffer_TankCol.h"
#include "Transform.h"
#include "Shader.h"
#include "Terrain.h"
#include "Buffer_Terrain.h"
CMonster::CMonster()
{
}


CMonster::~CMonster()
{
	Release();
}

HRESULT CMonster::Init()
{
	m_pBuffer = new CBuffer_TankCol;
	m_pBuffer->Init();
	m_pTransform = new CTransform;

	m_pTransform->SetUp_Speed(0.1f, radians(0.1f));
	vec3 vPos = { 0.f,0.f,0.f };
	m_pTransform->Set_StateInfo(STATE_POSITION, &vPos);

	m_pTransform->Scaling(vec3(0.5f, 0.5f, 0.5f));
	return S_OK;
}
HRESULT CMonster::Init(vec3 vPos, vec3 vSize, vec3 vColor)
{
	m_pBuffer = new CBuffer_TankCol;
	m_pBuffer->Init();
	m_pTransform = new CTransform;

	m_pTransform->SetUp_Speed(0.1f, radians(0.1f));
	dynamic_cast<CBuffer_TankCol*>(m_pBuffer)->SetColor(vColor);
	m_pTransform->Scaling(vSize);
	m_pTransform->Set_StateInfo(STATE_POSITION, &vPos);

	CObj* pObj = CAbstractFactory<CCollider>::CreateObj(*this->m_pTransform->Get_StateInfo(STATE_POSITION), vec3(2.f, 2.f, 2.f), vec3(), this);
	if (nullptr == pObj)
		return E_FAIL;
	CObjectMgr::GetInstance()->Add_Object(pObj, OBJECT_COLLIDER);
	return S_OK;
}

int CMonster::Update(_float fTimeDelta)
{
	CBuffer_Terrain* pTerrain = (CBuffer_Terrain*)CObjectMgr::GetInstance()->GetObject_List(OBJECT_TERRAIN)[0]->GetBuffer();
	_float fY = pTerrain->Compute_HeightOnTerrain(this->GetTransform());

	_float fX = m_pTransform->Get_StateInfo(STATE_POSITION)->x;
	_float fZ = m_pTransform->Get_StateInfo(STATE_POSITION)->z;
	vec3 vPos = vec3(fX, fY+0.5f, fZ);

	m_pTransform->Set_StateInfo(STATE_POSITION, &vPos);
	return 0;
}

void CMonster::Render()
{
	_uint WorldLocation = glGetUniformLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Normal")->GetShaderNum(), "matWorld");
	glUniformMatrix4fv(WorldLocation, 1, GL_FALSE, value_ptr(m_pTransform->GetMatrix()));

	_uint ViewLocation = glGetUniformLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Normal")->GetShaderNum(), "matView");
	glUniformMatrix4fv(ViewLocation, 1, GL_FALSE, &CCameraMgr::GetInstance()->Get_ViewMatrix()[0][0]);

	_uint ProjLocation = glGetUniformLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Normal")->GetShaderNum(), "matProj");
	glUniformMatrix4fv(ProjLocation, 1, GL_FALSE, &CCameraMgr::GetInstance()->Get_ProjMatrix()[0][0]);

	_uint	LigtPosLocation = glGetUniformLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Normal")->GetShaderNum(), "vLightPos");
	glUniform3f(LigtPosLocation, 0.f, 2.f, 0.f);
	_uint	LightColorLocation = glGetUniformLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Normal")->GetShaderNum(), "vLightColor");
	glUniform3f(LightColorLocation, 1.f, 1.f, 1.f);

	m_pBuffer->Render();
}

void CMonster::Release()
{
	SafeDelete(m_pBuffer);
	SafeDelete(m_pTransform);
}

