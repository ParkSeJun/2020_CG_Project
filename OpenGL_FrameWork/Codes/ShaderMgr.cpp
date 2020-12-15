#include "pch.h"
#include "..\Headers\ShaderMgr.h"
#include "Shader.h"

_IMPLEMENT_SINGLETON(CShaderMgr)
CShaderMgr::CShaderMgr()
{
}


CShaderMgr::~CShaderMgr()
{
	Release();
}

HRESULT CShaderMgr::AddShader(const _tchar* pShader_Tag, const char* vertexShader_FileName, const char* FragmentShader_FileName)
{
	CShader* pShader = Find_Shader(pShader_Tag);
	if (nullptr != pShader)
		return E_FAIL;

	pShader = new CShader;
	if (FAILED(pShader->Create_Shader(vertexShader_FileName, FragmentShader_FileName)))
	{
		SafeDelete(pShader);
		return E_FAIL;
	}
	

	m_mapShader.insert({pShader_Tag, pShader});

	return S_OK;
}

CShader * CShaderMgr::GetShader(const _tchar * pShader_Tag)
{
	CShader* pShader = Find_Shader(pShader_Tag);
	if (nullptr == pShader)
		return nullptr;

	return pShader;
}

CShader * CShaderMgr::Find_Shader(const _tchar * pShader_Tag)
{
	auto iter = find_if(m_mapShader.begin(), m_mapShader.end(), CFinder_Tag(pShader_Tag));

	if (iter == m_mapShader.end())
		return nullptr;

	return iter->second;
}

void CShaderMgr::Release()
{
	for (auto& iter : m_mapShader)
	{
		SafeDelete(iter.second);
	}
}
