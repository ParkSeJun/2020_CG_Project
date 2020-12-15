#pragma once
#include "Obj.h"
class CFood :
	public CObj
{
public:
	CFood();
	virtual ~CFood();
	void Die();
	bool IsDie();
private:
	virtual HRESULT Init() override;
	virtual HRESULT Init(vec3 vPos, vec3 vSize, vec3 vColor)override;
	virtual int Update(_float fTimeDelta) override;
	virtual void Render() override;
	virtual void Release() override;

	bool isDie;
};

