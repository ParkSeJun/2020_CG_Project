#include "pch.h"
#include "Shader.h"

CBuffer_TriCol::CBuffer_TriCol()
{
}


CBuffer_TriCol::~CBuffer_TriCol()
{
	Release();
}

void CBuffer_TriCol::Init()
{
	m_iNumVertices = 3;
	m_iNumPolygons = 1;

	m_vecVertex.resize(m_iNumVertices);

	m_vecVertex[0].vPos = {-0.25, 0.f, 0.f};
	m_vecVertex[0].vColor = { 1.f, 1.f, 1.f };

	m_vecVertex[1].vPos = { 0.25, 0.f, 0.f};
	m_vecVertex[1].vColor = { 1.f, 1.f, 1.f };

	m_vecVertex[2].vPos = { 0.f, 0.5f, 0.f};
	m_vecVertex[2].vColor = { 1.f, 1.f, 1.f };



	m_vecIndices.resize(3);
	m_vecIndices =
	{
		0, 1, 2
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

void CBuffer_TriCol::Update()
{
}

void CBuffer_TriCol::Render()
{
	glUseProgram(CShaderMgr::GetInstance()->GetShader(L"Shader_Default")->GetShaderNum());
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, m_vecIndices.size(), GL_UNSIGNED_INT, (void*)0);
}

void CBuffer_TriCol::Release()
{
	
}

void CBuffer_TriCol::SetColor(vec3 vColor)
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
