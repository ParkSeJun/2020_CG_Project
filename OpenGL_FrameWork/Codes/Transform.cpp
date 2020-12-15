#include "pch.h"
#include "..\Headers\Transform.h"
#include "Obj.h"


CTransform::CTransform()
{
	if (FAILED(Init()))
		return;

}


CTransform::~CTransform()
{
}

HRESULT CTransform::Init()
{
	m_matWorld = mat4(1.f);
	return S_OK;
}

vec3 * CTransform::Get_StateInfo(STATE eState)
{
	vec3* temp = (vec3*)&m_matWorld[eState][0];
	return temp;
}

mat4 CTransform::GetNoneScaleMatrix( _float fScaleX, _float fScaleY, _float fScaleZ)
{
	mat4 matTemp = m_matWorld;
	matTemp[0][0] = fScaleX;
	matTemp[1][1] = fScaleY;
	matTemp[2][2] = fScaleZ;
	return matTemp;
}

vec3 CTransform::GetScale()
{
	_float			fScaleX = length(*Get_StateInfo(STATE_RIGHT));
	_float			fScaleY = length(*Get_StateInfo(STATE_UP));
	_float			fScaleZ = length(*Get_StateInfo(STATE_LOOK));

	return vec3(fScaleX, fScaleY, fScaleZ);
}

mat4 CTransform::Get_Matrix_Inverse() const
{
	mat4 mat = m_matWorld;
	mat = inverse(mat);
	return mat;
}



void CTransform::Set_StateInfo(STATE eState, const vec3 * pInfo)
{
	memcpy(&m_matWorld[eState][0], pInfo, sizeof(vec3));
}

void CTransform::SetUp_Speed(const _float & fSpeed, const _float& fRotSpeed)
{
	m_fSpeed = fSpeed;
	m_fRotation_Speed = fRotSpeed;
}

void CTransform::Go_Straight()
{
	vec3		vLook, vPosition;
	vLook = *Get_StateInfo(STATE_LOOK);
	vPosition = *Get_StateInfo(STATE_POSITION);

	vLook = normalize(vLook);
	vLook = vLook * -m_fSpeed;
	vPosition = vPosition + vLook;

	Set_StateInfo(STATE_POSITION, &vPosition);
}

void CTransform::BackWard()
{
	vec3		vLook, vPosition;
	vLook = *Get_StateInfo(STATE_LOOK);
	vPosition = *Get_StateInfo(STATE_POSITION);

	vLook = normalize(vLook);
	vLook = vLook * m_fSpeed;
	vPosition = vPosition + vLook;

	Set_StateInfo(STATE_POSITION, &vPosition);
}

void CTransform::Go_Left()
{
	vec3		vRight, vPosition;

	vRight = *Get_StateInfo(STATE_RIGHT);
	vPosition = *Get_StateInfo(STATE_POSITION);

	vRight = normalize(vRight);
	vRight = vRight * -m_fSpeed;
	vPosition = vPosition + vRight;

	Set_StateInfo(STATE_POSITION, &vPosition);
}

void CTransform::Go_Right()
{
	vec3		vRight, vPosition;

	vRight = *Get_StateInfo(STATE_RIGHT);
	vPosition = *Get_StateInfo(STATE_POSITION);

	vRight = normalize(vRight);

	vRight = vRight * m_fSpeed;
	vPosition = vPosition + vRight;

	Set_StateInfo(STATE_POSITION, &vPosition);
}

void CTransform::Go_Up()
{
	vec3		vUp, vPosition;

	vUp = *Get_StateInfo(STATE_UP);
	vPosition = *Get_StateInfo(STATE_POSITION);

	vUp = normalize(vUp);

	vUp = vUp * m_fSpeed;
	vPosition = vPosition + vUp;

	Set_StateInfo(STATE_POSITION, &vPosition);
}

void CTransform::Go_Down()
{
	vec3		vUp, vPosition;

	vUp = *Get_StateInfo(STATE_UP);
	vPosition = *Get_StateInfo(STATE_POSITION);

	vUp = normalize(vUp);

	vUp = vUp * -m_fSpeed;
	vPosition = vPosition + vUp;

	Set_StateInfo(STATE_POSITION, &vPosition);
}

