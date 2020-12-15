#include "pch.h"
#include "..\Headers\Buffer_TankCol.h"
#include "Shader.h"
#include "ReadObj.h"

#define FILE_NAME		"sphere.obj"

CBuffer_TankCol::CBuffer_TankCol()
{
}


CBuffer_TankCol::~CBuffer_TankCol()
{
}

void CBuffer_TankCol::Init()
{
	ReadObj(FILE_NAME, vPosData, vNormalData, vTextureCoordinateData, indexData, vertexCount, indexCount);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(3, VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);


	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(VTXNORMAL) * 3, vPosData, GL_STATIC_DRAW);
	GLint posLocation = glGetAttribLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Normal")->GetShaderNum(), "vPos");
	glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, sizeof(_float) * 3, NULL);
	glEnableVertexAttribArray(posLocation);


	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(VTXNORMAL) * 3, vNormalData, GL_STATIC_DRAW);
	GLint normalLocation = glGetAttribLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Normal")->GetShaderNum(), "vColor");
	glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, sizeof(_float) * 3, NULL);
	glEnableVertexAttribArray(normalLocation);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(VTXNORMAL) * 2, vTextureCoordinateData, GL_STATIC_DRAW);
	GLint uvLocation = glGetAttribLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Normal")->GetShaderNum(), "vNormal");
	glVertexAttribPointer(uvLocation, 2, GL_FLOAT, GL_FALSE, sizeof(_float) * 2, NULL);
	glEnableVertexAttribArray(uvLocation);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(_uint), indexData, GL_STATIC_DRAW);
}

void CBuffer_TankCol::Update()
{
}

void CBuffer_TankCol::Render()
{
	glUseProgram(CShaderMgr::GetInstance()->GetShader(L"Shader_Normal")->GetShaderNum());
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (void*)0);
}

void CBuffer_TankCol::Release()
{
}

void CBuffer_TankCol::SetColor(vec3 vColor)
{
	for (int i = 0; i < 8; ++i)
		m_vecVertex[i].vColor = vColor;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(3, VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);


	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(VTXNORMAL) * 3, vPosData, GL_STATIC_DRAW);
	GLint posLocation = glGetAttribLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Normal")->GetShaderNum(), "vPos");
	glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, sizeof(_float) * 3, NULL);
	glEnableVertexAttribArray(posLocation);


	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(VTXNORMAL) * 3, vNormalData, GL_STATIC_DRAW);
	GLint normalLocation = glGetAttribLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Normal")->GetShaderNum(), "vColor");
	glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, sizeof(_float) * 3, NULL);
	glEnableVertexAttribArray(normalLocation);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(VTXNORMAL) * 2, vTextureCoordinateData, GL_STATIC_DRAW);
	GLint uvLocation = glGetAttribLocation(CShaderMgr::GetInstance()->GetShader(L"Shader_Normal")->GetShaderNum(), "vNormal");
	glVertexAttribPointer(uvLocation, 2, GL_FLOAT, GL_FALSE, sizeof(_float) * 2, NULL);
	glEnableVertexAttribArray(uvLocation);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(_uint), indexData, GL_STATIC_DRAW);
}
