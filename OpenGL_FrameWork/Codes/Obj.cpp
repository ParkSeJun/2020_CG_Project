#include "pch.h"
#include "..\Headers\Obj.h"


CObj::CObj()
{
}


CObj::~CObj()
{
}

HRESULT CObj::Init(vec3 vPos, vec3 vSize, vec3 vColor)
{
	return E_NOTIMPL;
}

HRESULT CObj::Init(vec3 vPos, vec3 vSize, vec3 vColor, CObj * pTarget)
{
	return E_NOTIMPL;
}

HRESULT CObj::Init(vec3 vLightPos, vec3 vLightColor, string strLightName)
{
	return E_NOTIMPL;
}

