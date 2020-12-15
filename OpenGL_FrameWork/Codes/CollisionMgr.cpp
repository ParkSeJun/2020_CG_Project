#include "pch.h"
#include "..\Headers\CollisionMgr.h"
#include "Transform.h"
#include "Obj.h"
#include "Food.h"
_IMPLEMENT_SINGLETON(CCollisionMgr)
CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

bool CCollisionMgr::Check_Collision(vector<CObj*> pTargetLst, vector<CObj*> pBulletLst)
{
	_float fLenght = 0.f;

	for (auto& pTarget : pTargetLst)
	{
		for (auto& iter : pBulletLst)
		{
			fLenght = length(*pTarget->GetTransform()->Get_StateInfo(STATE_POSITION) - *iter->GetTransform()->Get_StateInfo(STATE_POSITION));

			if (fLenght <= 1.5f)
			{
				vec3 center = vec3(63.f, 0.f, 63.f);
				pTarget->GetTransform()->Set_StateInfo(STATE_POSITION, &center);
				PlaySound(TEXT(RESTART_SOUND_FILE), NULL, SND_ASYNC);

				return true;
			}
		}
	}
}

bool IsFoodAllDie(vector<CObj*> pFoodLst)
{
	for (auto& iter : pFoodLst)
	{
		CFood* food = dynamic_cast<CFood*>(iter);
		if (!food->IsDie())
			return false;
	}
	return true;
}

bool CCollisionMgr::Check_Collision_Food(CObj* pPlayer, vector<CObj*> pFoodLst)
{
	_float fLenght = 0.f;

	for (auto& iter : pFoodLst)
	{
		CFood* food = dynamic_cast<CFood*>(iter);
		if (food->IsDie())
			continue;
		fLenght = length(*pPlayer->GetTransform()->Get_StateInfo(STATE_POSITION) - *iter->GetTransform()->Get_StateInfo(STATE_POSITION));

		if (fLenght <= 2.f)
		{
			food->Die();
			return IsFoodAllDie(pFoodLst);
		}
	}
	return false;
}