void CTransform::SetUp_RotationX(const _float & fRadian)
{
	vec3		vRight(1.f, 0.f, 0.f), vUp(0.f, 1.f, 0.f), vLook(0.f, 0.f, 1.f);

	mat4			matRot = mat4(1.f);
	matRot = rotate(matRot, fRadian, vec3(1.f, 0.f, 0.f));

	vRight *= GetScale().x;
	vUp *= GetScale().y;
	vLook *= GetScale().z;

	vRight = mat3(matRot)*vRight;
	vUp = mat3(matRot)*vUp;
	vLook = mat3(matRot)*vLook;

	Set_StateInfo(STATE_RIGHT, &vRight);
	Set_StateInfo(STATE_UP, &vUp);
	Set_StateInfo(STATE_LOOK, &vLook);
}

void CTransform::SetUp_RotationY(const _float & fRadian)
{
	vec3		vRight(1.f, 0.f, 0.f), vUp(0.f, 1.f, 0.f), vLook(0.f, 0.f, 1.f);

	mat4			matRot = mat4(1.f);
	matRot = rotate(matRot, fRadian, vec3(0.f, 1.f, 0.f));

	vRight *= GetScale().x;
	vUp *= GetScale().y;
	vLook *= GetScale().z;

	vRight = mat3(matRot)*vRight;
	vUp = mat3(matRot)*vUp;
	vLook = mat3(matRot)*vLook;

	Set_StateInfo(STATE_RIGHT, &vRight);
	Set_StateInfo(STATE_UP, &vUp);
	Set_StateInfo(STATE_LOOK, &vLook);
}

void CTransform::SetUp_RotationZ(const _float & fRadian)
{
	vec3		vRight(1.f, 0.f, 0.f), vUp(0.f, 1.f, 0.f), vLook(0.f, 0.f, 1.f);

	mat4			matRot = mat4(1.f);
	matRot = rotate(matRot, fRadian, vec3(0.f, 0.f, 1.f));

	vRight *= GetScale().x;
	vUp *= GetScale().y;
	vLook *= GetScale().z;

	vRight = mat3(matRot)*vRight;
	vUp = mat3(matRot)*vUp;
	vLook = mat3(matRot)*vLook;

	Set_StateInfo(STATE_RIGHT, &vRight);
	Set_StateInfo(STATE_UP, &vUp);
	Set_StateInfo(STATE_LOOK, &vLook);
}

void CTransform::RotationX(_float fDir)
{
	vec3		vDir[3];

	for (size_t i = 0; i < 3; ++i)
		vDir[i] = *Get_StateInfo(STATE(i));

	mat4			matRot = mat4(1.f);

	matRot = rotate(matRot, m_fRotation_Speed*fDir, vec3(1.f, 0.f, 0.f));
	for (size_t i = 0; i < 3; ++i)
		vDir[i] = mat3(matRot)*vDir[i];

	Set_StateInfo(STATE_RIGHT, &vDir[STATE_RIGHT]);
	Set_StateInfo(STATE_UP, &vDir[STATE_UP]);
	Set_StateInfo(STATE_LOOK, &vDir[STATE_LOOK]);
}

void CTransform::RotationY(_float fDir)
{
	vec3		vDir[3];

	for (size_t i = 0; i < 3; ++i)
		vDir[i] = *Get_StateInfo(STATE(i));

	mat4			matRot = mat4(1.f);

	matRot = rotate(matRot, m_fRotation_Speed*fDir, vec3(0.f, 1.f, 0.f));
	for (size_t i = 0; i < 3; ++i)
		vDir[i] = mat3(matRot)*vDir[i];

	Set_StateInfo(STATE_RIGHT, &vDir[STATE_RIGHT]);
	Set_StateInfo(STATE_UP, &vDir[STATE_UP]);
	Set_StateInfo(STATE_LOOK, &vDir[STATE_LOOK]);
}

void CTransform::RotationZ(_float fDir)
{
	vec3		vDir[3];

	for (size_t i = 0; i < 3; ++i)
		vDir[i] = *Get_StateInfo(STATE(i));

	mat4			matRot = mat4(1.f);

	matRot = rotate(matRot, m_fRotation_Speed*fDir, vec3(0.f, 0.f, 1.f));
	for (size_t i = 0; i < 3; ++i)
		vDir[i] = mat3(matRot)*vDir[i];

	Set_StateInfo(STATE_RIGHT, &vDir[STATE_RIGHT]);
	Set_StateInfo(STATE_UP, &vDir[STATE_UP]);
	Set_StateInfo(STATE_LOOK, &vDir[STATE_LOOK]);
}

