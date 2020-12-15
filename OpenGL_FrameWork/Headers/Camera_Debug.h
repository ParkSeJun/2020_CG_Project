#pragma once
#include "Camera.h"
class CCamera_Debug :
	public CCamera
{
public:
	CCamera_Debug();
	virtual ~CCamera_Debug();
public:
	virtual HRESULT Init() override;
	virtual int Update(_float fTimeDelta) override;
	virtual void Render() override;
	virtual void Release() override;
};

