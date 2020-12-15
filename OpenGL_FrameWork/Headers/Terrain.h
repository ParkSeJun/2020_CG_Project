#pragma once
#include "Obj.h"

class CTerrain :
	public CObj
{
public:
	CTerrain();
	virtual ~CTerrain();
public:
	virtual HRESULT Init() override;
	virtual int Update(_float fTimeDelta) override;
	virtual void Render() override;
	virtual void Release() override;
};

