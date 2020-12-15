#pragma once
#include "Tank.h"
class CPlayer :
	public CTank
{
public:
	CPlayer();
	virtual ~CPlayer();
public:
	virtual HRESULT Init() override;
	virtual HRESULT Init(vec3 vPos, vec3 vSize, vec3 vColor) override;
	virtual int Update(_float fTimeDelta) override;
	virtual void Render() override;
	virtual void Release() override;
private:
	_float			m_fShake = 0;
};

