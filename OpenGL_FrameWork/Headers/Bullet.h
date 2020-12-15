#pragma once
#include "Obj.h"
class CBullet :
	public CObj
{
public:
	CBullet();
	virtual ~CBullet();
public:
	virtual HRESULT Init() override;
	virtual HRESULT Init(vec3 vPos, vec3 vSize, vec3 vColor)override;
	virtual int Update(_float fTimeDelta) override;
	virtual void Render() override;
	virtual void Release() override;
};

