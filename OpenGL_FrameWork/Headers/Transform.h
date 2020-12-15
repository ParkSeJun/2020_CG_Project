#pragma once
class CObj;
class CTransform
{
	
public:
	CTransform();
	~CTransform();
public:
	HRESULT					Init();
public:
public:
	vec3*					Get_StateInfo(STATE eState);
	mat4					GetMatrix() { return m_matWorld; }
	mat4					GetNoneScaleMatrix( _float fScaleX, _float fScaleY, _float fScaleZ);
	vec3					GetScale();
	const mat4*				Get_Matrix_Pointer()const { return &m_matWorld; }
	mat4					Get_Matrix_Inverse()const;
public:
	void					SetMatrix(mat4 mat) { m_matWorld = mat; }
public:
	void					Set_StateInfo(STATE eState, const vec3* pInfo);
	void					Set_PositionY(const _float& Y) { m_matWorld[1][3] = Y; }
public:
	void					SetUp_Speed(const _float& fSpeed, const _float& fRotSpeed);
	void					Go_Straight();
	vec3					Get_Straight();
	void					BackWard();
	void					Go_Left();
	void					Go_Right();
	void					Go_Up();
	void					Go_Down();
	void					SetUp_RotationX(const _float& fRadian);
	void					SetUp_RotationY(const _float& fRadian);
	void					SetUp_RotationZ(const _float& fRadian);
	void					RotationX(_float fDir);
	void					RotationY(_float fDir);
	void					RotationZ(_float fDir);
	void					Rotation_Axis(_float fDir, const vec3* pAxis);
	void					Scaling(vec3 vScale);
	void					Go_ToTarget(vec3* pTargetPos);
	void					Rotaion_Rev(mat4 matParent, const vec3 * pAxis);
	void					TempRotate(float fDir);
	void					Shake();
private:
	mat4					m_matWorld = mat4(1.f);
	_float					m_fSpeed = 0.f;
	_float					m_fRotation_Speed = 0.f;
private:
	_int					m_iCnt_Shake=1;
};

