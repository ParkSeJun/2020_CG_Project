#pragma once
#include "Buffer.h"
class CTransform;
class CBuffer_Terrain :
	public CBuffer
{
public:
	CBuffer_Terrain();
	virtual ~CBuffer_Terrain();
public:
	virtual void Init() override;
	virtual void Init(const _tchar* pHeightMap, const _float& fInterval);
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
public:
	_float Compute_HeightOnTerrain(CTransform* pPosition);
private:
	_uint				m_iNumVerticesX = 0;
	_uint				m_iNumVerticesZ = 0;
	_float				m_fInterval = 0.f;
	BITMAPFILEHEADER	m_fh;
	BITMAPINFOHEADER	m_ih;
	_ulong*				m_pPixel = nullptr;
private:
	vector<VTXNORMAL>		m_vecVertex;
	vector<_uint>		m_vecIndices;
	vec3*								m_pPosition = nullptr;
};

