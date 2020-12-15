#include "pch.h"
#include "..\Headers\Buffer_FoodCol.h"
#include "Shader.h"

CBuffer_FoodCol::CBuffer_FoodCol()
{
}


CBuffer_FoodCol::~CBuffer_FoodCol()
{
}

void CBuffer_FoodCol::Init()
{
	m_iNumPolygons = 12;
	m_iNumVertices = 8;

	m_vecVertex.resize(m_iNumVertices);

	m_vecVertex[0].vPos = { -0.5f, -0.5f, 0.5f };
	m_vecVertex[0].vColor = { 1.f, 1.f, 0.f };
	m_vecVertex[0].vNormal = {  };

	m_vecVertex[1].vPos = { 0.5f, -0.5f, 0.5f };
	m_vecVertex[1].vColor = { 1.f, 1.f, 0.f };
	m_vecVertex[1].vNormal = {  };

	m_vecVertex[2].vPos = { 0.5f, 0.5f, 0.5f };
	m_vecVertex[2].vColor = { 1.f, 1.f, 0.f };
	m_vecVertex[2].vNormal = {  };

	m_vecVertex[3].vPos = { -0.5f, 0.5f, 0.5f };
	m_vecVertex[3].vColor = { 1.f, 1.f, 0.f };
	m_vecVertex[3].vNormal = {  };

	m_vecVertex[4].vPos = { -0.5f, -0.5f, -0.5f };
	m_vecVertex[4].vColor = { 1.f, 1.f, 0.f };
	m_vecVertex[4].vNormal = {  };

	m_vecVertex[5].vPos = { 0.5f, -0.5f, -0.5f };
	m_vecVertex[5].vColor = { 1.f, 1.f, 0.f };
	m_vecVertex[5].vNormal = { };

	m_vecVertex[6].vPos = { 0.5f, 0.5f, -0.5f };
	m_vecVertex[6].vColor = { 1.f, 1.f, 0.f };
	m_vecVertex[6].vNormal = {  };

	m_vecVertex[7].vPos = { -0.5f, 0.5f, -0.5f };
	m_vecVertex[7].vColor = { 1.f, 1.f, 0.f };
	m_vecVertex[7].vNormal = {  };


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
	for (int i = 0; i < 36;)
	{
		vec3 vSour, vDest, vNormal;
		//ÁÂÇÏ
		vSour = m_vecVertex[m_vecIndices[i + 1]].vPos - m_vecVertex[m_vecIndices[i]].vPos;
		vDest = m_vecVertex[m_vecIndices[i + 2]].vPos - m_vecVertex[m_vecIndices[i]].vPos;
		vNormal = normalize(cross(vSour, vDest));

		m_vecVertex[m_vecIndices[i]].vNormal += vNormal;
		m_vecVertex[m_vecIndices[i + 1]].vNormal += vNormal;
		m_vecVertex[m_vecIndices[i + 2]].vNormal += vNormal;
		++++++i;

		//¿ì»ó
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

void CBuffer_FoodCol::Update()
{

}

void CBuffer_FoodCol::Render()
{
	glBindVertexArray(VAO);
	glUseProgram(CShaderMgr::GetInstance()->GetShader(L"Shader_Normal")->GetShaderNum());
	glDrawElements(GL_TRIANGLES, m_vecIndices.size(), GL_UNSIGNED_INT, (void*)0);
}

void CBuffer_FoodCol::Release()
{
}
