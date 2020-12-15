#include "pch.h"
#include "..\Headers\Line.h"
#include "Shader.h"

CLine::CLine()
{
}


CLine::~CLine()
{
	Release();
}

HRESULT CLine::Init()
{
	return S_OK;
}



int CLine::Update(_float fTimeDelta)
{
	if (CKeyMgr::GetInstance()->KeyPressing(KEY_RBUTTON))
	{
		m_fAngle += 10.f;
	}
	return 0;
}

void CLine::Render()
{


}

void CLine::Release()
{
	SafeDelete(m_pBuffer);
}
