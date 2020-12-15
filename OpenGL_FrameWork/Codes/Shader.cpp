#include "pch.h"
#include "..\Headers\Shader.h"


CShader::CShader()
{
}


CShader::~CShader()
{
}

HRESULT CShader::Create_Shader(const char* vertexShader_FileName, const char* FragmentShader_FileName)
{
	int iVertexShader = Find_Shader(vertexShader_FileName, SHADER_VERTEX);
	int iFragmentShader = Find_Shader(FragmentShader_FileName, SHADER_FRAGMENT);

	m_iShaderNum = glCreateProgram();

	Attach_Shader(m_iShaderNum, iVertexShader);
	Attach_Shader(m_iShaderNum, iFragmentShader);

	return S_OK;
}

_int CShader::Find_Shader(const char * pFileName, SHADER eID)
{
	string strShader = "";
	ifstream FileShader(pFileName);

	while (FileShader.good())
	{
		string line;
		getline(FileShader, line);
		strShader.append(line + "\n");
	}

	GLchar const*	pShader_Source = strShader.c_str();
	GLint			iShader_Length = strShader.length();

	GLuint glShader;
	if (eID == SHADER_VERTEX)
		glShader = glCreateShader(GL_VERTEX_SHADER);
	else if (eID == SHADER_FRAGMENT)
		glShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(glShader, 1, &pShader_Source, &iShader_Length);
	glCompileShader(glShader);

	GLint	iResult;
	GLchar	szErrLog[512] = {};
	glGetShaderiv(glShader, GL_COMPILE_STATUS, &iResult);
	if (!iResult)
	{
		glGetShaderInfoLog(glShader, 512, nullptr, szErrLog);
		if (eID == SHADER_VERTEX)
			cout << "Error: VertexShader Compile Failed" << endl << szErrLog << endl;
		if (eID == SHADER_FRAGMENT)
			cout << "Error: FragmentShader Compile Failed" << endl << szErrLog << endl;
		return false;
	}
	FileShader.close();
	return glShader;
}

void CShader::Attach_Shader(_int iShaderProgram, _int iShader)
{
	glAttachShader(iShaderProgram, iShader);
	glLinkProgram(iShaderProgram);
	glDeleteShader(iShader);

	GLint iResult;
	GLchar	szErrLog[512] = {};
	glGetProgramiv(iShaderProgram, GL_LINK_STATUS, &iResult);
	if (!iResult)
	{
		glGetProgramInfoLog(iShaderProgram, 512, nullptr, szErrLog);
		cerr << "Errer: Shader Program DisConnected" << endl << szErrLog << endl;
		return;
	}
}
