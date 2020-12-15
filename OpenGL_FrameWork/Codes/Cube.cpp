#include "pch.h"
#include "..\Headers\Cube.h"
#include "Buffer_CubeNor.h"
#include "Shader.h"
#include "Transform.h"

_float CCube::m_fTime = 0.f;
CCube::CCube()
{
}


CCube::~CCube()
{
	Release();
}

HRESULT CCube::Init()
{
	m_pBuffer = new CBuffer_CubeNor;
	m_pTransform = new CTransform;
	m_pBuffer->Init();

	vec3 vPos = vec3(0.f, 0.f, 0.f);
	m_pTransform->Set_StateInfo(STATE_POSITION, &vPos);
	vec3 vSize = vec3(1.f, 1.f, 1.f);
	m_pTransform->Scaling(vSize);
	m_pTransform->SetUp_Speed(1.f, radians(1.f));
	return S_OK;
}

HRESULT CCube::Init(vec3 vPos, vec3 vSize, vec3 vColor)
{
	m_pBuffer = new CBuffer_CubeNor;
	m_pTransform = new CTransform;
	m_pBuffer->Init();


	m_pTransform->Scaling(vSize);
	m_pTransform->Set_StateInfo(STATE_POSITION, &vPos);
	m_pTransform->SetUp_Speed(1.f, radians(0.1f));
	return S_OK;
}

int CCube::Update(_float fTimeDelta)
{
	m_pTransform->RotationY(1.f);
	return 0;
}

void CCube::Render()
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
	glUniform3f(LightColorLocation, 1.f, 0.f, 0.f);

	m_pBuffer->Render();
}

void CCube::Release()
{
	SafeDelete(m_pBuffer);
	SafeDelete(m_pTransform);
}

