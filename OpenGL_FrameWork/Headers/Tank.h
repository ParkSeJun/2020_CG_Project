#pragma once
#include "Obj.h"
class CTank :
	public CObj
{
public:
	CTank();
	virtual ~CTank();
private:
	virtual HRESULT Init() PURE;
	virtual HRESULT Init(vec3 vPos, vec3 vSize, vec3 vColor)PURE;
	virtual int Update(_float fTimeDelta) PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

};

