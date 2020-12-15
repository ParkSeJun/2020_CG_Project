#pragma once
#include "Obj.h"
class CLight :
	public CObj
{
public:
	CLight();
	virtual ~CLight();
public:
	virtual HRESULT Init() override;
	virtual HRESULT	Init(vec3 vLightPos, vec3 vLightColor, string strLightName);
	virtual int Update(_float fTimeDelta) override;
	virtual void Render() override;
	virtual void Release() override;
public:
	vec3		GetLightColor() { return m_vLightColor; }
private:
	vec3		m_vLightColor = {};
};

