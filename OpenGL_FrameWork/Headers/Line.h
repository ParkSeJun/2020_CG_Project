#pragma once
#include "Obj.h"
class CLine :
	public CObj
{
public:
	CLine();
	virtual ~CLine();
public:
	virtual HRESULT Init() override;
	virtual int Update(_float fTimeDelta) override;
	virtual void Render() override;
	virtual void Release() override;
private:
	_float		m_fAngle = 0.f;
	_int		m_iIdx = 0;
};

