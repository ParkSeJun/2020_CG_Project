#include "pch.h"
#include "..\Headers\Buffer_RectCol.h"
#include "Shader.h"

CBuffer_RectCol::CBuffer_RectCol()
{
}


CBuffer_RectCol::~CBuffer_RectCol()
{
}

void CBuffer_RectCol::Init()
{
	m_iNumVertices = 4;
	m_iNumPolygons = 2;

	m_vecVertex.resize(m_iNumVertices);

	m_vecVertex[0].vPos = { -0.5f, -0.5f, 0.f };
	m_vecVertex[0].vColor = { 1.f, 1.f, 1.f };

	m_vecVertex[1].vPos = { 0.5f, -0.5f, 0.f};
	m_vecVertex[1].vColor = { 1.f, 1.f, 1.f};

	m_vecVertex[2].vPos = { 0.5f, 0.5f, 0.f};
	m_vecVertex[2].vColor = { 1.f, 1.f, 1.f };


	m_vecVertex[3].vPos = { -0.5f, 0.5f, 0.f};
	m_vecVertex[3].vColor = { 1.f, 1.f, 1.f };

	m_vecIndices.resize(6);
	m_vecIndices = 
	{
		0, 1, 3,
		1, 2, 3
	};


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO_Pos);
	glGenBuffers(1, &VBO_Col);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);


	glBindBuffer(GL_ARRAY_BUFFER, VBO_Pos);
	glBufferData(GL_ARRAY_BUFFER, m_vecVertex.size() * sizeof(VTXCOL), &m_vecVertex.front(), GL_STATIC_DRAW);
	_int	iAttribute = glGetAttribLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Default")->GetShaderNum(), "vPos");
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

void CBuffer_RectCol::Update()
{
}

void CBuffer_RectCol::Render()
{	

	glUseProgram(CShaderMgr::GetInstance()->GetShader(L"Shader_Default")->GetShaderNum());
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, m_vecIndices.size(), GL_UNSIGNED_INT, (void*)0);
}

void CBuffer_RectCol::Release()
{
}

void CBuffer_RectCol::SetColor(vec3 vColor)
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
	_int	iAttribute = glGetAttribLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Default")->GetShaderNum(), "vPos");
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
