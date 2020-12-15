#pragma once
#include "Buffer.h"
class CBuffer_TankCol :
	public CBuffer
{
public:
	CBuffer_TankCol();
	virtual ~CBuffer_TankCol();
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
public:
	void	SetColor(vec3 vColor);
private:
	vector<VTXNORMAL>	m_vecVertex;
	vector<_uint>		m_vecIndices;
	_float* vPosData;
	_float* vNormalData;
	_float* vTextureCoordinateData;
	_uint* indexData;
	_uint vertexCount;
	_uint indexCount;
};

