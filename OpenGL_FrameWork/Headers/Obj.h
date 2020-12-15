#pragma once
class CBuffer;
class CTransform;
class CObj
{
public:
	CObj();
	virtual ~CObj();
public:
	virtual HRESULT	Init()PURE;
	virtual HRESULT Init(vec3 vPos, vec3 vSize, vec3 vColor);
	virtual HRESULT	Init(vec3 vPos, vec3 vSize, vec3 vColor, CObj* pTarget);
	virtual HRESULT	Init(vec3 vLightPos, vec3 vLightColor, string strLightName);
	virtual	int		Update(_float fTimeDelta)PURE;
	virtual void	Render()PURE;
	virtual void	Release()PURE;
public:
	CTransform*		GetTransform() { return m_pTransform; }
	CBuffer*		GetBuffer() { return m_pBuffer; }
	_bool&			GetIsPlayer() { return m_IsPlayer; }
	string			GetLightName() { return m_strLightName; }
protected:
	CBuffer*		m_pBuffer = nullptr;
	CTransform*		m_pTransform = nullptr;
protected:
	_float			m_fTimeDelta = 0.f;
	string			m_strLightName = "";	
	_bool			m_IsPlayer = false;
	_bool			m_IsTeam = FALSE;
};

