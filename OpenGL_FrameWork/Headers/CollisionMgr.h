#pragma once
class CObj;
class CCollisionMgr
{
	_DECLARE_SINGLETON(CCollisionMgr)
private:
	CCollisionMgr();
	~CCollisionMgr();
public:
	bool		Check_Collision(vector<CObj*> pTarget, vector<CObj*> pBulletLst);
};

