#pragma once
class CBuffer
{
public:
	CBuffer();
	virtual ~CBuffer();
public:
	virtual void Init()PURE;
	virtual void Init(const _tchar* pHeightMap, const _float& fInterval);
	virtual void Update()PURE;
	virtual void Render()PURE;
	virtual void Release()PURE;
protected:
	int		m_iNumVertices = 0;
	int		m_iNumPolygons = 0;
	GLuint  VBO[3];
	GLuint	VAO = 0, VBO_Pos = 0, VBO_Col = 0;
	GLuint	VBO_UV = 0, VBO_NORMAL;
	GLuint	EBO = 0;
};

