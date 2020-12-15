#pragma once
#include "Buffer.h"
class CBuffer_CubeCol :
	public CBuffer
{
public:
	CBuffer_CubeCol();
	virtual ~CBuffer_CubeCol();
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
public:
	void	SetColor(vec3 vColor);
private:
	vector<VTXNORMAL>		m_vecVertex;
	vector<_uint>		m_vecIndices;
};

