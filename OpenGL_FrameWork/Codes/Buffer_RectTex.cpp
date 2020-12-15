#include "pch.h"
#include "..\Headers\Buffer_RectTex.h"
#include "Shader.h"

CBuffer_RectTex::CBuffer_RectTex()
{
}


CBuffer_RectTex::~CBuffer_RectTex()
{
}

void CBuffer_RectTex::Init()
{
	m_iNumVertices = 4;
	m_iNumPolygons = 2;

	m_vecVertex.resize(m_iNumVertices);

	m_vecVertex[0].vPos = { -0.5f, -0.5f, 0.f };
	m_vecVertex[0].vColor = { 1.f,1.f,1.f };
	m_vecVertex[0].vTexUV = { 0.f, 1.f };

	m_vecVertex[1].vPos = { 0.5f, -0.5f, 0.f };
	m_vecVertex[1].vColor = { 1.f,1.f,1.f };
	m_vecVertex[1].vTexUV = { 1.f, 1.f};

	m_vecVertex[2].vPos = { 0.5f, 0.5f, 0.f };
	m_vecVertex[2].vColor = { 1.f,1.f,1.f };
	m_vecVertex[2].vTexUV = { 1.f, 0.f};

	m_vecVertex[3].vPos = { -0.5f, 0.5f, 0.f };
	m_vecVertex[3].vColor = { 1.f,1.f,1.f };
	m_vecVertex[3].vTexUV = { 0.f, 0.f };

	m_vecIndices.resize(6);
	m_vecIndices =
	{
		0, 1, 3,
		1, 2, 3
	};

	glGenVertexArrays(1, &VAO);


	glGenBuffers(1, &VBO_Pos);
	glGenBuffers(1, &VBO_Col);
	glGenBuffers(1, &VBO_UV);
	glGenBuffers(1, &EBO);


	glBindVertexArray(VAO);


	glBindBuffer(GL_ARRAY_BUFFER, VBO_Pos);
	glBufferData(GL_ARRAY_BUFFER, m_vecVertex.size() * sizeof(VTXUV), &m_vecVertex.front(), GL_STATIC_DRAW);
	_int	iAttribute = glGetAttribLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Texture")->GetShaderNum(), "vPos");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VTXUV), 0);
	glEnableVertexAttribArray(iAttribute);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_Col);
	glBufferData(GL_ARRAY_BUFFER, m_vecVertex.size() * sizeof(VTXUV), &m_vecVertex.front(), GL_STATIC_DRAW);
	iAttribute = glGetAttribLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Texture")->GetShaderNum(), "vColor");
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VTXUV), (void*)offsetof(VTXUV, vColor));
	glEnableVertexAttribArray(iAttribute);


	glBindBuffer(GL_ARRAY_BUFFER, VBO_UV);
	glBufferData(GL_ARRAY_BUFFER, m_vecVertex.size() * sizeof(VTXUV), &m_vecVertex.front(), GL_STATIC_DRAW);
	iAttribute = glGetAttribLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Texture")->GetShaderNum(), "vTexUV");
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VTXUV), (void*)offsetof(VTXUV, vTexUV));
	glEnableVertexAttribArray(iAttribute);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_vecIndices.size() * sizeof(_uint), &m_vecIndices.front(), GL_STATIC_DRAW);

}

void CBuffer_RectTex::Update()
{
} 

void CBuffer_RectTex::Render()
{ 
	glUseProgram(CShaderMgr::GetInstance()->GetShader(L"Shader_Texture")->GetShaderNum());
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, m_vecIndices.size(), GL_UNSIGNED_INT, (void*)0);
	//delete tTemp.pData;
}

void CBuffer_RectTex::Release()
{
}