void CTransform::Rotation_Axis(_float fDir, const vec3 * pAxis)
{
	vec3		vDir[3];

	for (size_t i = 0; i < 3; ++i)
		vDir[i] = *Get_StateInfo(STATE(i));

	mat4			matRot = mat4(1.f);
	matRot = rotate(matRot, m_fRotation_Speed*fDir, *pAxis);
	for (size_t i = 0; i < 3; ++i)
		vDir[i] = mat3(matRot)*vDir[i];

	Set_StateInfo(STATE_RIGHT, &vDir[STATE_RIGHT]);
	Set_StateInfo(STATE_UP, &vDir[STATE_UP]);
	Set_StateInfo(STATE_LOOK, &vDir[STATE_LOOK]);
}

void CTransform::Scaling(vec3 vScale)
{
	vec3		vDir[3];

	for (size_t i = 0; i < 3; ++i)
	{
		vDir[i] = *Get_StateInfo(STATE(i));
		vDir[i] = normalize(vDir[i]);
	}

	vDir[STATE_RIGHT] *= vScale.x;
	vDir[STATE_UP] *= vScale.y;
	vDir[STATE_LOOK] *= vScale.z;

	Set_StateInfo(STATE_RIGHT, &vDir[STATE_RIGHT]);
	Set_StateInfo(STATE_UP, &vDir[STATE_UP]);
	Set_StateInfo(STATE_LOOK, &vDir[STATE_LOOK]);
}

void CTransform::Go_ToTarget(vec3 * pTargetPos)
{
	vec3	vLook, vPosition;

	vPosition = *Get_StateInfo(STATE_POSITION);

	vLook = *pTargetPos - vPosition;
	vLook = normalize(vLook);
	vPosition += vLook * m_fSpeed;

	Set_StateInfo(STATE_POSITION, &vPosition);
}

void CTransform::Rotaion_Rev(mat4 matParent, const vec3 * pAxis)
{
	mat4 matResult = mat4(1.f);
	mat4 matScale = mat4(1.f);
	mat4 matRot = mat4(1.f);
	mat4 matTrans = mat4(1.f);
	mat4 matRev = mat4(1.f);
	mat4 matParents = mat4(1.f);


	matScale = scale(matScale, this->GetScale());
	matRot = rotate(matRot, m_fRotation_Speed, *pAxis);
	matTrans = translate(matTrans, *this->Get_StateInfo(STATE_POSITION));
	matRev = rotate(matRev, m_fRotation_Speed, *pAxis);

	// r s t
	// 스 자 이 공 부
	//matResult = matTrans * matRot*matScale;
	//matResult = matRot * matScale * matTrans;
	matResult = matScale * matRot * matTrans;
	//matResult = matParents * matRev* matTrans* matRot* matScale;

	m_matWorld = matResult;
}

void CTransform::TempRotate(float fDir)
{
	_float fTempX = this->Get_StateInfo(STATE_POSITION)->x;
	_float fTempZ = this->Get_StateInfo(STATE_POSITION)->z;

	if (fDir <= 0.f)
	{
		this->Get_StateInfo(STATE_POSITION)->x = fTempX * cosf(m_fRotation_Speed) - fTempZ * sinf(m_fRotation_Speed);
		this->Get_StateInfo(STATE_POSITION)->z = fTempX * sinf(m_fRotation_Speed) + fTempZ * cosf(m_fRotation_Speed);
	}
	else if (fDir >= 0.f)
	{
		this->Get_StateInfo(STATE_POSITION)->x = fTempX * cosf(-m_fRotation_Speed) - fTempZ * sinf(-m_fRotation_Speed);
		this->Get_StateInfo(STATE_POSITION)->z = fTempX * sinf(-m_fRotation_Speed) + fTempZ * cosf(-m_fRotation_Speed);
	}
}

void CTransform::Shake()
{
	if (m_iCnt_Shake >= 0)
	{
		this->Get_StateInfo(STATE_POSITION)->y += 10;
		//m_iCnt_Shake = -1;
		return;
	}
	else if(m_iCnt_Shake < 0)
	{
		this->Get_StateInfo(STATE_POSITION)->y -= 10;
		//m_iCnt_Shake = 1;
		return;
	}
}


