#include "pch.h"
#include "..\Headers\CollisionMgr.h"
#include "Transform.h"
#include "Obj.h"
_IMPLEMENT_SINGLETON(CCollisionMgr)
CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Check_Collision(vector<CObj*> pTargetLst, vector<CObj*> pBulletLst)
{
	_float fLenght = 0.f;

	for (auto& pTarget : pTargetLst)
	{
		for (auto& iter : pBulletLst)
		{
			fLenght = length(*pTarget->GetTransform()->Get_StateInfo(STATE_POSITION) - *iter->GetTransform()->Get_StateInfo(STATE_POSITION));

			if (fLenght <= 3.f)
			{
				vec3 vTempLook = normalize(*pTarget->GetTransform()->Get_StateInfo(STATE_LOOK));
				vec3 vTempBullet = normalize(*pTarget->GetTransform()->Get_StateInfo(STATE_POSITION) - *iter->GetTransform()->Get_StateInfo(STATE_POSITION));

				_float fDot = dot(vTempBullet, -vTempLook);

				if ((fDot < 0.5f && fDot > -0.5f))
				{
					iter->GetTransform()->SetUp_RotationY(fDot);
				}
			}
		}
	}
}
