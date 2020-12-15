#include "pch.h"
#include "..\Headers\Pyramid.h"
#include "Buffer_PyramidCol.h"
#include "Shader.h"

CPyramid::CPyramid()
{
}


CPyramid::~CPyramid()
{
}

HRESULT CPyramid::Init()
{
	m_pBuffer = new CBuffer_PyramidCol;
	m_pBuffer->Init();

	return S_OK;
}

int CPyramid::Update()
{

	return 0;
}

void CPyramid::Render()
{


	m_pBuffer->Render();
}

void CPyramid::Release()
{
	SafeDelete(m_pBuffer);
}
