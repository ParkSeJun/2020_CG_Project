#include "pch.h"
#include "..\Headers\Rect.h"
#include "Buffer_RectCol.h"
#include "Shader.h"
#include "Transform.h"
CRect::CRect()
{
}


CRect::~CRect()
{
	Release();
}

HRESULT CRect::Init()
{
	m_pBuffer = new CBuffer_RectCol;
	m_pTransform = new CTransform;
	m_pBuffer->Init();

	m_pTransform->SetUp_RotationX(radians(90.f));
	vec3 vPos = {0.f,-0.5f,0.f};
	m_pTransform->Set_StateInfo(STATE_POSITION, &vPos);


	return S_OK;
}

HRESULT CRect::Init(vec3 vPos, vec3 vSize, vec3 vColor)
{
	m_pBuffer = new CBuffer_RectCol;
	m_pTransform = new CTransform;

	m_pBuffer->Init();

	m_pTransform->Scaling(vSize);
	m_pTransform->Set_StateInfo(STATE_POSITION, &vPos);
	dynamic_cast<CBuffer_RectCol*>(m_pBuffer)->SetColor(vColor);
	

	return S_OK;
}

int CRect::Update(_float fTimeDelta)
{

	return 0;
}

void CRect::Render()
{
	mat4 matView = CCameraMgr::GetInstance()->Get_ViewMatrix();
	mat4 matProj = CCameraMgr::GetInstance()->Get_ProjMatrix();
	_uint WorldLocation = glGetUniformLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Default")->GetShaderNum(), "matWorld");
	glUniformMatrix4fv(WorldLocation, 1, GL_FALSE, value_ptr(m_pTransform->GetMatrix()));

	_uint ViewLocation = glGetUniformLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Default")->GetShaderNum(), "matView");
	glUniformMatrix4fv(ViewLocation, 1, GL_FALSE, &matView[0][0]);

	_uint ProjLocation = glGetUniformLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Default")->GetShaderNum(), "matProj");
	glUniformMatrix4fv(ProjLocation, 1, GL_FALSE, &matProj[0][0]);
	m_pBuffer->Render();
}

void CRect::Release()
{
	SafeDelete(m_pBuffer);
	SafeDelete(m_pTransform);
}
