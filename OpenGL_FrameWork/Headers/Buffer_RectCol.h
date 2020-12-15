#pragma once
#include "Buffer.h"
class CBuffer_RectCol :
	public CBuffer
{
public:
	CBuffer_RectCol();
	virtual ~CBuffer_RectCol();
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
public:
	void	SetColor(vec3 vColor);
private:
	vector<VTXCOL>		m_vecVertex;
	vector<_uint>		m_vecIndices;
};

