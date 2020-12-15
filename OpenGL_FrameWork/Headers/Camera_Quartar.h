#pragma once
#include "Camera.h"
class CCamera_Quartar :
	public CCamera
{
public:
	CCamera_Quartar();
	virtual ~CCamera_Quartar();
public:
	virtual HRESULT Init() override;
	virtual int Update(_float fTimeDelta) override;
	virtual void Render() override;
	virtual void Release() override;
private:
	void	Compute_RUL();
};

