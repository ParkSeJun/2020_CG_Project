#pragma once
class CObj;
class CObjectMgr
{
	_DECLARE_SINGLETON(CObjectMgr)
private:
	CObjectMgr();
	~CObjectMgr();
public:
	void			Add_Object(CObj* pObj, OBJECT eID);
	void			Update(_float fTimeDelta);
	void			Render();
	void			Release();
public:
	void			Group_Release(OBJECT eID);
	CObj*			Find_Light(string strLightName);
public:
	vector<CObj*>	GetObject_List(OBJECT eID) { return m_vecObj[eID]; }
public:
	vector<CObj*>	m_vecObj[OBJECT_END];
};

