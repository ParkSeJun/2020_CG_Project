#pragma once
class CCameraMgr
{
	_DECLARE_SINGLETON(CCameraMgr)
private:
	CCameraMgr();
	~CCameraMgr();
private:
	mat4 m_matView = mat4(1.f);
	mat4 m_matProj = mat4(1.f);
public:
	mat4	Get_ViewMatrix() { return m_matView; }
	mat4	Get_ProjMatrix() { return m_matProj; }
public:
	void	Set_ViewMatrix(mat4 matView) { m_matView = matView; }
	void	Set_ProjMatrix(mat4 matView) { m_matProj = matView; }
public:
	void	Swap_Camera(CAMERA eCameraMode);
	HRESULT	SetUp_CameraOption(CAMERA eCameraMode);
private:
	CAMERA  m_eCameraMode = CAMERA_END;
	CAMERA	m_ePreCameraMode;
};

