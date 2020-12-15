#include "pch.h"
#include "..\Headers\Bullet.h"
#include "Buffer_CubeNor.h"
#include "Transform.h"
#include "Shader.h"
#include "Terrain.h"
#include "Buffer_Terrain.h"
CBullet::CBullet()
{
}


CBullet::~CBullet()
{
	Release();
}

HRESULT CBullet::Init()
{
	return S_OK;
}

HRESULT CBullet::Init(vec3 vPos, vec3 vSize, vec3 vColor)
{
	m_pBuffer = new CBuffer_CubeNor;
	m_pBuffer->Init();
	m_pTransform = new CTransform;

	m_pTransform->SetUp_Speed(1.f, radians(0.1f));
	//dynamic_cast<CBuffer_CubeNor*>(m_pBuffer)->SetColor(vColor);
	m_pTransform->Scaling(vSize);

	return S_OK;
}

int CBullet::Update(_float fTimeDelta)
{
	m_fTimeDelta += 0.01f;
	m_pTransform->Go_Straight();


	if (m_fTimeDelta >2.f)
	{
		m_fTimeDelta = 0.f;
		return 1;
	}
	return 0;
}

void CBullet::Render()
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

void CBullet::Release()
{
	SafeDelete(m_pBuffer);
	SafeDelete(m_pTransform);
}
