#pragma once
#include "Camera.h"
class CCamera_Player :
	public CCamera
{
public:
	CCamera_Player();
	virtual ~CCamera_Player();
public:
	virtual HRESULT Init() override;
	virtual int Update(_float fTimeDelta) override;
	virtual void Render() override;
	virtual void Release() override;

};

