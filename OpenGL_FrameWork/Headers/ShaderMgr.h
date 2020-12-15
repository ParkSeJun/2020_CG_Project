#pragma once
class CShader;
class CShaderMgr
{
	_DECLARE_SINGLETON(CShaderMgr)
private:
	CShaderMgr();
	~CShaderMgr();
public:
	HRESULT		AddShader(const _tchar* pShader_Tag, const char* vertexShader_FileName, const char* FragmentShader_FileName);
	CShader*	GetShader(const _tchar* pShader_Tag);
private:
	CShader*	Find_Shader(const _tchar* pShader_Tag);
	void		Release();
private:
	map<const _tchar*, CShader*>			m_mapShader;
};

