#include "pch.h"
#include "..\Headers\ObjectMgr.h"
#include "Transform.h"
#include "Obj.h"

_IMPLEMENT_SINGLETON(CObjectMgr)
CObjectMgr::CObjectMgr()
{
}

CObjectMgr::~CObjectMgr()
{
	Release();
}

void CObjectMgr::Add_Object(CObj * pObj, OBJECT eID)
{
	m_vecObj[eID].push_back(pObj);
}

void CObjectMgr::Update(_float fTimeDelta)
{
	for (int i = 0; i < OBJECT_END; ++i)
	{
		auto iter_begin = m_vecObj[i].begin();

		for (; iter_begin != m_vecObj[i].end();)
		{
			int iEvent = (*iter_begin)->Update(fTimeDelta);

			if (1 == iEvent)
			{
				SafeDelete(*iter_begin);
				iter_begin = m_vecObj[i].erase(iter_begin);
			}
			else
				++iter_begin;
		}
	}

	bool isPlayerDie = CCollisionMgr::GetInstance()->Check_Collision(m_vecObj[OBJECT_MONSTER], m_vecObj[OBJECT_PLAYER]);
	if (isPlayerDie)
	{
		vec3 startPos = vec3(65.f, 0.f, 9.3f);
		m_vecObj[OBJECT_PLAYER][0]->GetTransform()->SetUp_RotationY(radians(180.f));
		m_vecObj[OBJECT_PLAYER][0]->GetTransform()->Set_StateInfo(STATE_POSITION, &startPos);
	}

	bool isFoodAllDie = CCollisionMgr::GetInstance()->Check_Collision_Food(m_vecObj[OBJECT_PLAYER][0], m_vecObj[OBJECT_FOOD]);
	if (isFoodAllDie)
	{
		// TODO: 모든 음식을 다 먹었을 때 -> 맵 변경?
	}
}

void CObjectMgr::Render()
{
	for (int i = 0; i < OBJECT_END; ++i)
	{
		for (auto& pObject : m_vecObj[i])
			pObject->Render();
	}
}

void CObjectMgr::Release()
{
	for (int i = 0; i < OBJECT_END; ++i)
	{
		for_each(m_vecObj[i].begin(), m_vecObj[i].end(), SafeDelete<CObj*>);
		m_vecObj[i].clear();
	}
}

void CObjectMgr::Group_Release(OBJECT eID)
{
	for_each(m_vecObj[eID].begin(), m_vecObj[eID].end(), SafeDelete<CObj*>);
	m_vecObj[eID].clear();
}

CObj * CObjectMgr::Find_Light(string strLightName)
{
	CObj* pTemp = nullptr;

	auto iter = m_vecObj[OBJECT_LIGHT].begin();
	for (; iter != m_vecObj[OBJECT_LIGHT].end(); ++iter)
	{
		if ((*iter)->GetLightName() == strLightName)
		{
			pTemp = *iter;
		}
	}
	return pTemp;
}
