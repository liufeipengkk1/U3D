

#include "stdafx.h"
#include <gl\glew.h>
#include <GLFW\glfw3.h>
#include <SOIL\SOIL.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <iostream>
#include "LCShader.h"
#include "LCCamera.h"
using namespace std ;
using namespace glm;

//callback Func
void colorKey_callback(GLFWwindow * window,int key,int scancode,int action,int mode);
void colorMouse_callback(GLFWwindow * window,double xpos,double ypos);
void colorScroll_callback(GLFWwindow * window,double xoffset,double yoffset);
void do_movement();
//window
const GLuint WIDTH = 800,HEIGHT=600;
//camera
LCCamera camera(vec3(0.0,0.0f,-3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT/2.0f;

bool keys[1024] ;

vec3 lightPos(1.2,2.0f,2.0);

//DeltaTime
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

int main()
{
	  glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window,colorKey_callback);
	glfwSetCursorPosCallback(window,colorMouse_callback);
	glfwSetScrollCallback(window,colorScroll_callback);

	 // GLFW Options
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;
    glewInit();
    glViewport(0, 0, WIDTH, HEIGHT);
    // OpenGL options
    glEnable(GL_DEPTH_TEST);

	// read shader
	// diffuse shader
	/*LCShader lightingShader("Shader/basicLighting.vs","Shader/basicLighting.frag");
	LCShader lampShader("Shader/lamp.vs", "Shader/lamp.frag");*/
	//specular shader
	LCShader lightingShader("Shader/specularLighting.vs","Shader/specularLighting.frag");
	LCShader lampShader("Shader/lamp.vs", "Shader/lamp.frag");
	 GLfloat vertices[] = {
         -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

	GLuint VBO, containerVAO;
    glGenVertexArrays(1, &containerVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(containerVAO);

    // Position attribute
	glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);

	glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 *sizeof(GLfloat)));
    glBindVertexArray(0);

	GLuint lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    // We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Set the vertex attributes (only position data for the lamp))
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
	
	while(!glfwWindowShouldClose(window))
	{
		// Calculate deltatime of current frame
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        do_movement();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glUseProgram(lightingShader.shaderProgram);
		GLint objectColorLoc = glGetUniformLocation(lightingShader.shaderProgram, "objectColor");
        GLint lightColorLoc  = glGetUniformLocation(lightingShader.shaderProgram, "lightColor");
		GLint lightPosLoc = glGetUniformLocation(lightingShader.shaderProgram,"lightPos");
		GLint viewPosLoc     = glGetUniformLocation(lightingShader.shaderProgram, "viewPos");

        glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
        glUniform3f(lightColorLoc,  1.0f, 0.5f, 1.0f);
		glUniform3f(lightPosLoc,lightPos.x,lightPos.y,lightPos.z);
		glUniform3f(viewPosLoc,camera.camPosition.x,camera.camPosition.y,camera.camPosition.z);

		glm::mat4 view;
        view = camera.getViewMatrix();
		glm::mat4 projection = perspective(camera.camZoom, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
        GLint tranlLoc = glGetUniformLocation(lightingShader.shaderProgram, "transform");
        GLint viewLoc  = glGetUniformLocation(lightingShader.shaderProgram,  "view");
        GLint projLoc  = glGetUniformLocation(lightingShader.shaderProgram,  "projection");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glBindVertexArray(containerVAO);
        glm::mat4 transform;
        glUniformMatrix4fv(tranlLoc, 1, GL_FALSE, glm::value_ptr(transform));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

		  // Also draw the lamp object, again binding the appropriate shader
		glUseProgram(lampShader.shaderProgram);
        // Get location objects for the matrices on the lamp shader (these could be different on a different shader)
        tranlLoc = glGetUniformLocation(lampShader.shaderProgram, "transform");
        viewLoc  = glGetUniformLocation(lampShader.shaderProgram, "view");
        projLoc  = glGetUniformLocation(lampShader.shaderProgram, "projection");
        // Set matrices
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        transform = glm::mat4();
        transform = glm::translate(transform, lightPos);
        transform = glm::scale(transform, glm::vec3(0.2f)); // Make it a smaller cube
        glUniformMatrix4fv(tranlLoc, 1, GL_FALSE, glm::value_ptr(transform));
        // Draw the light object (using light's vertex attributes)
        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        // Swap the screen buffers
        glfwSwapBuffers(window);
	}
	
	glDeleteVertexArrays(1,&containerVAO);
	glDeleteVertexArrays(1,&lightVAO);
	glDeleteBuffers(1,&VBO);
	glDeleteProgram(lightingShader.shaderProgram);
	glDeleteProgram(lightingShader.shaderProgram);

	return 0 ;
}



void colorKey_callback(GLFWwindow * window,int key,int scancode,int action,int mode)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window,true);
	if(key >-1 && key < 1024)
	{
		if(action == GLFW_PRESS)
			keys[key] = true;
		else if(action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void do_movement()
{
	if(keys[GLFW_KEY_W])
		camera.processKeyboard(FORWARD,deltaTime);
	if(keys[GLFW_KEY_S])
		camera.processKeyboard(BACKWARD,deltaTime);
	if(keys[GLFW_KEY_A])
		camera.processKeyboard(LEFT,deltaTime);
	if(keys[GLFW_KEY_D])
		camera.processKeyboard(RIGHT,deltaTime);
}

bool firstMouse = true ;
void colorMouse_callback(GLFWwindow * window,double xpos,double ypos)
{
	if(firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false ;
	}

	GLfloat xoffset = xpos - lastX ;
	GLfloat yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	
	camera.processMouseMovement(xoffset,yoffset);
}
void colorScroll_callback(GLFWwindow * window,double xoffset,double yoffset)
{
	camera.processMouseScroll(yoffset);
}