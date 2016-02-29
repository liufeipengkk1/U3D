#pragma once

#ifndef LCSHADER_H_
#define LCSHADER_H_
#include <gl\glew.h>
#include <GLFW\glfw3.h>
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;

class LCShader
{
public:
	GLuint shaderProgram;
	LCShader();
	~LCShader();

	LCShader(const char * vertexPath,const char * shaderPath);
};

#endif 
