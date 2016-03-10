#pragma once

#ifndef SHADER
#define SHADER

//class from: http://www.learnopengl.com/code_viewer.php?type=header&code=shader

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include <gl\glew.h>
using namespace std ;

class Shader
{
public:
	GLuint Program ;
	Shader(const GLchar * vertexPath,const GLchar * fragmentPath)
	{
		ifstream vShaderFile,fShaderFile;
		string vertexCode,fragmentCode;
		stringstream vShaderStream,fShaderStream;

		try
		{
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);

			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}catch(exception & e)
		{
			cout << "read Shader error,check the shader path!" << endl;
		}
		
		const GLchar * vShaderCode = vertexCode.c_str();
		const GLchar * fShaderCode = fragmentCode.c_str();
		GLint vShaderCodeLen = vertexCode.size();
		GLint fShaderCodeLen = fragmentCode.size();

		GLuint vertex,fragment;
		GLint success;
		GLchar infoLog[512];

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex,1,&vShaderCode,&vShaderCodeLen);
		glCompileShader(vertex);
		glGetShaderiv(vertex,GL_COMPILE_STATUS,&success);
		if(!success)
		{
			glGetShaderInfoLog(vertex,512,NULL,infoLog);
			cout << vertexPath << " vertex compile error : " << infoLog << endl;
		}

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment,1,&fShaderCode,&fShaderCodeLen);
		glCompileShader(fragment);
		glGetShaderiv(fragment,GL_COMPILE_STATUS,&success);
		if(!success)
		{
			glGetShaderInfoLog(fragment,512,NULL,infoLog);
			cout << fragmentPath <<" fragment compile error : " << infoLog << endl;
		}

		createShaderProgram(vertex,fragment);

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	void Use()
	{
		glUseProgram(Program);
	}

	~Shader()
	{
		Program = -1;
	}
private:
	void createShaderProgram(GLuint vertex,GLuint fragment)
	{
		Program = glCreateProgram();
		glAttachShader(Program,vertex);
		glAttachShader(Program,fragment);
		glLinkProgram(Program);

		GLint success ;
		GLchar infoLog[512];
		glGetProgramiv(Program,GL_LINK_STATUS,&success);
		if(!success)
		{
			glGetProgramInfoLog(Program,512,NULL,infoLog);
			cout << "link program error : " << infoLog << endl;
		}
	}
};

#endif