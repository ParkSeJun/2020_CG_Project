#include "pch.h"
#include "..\Headers\TextureMgr.h"

_IMPLEMENT_SINGLETON(CTextureMgr)
CTextureMgr::CTextureMgr()
{
}


CTextureMgr::~CTextureMgr()
{
	Release();
}

HRESULT CTextureMgr::Add_Texture(const _tchar * pTextureTag, const char * pFilePath, _int iIdx)
{
	CTexture* pTexture = Find_Texture(pTextureTag);
	if (nullptr != pTexture)
		return E_FAIL;

	pTexture = new CTexture;
	if (FAILED(pTexture->Create_Texture(pFilePath, iIdx)))
	{
		SafeDelete(pTexture);
		return E_FAIL;
	}


	m_mapTexture.insert({ pTextureTag, pTexture });

	return S_OK;
}

CTexture * CTextureMgr::GetTexture(const _tchar * pTextureTag)
{
	CTexture* pTexture = Find_Texture(pTextureTag);
	if (nullptr == pTexture)
		return nullptr;

	return pTexture;
}

CTexture * CTextureMgr::Find_Texture(const _tchar * pTextureTag)
{
	auto iter = find_if(m_mapTexture.begin(), m_mapTexture.end(), CFinder_Tag(pTextureTag));

	if (iter == m_mapTexture.end())
		return nullptr;

	return iter->second;
}

void CTextureMgr::Release()
{
	for (auto& iter : m_mapTexture)
	{
		SafeDelete(iter.second);
	}
}
