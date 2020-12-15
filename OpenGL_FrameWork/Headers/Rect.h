#pragma once
#include "Obj.h"
class CRect :
	public CObj
{
public:
	CRect();
	virtual ~CRect();
public:
	virtual HRESULT Init() override;
	virtual HRESULT Init(vec3 vPos, vec3 vSize, vec3 vColor);
	virtual int Update(_float fTimeDelta) override;
	virtual void Render() override;
	virtual void Release() override;
};

