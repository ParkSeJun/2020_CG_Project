#include "pch.h"
#include "..\Headers\Buffer_CubeCol.h"
#include "Shader.h"

CBuffer_CubeCol::CBuffer_CubeCol()
{
}

CBuffer_CubeCol::~CBuffer_CubeCol()
{
	Release();
}

void CBuffer_CubeCol::Init()
{	
	m_iNumPolygons = 12;
	m_iNumVertices = 8;

	m_vecVertex.resize(m_iNumVertices);

	m_vecVertex[0].vPos = {-0.5f, -0.5f, 0.5f};
	m_vecVertex[0].vColor = { 0.5f, 0.5f, 1.f};

	m_vecVertex[1].vPos = {0.5f, -0.5f, 0.5f};
	m_vecVertex[1].vColor = { 1.f, 0.5f, 0.5f };

	m_vecVertex[2].vPos = {0.5f, 0.5f, 0.5f};
	m_vecVertex[2].vColor = { 1.f, 0.5f, 1.f };

	m_vecVertex[3].vPos = {-0.5f, 0.5f, 0.5f};
	m_vecVertex[3].vColor = { 1.f, 0.f, 0.f };

	m_vecVertex[4].vPos = {-0.5f, -0.5f, -0.5f};
	m_vecVertex[4].vColor = { 1.f, 0.f, 1.f };

	m_vecVertex[5].vPos = { 0.5f, -0.5f, -0.5f };
	m_vecVertex[5].vColor = { 0.5f, 0.5f, 0.5f };

	m_vecVertex[6].vPos = { 0.5f, 0.5f, -0.5f };
	m_vecVertex[6].vColor = { 1.f, 1.f, 0.5f };

	m_vecVertex[7].vPos = { -0.5f, 0.5f, -0.5f };
	m_vecVertex[7].vColor = { 0.5f, 1.f, 1.f };


	m_vecIndices.resize(36);

	m_vecIndices =
	{
		0, 1, 3, 
		1, 2, 3, 

		1, 5, 2, 
		5, 6, 2,

		3, 2, 7,
		2, 6, 7,

		5, 4, 6,
		4, 7, 6, 

		4, 0, 7,
		0, 3, 7,

		1, 0, 5,
		0, 4, 5
	};


	glGenVertexArrays(1, &VAO);


	glGenBuffers(1, &VBO_Pos);
	glGenBuffers(1, &VBO_Col);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);


	glBindBuffer(GL_ARRAY_BUFFER, VBO_Pos);
	glBufferData(GL_ARRAY_BUFFER, m_vecVertex.size() * sizeof(VTXCOL), &m_vecVertex.front(), GL_STATIC_DRAW);
	GLint iAttribute = glGetAttribLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Default")->GetShaderNum(), "vPos");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VTXCOL), 0);
	glEnableVertexAttribArray(iAttribute);


	glBindBuffer(GL_ARRAY_BUFFER, VBO_Col);
	glBufferData(GL_ARRAY_BUFFER, m_vecVertex.size() * sizeof(VTXCOL), &m_vecVertex.front(), GL_STATIC_DRAW);
	iAttribute = glGetAttribLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Default")->GetShaderNum(), "vColor");
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VTXCOL), (void*)offsetof(VTXCOL, vColor));
	glEnableVertexAttribArray(iAttribute);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_vecIndices.size() * sizeof(_uint), &m_vecIndices.front(), GL_STATIC_DRAW);
}

void CBuffer_CubeCol::Update()
{
}

void CBuffer_CubeCol::Render()
{
	glUseProgram(CShaderMgr::GetInstance()->GetShader(L"Shader_Default")->GetShaderNum());
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, m_vecIndices.size(), GL_UNSIGNED_INT, (void*)0);
}

void CBuffer_CubeCol::Release()
{
}

void CBuffer_CubeCol::SetColor(vec3 vColor)
{
	for (int i = 0; i < m_iNumVertices; ++i)
		m_vecVertex[i].vColor = vColor;

	glGenVertexArrays(1, &VAO);


	glGenBuffers(1, &VBO_Pos);
	glGenBuffers(1, &VBO_Col);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);


	glBindBuffer(GL_ARRAY_BUFFER, VBO_Pos);
	glBufferData(GL_ARRAY_BUFFER, m_vecVertex.size() * sizeof(VTXCOL), &m_vecVertex.front(), GL_STATIC_DRAW);
	GLint iAttribute = glGetAttribLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Default")->GetShaderNum(), "vPos");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VTXCOL), 0);
	glEnableVertexAttribArray(iAttribute);


	glBindBuffer(GL_ARRAY_BUFFER, VBO_Col);
	glBufferData(GL_ARRAY_BUFFER, m_vecVertex.size() * sizeof(VTXCOL), &m_vecVertex.front(), GL_STATIC_DRAW);
	iAttribute = glGetAttribLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Default")->GetShaderNum(), "vColor");
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VTXCOL), (void*)offsetof(VTXCOL, vColor));
	glEnableVertexAttribArray(iAttribute);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_vecIndices.size() * sizeof(_uint), &m_vecIndices.front(), GL_STATIC_DRAW);
}
