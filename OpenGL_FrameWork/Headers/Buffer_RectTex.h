#pragma once
#include "Buffer.h"
class CBuffer_RectTex :
	public CBuffer
{
public:
	CBuffer_RectTex();
	virtual ~CBuffer_RectTex();
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
private:
	vector<VTXUV>		m_vecVertex;
	vector<_uint>		m_vecIndices;
};

