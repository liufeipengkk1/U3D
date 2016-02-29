
#include "stdafx.h"
#include <iostream>
#include <gl\glew.h>
#include <GLFW\glfw3.h>
#include <fstream>
#include <sstream>
#include "LCShader.h"
using namespace std;

const GLuint WIDTH = 800, HEIGHT = 600;
void triangle_callback(GLFWwindow * window,int key,int scanMode,int action,int mode);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Hello Triangle", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, triangle_callback);
	glewExperimental = GL_TRUE;
	glewInit();
	glViewport(0, 0, WIDTH, HEIGHT);

	// read shader
	//string verCode;
	//string fragCode;
	//stringstream verStream;
	//stringstream fragStream;
	//ifstream verFile, fragFile;

	//try
	//{
	//	verFile.open("Shader/basic.vs");
	//	fragFile.open("Shader/basic.frag");

	//	verStream << verFile.rdbuf();
	//	fragStream << fragFile.rdbuf();

	//	verCode = verStream.str();
	//	fragCode = fragStream.str();
	//}
	//catch (const exception &e)
	//{
	//	cout << e.what() << endl;
	//}

	//const char * vertex = verCode.c_str();
	//const char * fragment = fragCode.c_str();

	//cout << vertex << endl;
	//cout << fragment << endl;

	//GLint success = 0;
	//GLchar infoLog[512];

	//// add and link shader 
	//GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, &vertex, NULL);
	//glCompileShader(vertexShader);

	//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	//if (!success)
	//{
	//	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	//	cout << "ERROR::SHADER::VERTEX::" << infoLog << endl;
	//}

	//GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragShader, 1, &fragment, NULL);
	//glCompileShader(fragShader);

	//glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	//if (!success)
	//{
	//	glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
	//	cout << "ERROR::SHADER::FRAGMENT::" << infoLog << endl;
	//}

	//GLuint shaderProgram = glCreateProgram();
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragShader);
	//glLinkProgram(shaderProgram);

	//glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	//if (!success)
	//{
	//	glGetProgramInfoLog(shaderProgram, 1, NULL, infoLog);
	//	cout << "ERROR::SHADER::LINGKING::" << infoLog << endl;
	//}

	//glDeleteShader(vertexShader);
	//glDeleteShader(fragShader);

	LCShader shader("Shader/basic.vs","Shader/basic.frag");

	//vertex 
	GLfloat vertices[] = {
		// Positions         // Colors
		0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // Bottom Right
		-0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  // Bottom Left
		0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f   // Top 
	};

	//这里没有设置按位置所引
	// BUFFER Setting
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//copy data

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid *)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid *)(3*sizeof(GL_FLOAT)));

	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		
		glfwPollEvents();
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw the triangle
		glUseProgram(shader.shaderProgram);

		GLfloat timeValue = glfwGetTime();
		GLfloat redValue = (cos(timeValue) / 2) + 0.5 ;
		GLfloat greenVlue = (sin(timeValue) / 2) + 0.5;
		GLfloat blueValue = (cos(timeValue + 1) / 2) + 0.5;
		
		GLint redValueLocation = glGetUniformLocation(shader.shaderProgram, "red");
		GLint greenValueLocation = glGetUniformLocation(shader.shaderProgram, "green");
		GLint blueValueLocation = glGetUniformLocation(shader.shaderProgram, "blue");
		
		glUniform1f(redValueLocation, redValue);
		glUniform1f(greenValueLocation, greenVlue);
		glUniform1f(blueValueLocation, blueValue);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glfwTerminate();
    return 0;
}

void triangle_callback(GLFWwindow * window, int key, int scanMode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window,true);
	}
}