#include "stdafx.h"
#include "LCShader.h"

#include <exception>
LCShader::LCShader()
{
	
}


LCShader::~LCShader()
{
}

//vertexPath && fragPath
LCShader::LCShader(const char * vertexPath, const char * fragPath)
{
	string verCode;
	string fragCode;
	stringstream verStream;
	stringstream fragStream;
	ifstream verFile, fragFile;

	try
	{
		verFile.open(vertexPath);
		fragFile.open(fragPath);

		verStream << verFile.rdbuf();
		fragStream << fragFile.rdbuf();

		verCode = verStream.str();
		fragCode = fragStream.str();
	}
	catch (const exception &e)
	{
		cout << e.what() << endl;
	}

	const char * vertex= verCode.c_str();
	const char * fragment = fragCode.c_str();
	GLint success = 0;
	GLchar infoLog[512];

	// add and link shader 
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS,&success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::"<< infoLog << endl;
	}

	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragment, NULL);
	glCompileShader(fragShader);

	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::" << infoLog << endl;
	}

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram,fragShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 1, NULL, infoLog);
		cout << "ERROR::SHADER::LINGKING::" << infoLog << endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);
}

void LCShader::useShader()
{
	glUseProgram(shaderProgram);
}