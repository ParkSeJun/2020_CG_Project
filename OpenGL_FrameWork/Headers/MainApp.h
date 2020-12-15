#pragma once
class CMainApp
{
public:
	CMainApp();
	~CMainApp();
public:
	HRESULT Init();
	void	Update(_float fTimeDelta);
	void	Render();
	void	Release();
private:
	HRESULT		SetUp_Texture_Filltering();
public:
	HRESULT		Create_Object();
};

