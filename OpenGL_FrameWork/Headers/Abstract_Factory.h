#pragma once
class CObj;

template <typename T>
class CAbstractFactory
{
public:
	static CObj* CreateObj()
	{
		CObj* pObject = new T;

		if (FAILED(pObject->Init()))
		{
			SafeDelete(pObject);
			return nullptr;
		}

		return pObject;
	}
	static CObj* CreateObj(vec3 vPos, vec3 vSize, vec3 vColor)
	{
		CObj* pObject = new T;

		if (FAILED(pObject->Init(vPos, vSize, vColor)))
		{
			SafeDelete(pObject);
			return nullptr;
		}

		return pObject;
	}
 	static CObj* CreateObj(vec3 vPos, vec3 vSize, vec3 vColor, CObj* pTarget)
	{
		CObj* pObject = new T;

		if (FAILED(pObject->Init(vPos, vSize, vColor, pTarget)))
		{
			SafeDelete(pObject);
			return nullptr;
		}

		return pObject;
	}
	static CObj* CreateObj(vec3 vLightPos, vec3 vLightColor, string strLightName)
	{
		CObj* pObject = new T;

		if (FAILED(pObject->Init(vLightPos, vLightColor, strLightName)))
		{
			SafeDelete(pObject);
			return nullptr;
		}

		return pObject;
	}
};