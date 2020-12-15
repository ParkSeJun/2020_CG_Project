#include "pch.h"
#include "..\Headers\Terrain.h"
#include "Buffer_Terrain.h"
#include "Shader.h"
#include "Transform.h"

CTerrain::CTerrain()
{
}


CTerrain::~CTerrain()
{
	Release();
}

HRESULT CTerrain::Init()
{
	m_pBuffer = new CBuffer_Terrain;
	m_pBuffer->Init(L"../Bin/Resource/Terrain/Map.bmp", 1.f);
	m_pTransform = new CTransform;

	//m_pTransform->Scaling(vec3(10.f, 10.f, 10.f));
	//vec3 vPos = vec3(0.f,-20.f,0.f);
	//m_pTransform->Set_StateInfo(STATE_POSITION, &vPos);

	return S_OK;
}

int CTerrain::Update(_float fTimeDelta)
{
	return 0;
}

void CTerrain::Render()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	_uint WorldLocation = glGetUniformLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Normal")->GetShaderNum(), "matWorld");
	glUniformMatrix4fv(WorldLocation, 1, GL_FALSE, value_ptr(m_pTransform->GetMatrix()));

	_uint ViewLocation = glGetUniformLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Normal")->GetShaderNum(), "matView");
	glUniformMatrix4fv(ViewLocation, 1, GL_FALSE, &CCameraMgr::GetInstance()->Get_ViewMatrix()[0][0]);

	_uint ProjLocation = glGetUniformLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Normal")->GetShaderNum(), "matProj");
	glUniformMatrix4fv(ProjLocation, 1, GL_FALSE, &CCameraMgr::GetInstance()->Get_ProjMatrix()[0][0]);
	_uint	LigtPosLocation = glGetUniformLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Normal")->GetShaderNum(), "vLightPos");
	glUniform3f(LigtPosLocation, 0.f, 5.f, 0.f);
	_uint	LightColorLocation = glGetUniformLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Normal")->GetShaderNum(), "vLightColor");
	glUniform3f(LightColorLocation, 1.f, 1.f, 1.f);
	m_pBuffer->Render();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void CTerrain::Release()
{
	SafeDelete(m_pTransform);
	SafeDelete(m_pBuffer);
}
