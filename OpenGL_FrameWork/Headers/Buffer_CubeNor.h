#pragma once
#include "Buffer.h"
class CBuffer_CubeNor :
	public CBuffer
{
public:
	CBuffer_CubeNor();
	virtual ~CBuffer_CubeNor();
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
private:
	vector<VTXNORMAL>		m_vecVertex;
	vector<_uint>			m_vecIndices;
};

