#pragma once
#include "Obj.h"
class CTri :
	public CObj
{
public:
	CTri();
	virtual ~CTri();
public:
	virtual HRESULT Init() override;
	virtual int Update(_float fTimeDelta) override;
	virtual void Render() override;
	virtual void Release() override;
public:
	vec3		GetOriginPos() { return m_vOriginPos; }
private:
	vec3 m_vOriginPos = {};
};

