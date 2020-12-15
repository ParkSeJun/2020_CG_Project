#include "pch.h"


CTexture::CTexture()
{
}


CTexture::~CTexture()
{
}

HRESULT CTexture::Create_Texture(const char* pFilePath, _int iIdx)
{
	if (FAILED(m_tTexture.pData = stbi_load(pFilePath, &m_tTexture.iWidth, &m_tTexture.iHeight, &m_tTexture.iChannel, 0)))
		return E_FAIL;


	return S_OK;
}

_int CTexture::Find_Texture(const char* pFilePath)
{
	return _int();
}
