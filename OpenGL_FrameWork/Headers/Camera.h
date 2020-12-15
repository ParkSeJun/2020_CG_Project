#pragma once
#include "Obj.h"
class CTransform;
class CCamera :
	public CObj
{
public:
	CCamera();
	virtual ~CCamera();
public:
	virtual HRESULT Init() PURE;
	virtual int Update(_float fTimeDelta) PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;
protected:
	mat4					m_matView=mat4(1.f);
	CAMERADESC				m_tCameraDesc;
protected:
	mat4					m_matProj = mat4(1.f);
	PROJDESC				m_tProjDesc;
public:
	HRESULT					SetUp_CameraProjDesc(const CAMERADESC& CameraDesc, const PROJDESC& ProjDesc);
	void					Invalidate_ViewProjMatrix();
private:
	HRESULT					SetUp_ViewProjMatrieces();
protected:
	POINT					m_ptMouse;
public:
	POINT			&GetPoint() { return m_ptMouse; }
};

