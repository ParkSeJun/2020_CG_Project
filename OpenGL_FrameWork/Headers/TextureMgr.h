#pragma once
class CTexture;
class CTextureMgr
{
	_DECLARE_SINGLETON(CTextureMgr)
private:
	CTextureMgr();
	~CTextureMgr();
public:
	HRESULT		Add_Texture(const _tchar* pTextureTag, const char* pFilePath, _int iIdx = 0);
	CTexture*	GetTexture(const _tchar* pTextureTag);
private:
	CTexture*	Find_Texture(const _tchar* pTextureTag);
	void		Release();
private:
	map<const _tchar*, CTexture*> m_mapTexture;
};

