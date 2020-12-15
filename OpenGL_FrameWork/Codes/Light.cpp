#include "pch.h"
#include "..\Headers\Light.h"
#include "Shader.h"
#include "Transform.h"

CLight::CLight()
{
}


CLight::~CLight()
{
	Release();
}

HRESULT CLight::Init()
{
	return E_NOTIMPL;
}

HRESULT CLight::Init(vec3 vLightPos, vec3 vLightColor, string strLightName)
{
	m_strLightName = strLightName;

	m_pTransform = new CTransform;
	m_pTransform->Set_StateInfo(STATE_POSITION, &vLightPos);
	m_pTransform->SetUp_Speed(0.1f, radians(1.f));
	m_vLightColor = vLightColor;

	m_pTransform->Scaling(vec3(0.25f, 0.25f, 0.25f));
	return S_OK;
}

int CLight::Update(_float fTimeDelta)
{
	return 0;
}

void CLight::Render()
{
}

void CLight::Release()
{
	SafeDelete(m_pTransform);
}
