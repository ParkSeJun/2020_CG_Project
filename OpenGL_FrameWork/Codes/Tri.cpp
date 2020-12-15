#include "pch.h"
#include "..\Headers\Tri.h"
#include "Shader.h"
#include "Transform.h"

CTri::CTri()
{
}


CTri::~CTri()
{
	Release();
}

HRESULT CTri::Init()
{

	return S_OK;
}

int CTri::Update(_float fTimeDelta)
{
	
	return 0;
}

void CTri::Render()
{


}

void CTri::Release()
{
	SafeDelete(m_pBuffer);
	SafeDelete(m_pTransform);
}
