#include "pch.h"
#include "..\Headers\Buffer_Terrain.h"
#include "Shader.h"
#include "Transform.h"

CBuffer_Terrain::CBuffer_Terrain()
{
}


CBuffer_Terrain::~CBuffer_Terrain()
{
	Release();
}

void CBuffer_Terrain::Init()
{
}

void CBuffer_Terrain::Init(const _tchar * pHeightMap, const _float & fInterval)
{
	_uint		iNumVerticesX, iNumVerticesZ;

	HANDLE		hFile = 0;
	_ulong		dwByte = 0;

	hFile = CreateFile(pHeightMap, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (0 == hFile)
		return ;

	// 파일정보
	ReadFile(hFile, &m_fh, sizeof(BITMAPFILEHEADER), &dwByte, nullptr);

	// 이미지정보
	ReadFile(hFile, &m_ih, sizeof(BITMAPINFOHEADER), &dwByte, nullptr);

	iNumVerticesX = m_ih.biWidth;
	iNumVerticesZ = m_ih.biHeight;

	m_pPixel = new _ulong[iNumVerticesX * iNumVerticesZ];

	// 픽셀정보
	ReadFile(hFile, m_pPixel, sizeof(_ulong) * (iNumVerticesX * iNumVerticesZ), &dwByte, nullptr);

	CloseHandle(hFile);

	m_iNumVerticesX = iNumVerticesX;
	m_iNumVerticesZ = iNumVerticesZ;

	m_pPosition = new vec3[iNumVerticesX * iNumVerticesZ];
	m_fInterval = fInterval;

	m_iNumVertices = iNumVerticesX * iNumVerticesZ;

	m_iNumPolygons = (iNumVerticesX - 1) * (iNumVerticesZ - 1) * 2;

	
	m_vecVertex.resize(m_iNumVertices);


	for (size_t i = 0; i < iNumVerticesZ; i++)
	{
		for (size_t j = 0; j < iNumVerticesX; j++)
		{
			_uint		iIndex = i * iNumVerticesX + j;

			m_vecVertex[iIndex].vPos = vec3(j * m_fInterval, (m_pPixel[iIndex] & 0x000000ff) / 10.0f, i * m_fInterval);
			m_pPosition[iIndex] = m_vecVertex[iIndex].vPos;
			//m_vecVertex[iIndex].vColor = vec3(j * m_fInterval, (m_pPixel[iIndex] & 0x000000ff) / 10.0f, i * m_fInterval);
			m_vecVertex[iIndex].vColor = {1.f,1.f,1.f};
		}
	}

	m_vecIndices.resize(m_iNumPolygons*3);

	_uint			iPolygonIndex = 0;

	for (size_t i = 0; i < iNumVerticesZ - 1; i++)
	{
		for (size_t j = 0; j < iNumVerticesX - 1; j++)
		{
			size_t iIndex = i * iNumVerticesX + j;

			// 우.상
			m_vecIndices[iPolygonIndex] = iIndex + iNumVerticesX + 1;
			++iPolygonIndex;
			m_vecIndices[iPolygonIndex] = iIndex + iNumVerticesX;
			++iPolygonIndex;
			m_vecIndices[iPolygonIndex] = iIndex + 1;
			++iPolygonIndex;

			// 좌.하
			m_vecIndices[iPolygonIndex] = iIndex + iNumVerticesX;
			++iPolygonIndex;
			m_vecIndices[iPolygonIndex] = iIndex;
			++iPolygonIndex;
			m_vecIndices[iPolygonIndex] = iIndex + 1;
			++iPolygonIndex;
		}
	}

	for (int i = 0; i < m_iNumPolygons * 3;)
	{
		vec3 vSour, vDest, vNormal;
		//좌하
		vSour = m_vecVertex[m_vecIndices[i + 1]].vPos - m_vecVertex[m_vecIndices[i]].vPos;
		vDest = m_vecVertex[m_vecIndices[i + 2]].vPos - m_vecVertex[m_vecIndices[i]].vPos;
		vNormal = normalize(cross(vSour, vDest));

		m_vecVertex[m_vecIndices[i]].vNormal += vNormal;
		m_vecVertex[m_vecIndices[i + 1]].vNormal += vNormal;
		m_vecVertex[m_vecIndices[i + 2]].vNormal += vNormal;
		++++++i;

		//우상
		vSour = m_vecVertex[m_vecIndices[i + 2]].vPos - m_vecVertex[m_vecIndices[i + 1]].vPos;
		vDest = m_vecVertex[m_vecIndices[i]].vPos - m_vecVertex[m_vecIndices[i + 1]].vPos;
		vNormal = normalize(cross(vSour, vDest));

		m_vecVertex[m_vecIndices[i]].vNormal += vNormal;
		m_vecVertex[m_vecIndices[i + 1]].vNormal += vNormal;
		m_vecVertex[m_vecIndices[i + 2]].vNormal += vNormal;
		++++++i;


	}
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO_Pos);
	glGenBuffers(1, &VBO_Col);
	glGenBuffers(1, &VBO_NORMAL);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);


	glBindBuffer(GL_ARRAY_BUFFER, VBO_Pos);
	glBufferData(GL_ARRAY_BUFFER, m_vecVertex.size() * sizeof(VTXNORMAL), &m_vecVertex.front(), GL_STATIC_DRAW);
	GLint iAttribute = glGetAttribLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Normal")->GetShaderNum(), "vPos");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VTXNORMAL), 0);
	glEnableVertexAttribArray(iAttribute);


	glBindBuffer(GL_ARRAY_BUFFER, VBO_Col);
	glBufferData(GL_ARRAY_BUFFER, m_vecVertex.size() * sizeof(VTXNORMAL), &m_vecVertex.front(), GL_STATIC_DRAW);
	iAttribute = glGetAttribLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Normal")->GetShaderNum(), "vColor");
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VTXNORMAL), (void*)offsetof(VTXNORMAL, vColor));
	glEnableVertexAttribArray(iAttribute);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_NORMAL);
	glBufferData(GL_ARRAY_BUFFER, m_vecVertex.size() * sizeof(VTXNORMAL), &m_vecVertex.front(), GL_STATIC_DRAW);
	iAttribute = glGetAttribLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Normal")->GetShaderNum(), "vNormal");
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VTXNORMAL), (void*)offsetof(VTXNORMAL, vNormal));
	glEnableVertexAttribArray(iAttribute);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_vecIndices.size() * sizeof(_uint), &m_vecIndices.front(), GL_STATIC_DRAW);
}

