#pragma once
#include "Obj.h"
class CCube :
	public CObj
{
public:
	CCube();
	virtual ~CCube();
public:
	virtual HRESULT Init() override;
	virtual HRESULT Init(vec3 vPos, vec3 vSize, vec3 vColor);
	virtual int Update(_float fTimeDelta) override;
	virtual void Render() override;
	virtual void Release() override;
private:
	static _float	m_fTime;
};

