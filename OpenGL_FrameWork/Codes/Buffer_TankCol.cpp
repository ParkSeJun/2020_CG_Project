#include "pch.h"
#include "..\Headers\Buffer_TankCol.h"
#include "Shader.h"

CBuffer_TankCol::CBuffer_TankCol()
{
}


CBuffer_TankCol::~CBuffer_TankCol()
{
}

void CBuffer_TankCol::Init()
{
	m_iNumPolygons = 48;
	m_iNumVertices = 32;

	m_vecVertex.resize(m_iNumVertices);

	//Body
	{
		m_vecVertex[0].vPos = { -1.f, -0.5f, 1.f };
		m_vecVertex[0].vColor = { 0.4f, 0.5f, 0.f };

		m_vecVertex[1].vPos = { 1.f, -0.5f, 1.f };
		m_vecVertex[1].vColor = { 0.4f, 0.5f, 0.f };

		m_vecVertex[2].vPos = { 1.f, 0.5f, 1.f };
		m_vecVertex[2].vColor = { 0.4f, 0.5f, 0.f };

		m_vecVertex[3].vPos = { -1.f, 0.5f, 1.f };
		m_vecVertex[3].vColor = { 0.4f, 0.5f, 0.f };

		m_vecVertex[4].vPos = { -1.f, -0.5f, -1.f };
		m_vecVertex[4].vColor = { 0.4f, 0.5f, 0.f };

		m_vecVertex[5].vPos = { 1.f, -0.5f, -1.f };
		m_vecVertex[5].vColor = { 0.4f, 0.5f, 0.f };

		m_vecVertex[6].vPos = { 1.f, 0.5f, -1.f };
		m_vecVertex[6].vColor = { 0.4f, 0.5f, 0.f };

		m_vecVertex[7].vPos = { -1.f, 0.5f, -1.f };
		m_vecVertex[7].vColor = { 0.4f, 0.5f, 0.f };
	}
	//LeftWheel
	{
		//vPos.x - 1.5f, vPos.y - 0.5f, vPos.z + 0.f), vec3(1.f, 1.f, 3.f)
		m_vecVertex[8].vPos = { -2.f, -1.f, 1.5f };
		m_vecVertex[8].vColor = { 0.f, 0.f, 0.f };

		m_vecVertex[9].vPos = { -1.f, -1.f, 1.5f };
		m_vecVertex[9].vColor = { 0.f, 0.f, 0.f };

		m_vecVertex[10].vPos = { -1.f,0.f, 1.5f };
		m_vecVertex[10].vColor = { 0.f, 0.f, 0.f };

		m_vecVertex[11].vPos = { -2.f, 0.f, 1.5f };
		m_vecVertex[11].vColor = { 0.f, 0.f, 0.f };

		m_vecVertex[12].vPos = { -2.f, -1.f, -1.5f };
		m_vecVertex[12].vColor = { 0.f, 0.f, 0.f };

		m_vecVertex[13].vPos = { -1.f, -1.f, -1.5f };
		m_vecVertex[13].vColor = { 0.f, 0.f, 0.f };

		m_vecVertex[14].vPos = { -1.f, 0.f, -1.5f };
		m_vecVertex[14].vColor = { 0.f, 0.f, 0.f };

		m_vecVertex[15].vPos = { -2.f, 0.f, -1.5f };
		m_vecVertex[15].vColor = { 0.f, 0.f, 0.f };

	}
	//RightWheel
	{
		m_vecVertex[16].vPos = { 1.f, -1.f, 1.5f };
		m_vecVertex[16].vColor = { 0.f, 0.f, 0.f };

		m_vecVertex[17].vPos = { 2.f, -1.f, 1.5f };
		m_vecVertex[17].vColor = { 0.f, 0.f, 0.f };

		m_vecVertex[18].vPos = { 2.f, 0.f, 1.5f };
		m_vecVertex[18].vColor = { 0.f, 0.f, 0.f };

		m_vecVertex[19].vPos = { 1.f, 0.f, 1.5f };
		m_vecVertex[19].vColor = { 0.f, 0.f, 0.f };

		m_vecVertex[20].vPos = { 1.f, -1.f, -1.5f };
		m_vecVertex[20].vColor = { 0.f, 0.f, 0.f };

		m_vecVertex[21].vPos = { 2.f, -1.f, -1.5f };
		m_vecVertex[21].vColor = { 0.f, 0.f, 0.f };

		m_vecVertex[22].vPos = { 2.f,0.f, -1.5f };
		m_vecVertex[22].vColor = { 0.f, 0.f, 0.f };

		m_vecVertex[23].vPos = { 1.f, 0.f, -1.5f };
		m_vecVertex[23].vColor = { 0.f, 0.f, 0.f };
	}
	//Cannon
	{
		m_vecVertex[24].vPos = { -0.15f, -0.15f, -1.f };
		m_vecVertex[24].vColor = { 0.f, 0.f, 0.f };

		m_vecVertex[25].vPos = { 0.15f, -0.15f, -1.f };
		m_vecVertex[25].vColor = { 0.f, 0.f, 0.f };

		m_vecVertex[26].vPos = { 0.15f, 0.15f, -1.f };
		m_vecVertex[26].vColor = { 0.f, 0.f, 0.f };

		m_vecVertex[27].vPos = { -0.15f, 0.15f, -1.f };
		m_vecVertex[27].vColor = { 0.f, 0.f, 0.f };

		m_vecVertex[28].vPos = { -0.15f, -0.15f, -2.5f };
		m_vecVertex[28].vColor = { 0.f, 0.f, 0.f };

		m_vecVertex[29].vPos = { 0.15f, -0.15f, -2.5f };
		m_vecVertex[29].vColor = { 0.f, 0.f, 0.f };

		m_vecVertex[30].vPos = { 0.15f,0.15f, -2.5f };
		m_vecVertex[30].vColor = { 0.f, 0.f, 0.f };

		m_vecVertex[31].vPos = { -0.15f, 0.15f, -2.5f };
		m_vecVertex[31].vColor = { 0.f, 0.f, 0.f };

	}

	m_vecIndices.resize(36 * 4);

	m_vecIndices =
	{
		//body
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
		0, 4, 5,

		//RightWheel
		8, 9, 11,
		9, 10, 11,

		9, 13, 10,
		13, 14, 10,

		11, 10, 15,
		10, 14, 15,

		13, 12, 14,
		12, 15, 14,

		12, 8, 15,
		8, 11, 15,

		9, 8, 13,
		8, 12, 13,

		//LeftWheel

		16, 17, 19,
		17, 18, 19,

		17, 21, 18,
		21, 22, 18,

		19, 18, 23,
		18, 22, 23,

		21, 20, 22,
		20, 23, 22,

		20, 16, 23,
		16, 17, 23,

		17, 16, 21,
		16, 20, 21,

		//Cannon

		24, 25, 27,
		25, 26, 27,

		25, 29, 26,
		29, 30, 26,

		27, 26, 31,
		26, 30, 31,

		29, 28, 30,
		28, 31, 30,

		28, 24, 31,
		24, 25, 31,

		25, 24, 29,
		24, 28, 29,
	};


	for (int i = 0; i < 36*4;)
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

void CBuffer_TankCol::Update()
{
}

void CBuffer_TankCol::Render()
{
	glUseProgram(CShaderMgr::GetInstance()->GetShader(L"Shader_Normal")->GetShaderNum());
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, m_vecIndices.size(), GL_UNSIGNED_INT, (void*)0);
}

void CBuffer_TankCol::Release()
{
}

void CBuffer_TankCol::SetColor(vec3 vColor)
{
	for (int i = 0; i < 8; ++i)
		m_vecVertex[i].vColor = vColor;

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