void CBuffer_Terrain::Update()
{
}

void CBuffer_Terrain::Render()
{
	glUseProgram(CShaderMgr::GetInstance()->GetShader(L"Shader_Normal")->GetShaderNum());
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, m_vecIndices.size(), GL_UNSIGNED_INT, (void*)0);
}

void CBuffer_Terrain::Release()
{
	SafeDelete(m_pPixel);
	SafeDelete(m_pPosition);
}

_float CBuffer_Terrain::Compute_HeightOnTerrain(CTransform* pPosition)
{
	const vec3* pTargetPos = pPosition->Get_StateInfo(STATE_POSITION);

	_uint		iCurrentIdx = _uint(pTargetPos->z / m_fInterval) * m_iNumVerticesX + _uint(pTargetPos->x / m_fInterval);

	_float		fRatioX = (pTargetPos->x - m_pPosition[iCurrentIdx + m_iNumVerticesX].x) / m_fInterval;
	_float		fRatioZ = (m_pPosition[iCurrentIdx + m_iNumVerticesX].z - pTargetPos->z) / m_fInterval;

	_float		fHeight[4] =
	{
		m_pPosition[iCurrentIdx + m_iNumVerticesX].y,
		m_pPosition[iCurrentIdx + m_iNumVerticesX + 1].y,
		m_pPosition[iCurrentIdx + 1].y,
		m_pPosition[iCurrentIdx].y
	};

	// 오른쪽위에있는삼각형
	if (fRatioX >= fRatioZ)
	{
		return fHeight[0] + (fHeight[1] - fHeight[0]) * fRatioX + (fHeight[2] - fHeight[1]) * fRatioZ;
	}
	// 왼쪽 아래에있는삼각형
	else
	{
		return fHeight[0] + (fHeight[3] - fHeight[0]) * fRatioZ + (fHeight[2] - fHeight[3]) * fRatioX;
	}
}
