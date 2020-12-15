#pragma once
class CShader
{
public:
	CShader();
	~CShader();
public:
	HRESULT	Create_Shader(const char* vertexShader_FileName, const char* FragmentShader_FileName);
private:
	_int	Find_Shader(const char* pFileName, SHADER eID);
	void	Attach_Shader(_int iShaderProgram, _int iShader);
public:
	_int	GetShaderNum()const { return m_iShaderNum; }
private:
	_int	m_iShaderNum = 0;
};

