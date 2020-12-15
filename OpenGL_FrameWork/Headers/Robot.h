#pragma once
#include "Obj.h"
class CRobot :
	public CObj
{
public:
	CRobot();
	virtual ~CRobot();
public:
	virtual HRESULT Init() override;
	virtual HRESULT	Init(vec3 vPos, vec3 vSize, vec3 vColor)override;
	virtual int Update(_float fTimeDelta) override;
	virtual void Render() override;
	virtual void Release() override;
private:
	vec3		m_vDest = {};
	vec3		m_vTempPos = {};
	vec3		m_vCameraPos = {};
	vec3		m_vCameraDest = {};
private:
	void		Compute_RUL();
	void		Compute_RULC();
	void		Follow_Object();
};

