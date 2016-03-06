

// identify 
//
#include "stdafx.h"
//
//#include <gl\glew.h>
//#include <GLFW\glfw3.h>
//
//#include <SOIL\SOIL.h>
//#include <glm\glm.hpp>
//#include <glm\gtc\matrix_transform.hpp>
//#include <glm\gtc\type_ptr.hpp>
//
//#include "LCShader.h"
//using namespace std;
//using namespace glm;
//
//void createCam_callback(GLFWwindow * window,int key,int scancode,int action,int mode);
//
//const GLuint WIDTH = 800,HEIGHT = 600;
//int shaderControlVal = 0 ;
//GLfloat pos_x= -0.5f,pos_y = -0.5f,pos_z = -0.5f;
//
//
//int main()
//{
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
//	 glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//
//    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
//    glfwMakeContextCurrent(window);
//	glfwSetKeyCallback(window,createCam_callback);
//
//	glewExperimental = GL_TRUE;
//	glewInit();
//    glViewport(0, 0, WIDTH, HEIGHT);
//	LCShader shader("Shader/glmFuctionTst.vs","Shader/glmFuctionTst.frag");
//
//	 GLfloat vertices[] = {
//     -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//
//	
//    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
//    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
//    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//    };
//
//	 GLuint VBO, VAO;
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//
//    glBindVertexArray(VAO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//    // Position attribute
//	glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
//    // TexCoord attribute
//	glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//
//    glBindVertexArray(0); // Unbind VAO
//
//	GLuint texture0;
//	glGenTextures(1, &texture0);
//    glBindTexture(GL_TEXTURE_2D, texture0); 
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//    int width, height;
//    unsigned char* image = SOIL_load_image("Pic/another woman.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
//    glGenerateMipmap(GL_TEXTURE_2D);
//    SOIL_free_image_data(image);
//    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
//
//	glEnable(GL_DEPTH_TEST);
//	//因为投影矩阵几乎不变，所以写在外头
//	mat4 projection;
//	projection = perspective(45.0f,(GLfloat)WIDTH/(GLfloat)HEIGHT,0.1f,100.0f);
//	GLuint proLoc = glGetUniformLocation(shader.shaderProgram,"projection");
//
//	vec3 cubePositions[] = {
//        glm::vec3( 0.0f,  0.0f,  0.0f),
//        glm::vec3( 2.0f,  5.0f, -15.0f),
//        glm::vec3(-1.5f, -2.2f, -2.5f),
//        glm::vec3(-3.8f, -2.0f, -12.3f),
//        glm::vec3( 2.4f, -0.4f, -3.5f),
//        glm::vec3(-1.7f,  3.0f, -7.5f),
//        glm::vec3( 1.3f, -2.0f, -2.5f),
//        glm::vec3( 1.5f,  2.0f, -2.5f),
//        glm::vec3( 1.5f,  0.2f, -1.5f),
//        glm::vec3(-1.3f,  1.0f, -1.5f)
//    };
//		
//	while(!glfwWindowShouldClose(window))
//	{
//		glfwPollEvents();
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D,texture0);
//		glUniform1i(glGetUniformLocation(shader.shaderProgram,"texture0"),0);
//
//		//mat4 transform;
//		//transform = translate(transform,vec3(pos_x, pos_y, pos_z)); // 移动的也是局部坐标 也就是说相对于自身的方向。。 先旋后移还是先移后旋问题需要考虑清楚
//		//transform = rotate(transform,  (GLfloat)glfwGetTime() , vec3(1.0f, 1.0f, 1.0f));  //绕局部坐标旋转 
//
//		glm::mat4 view;
//        GLfloat radius = 10.0f;
//        GLfloat camX = sin(glfwGetTime()) * radius;
//        GLfloat camZ = cos(glfwGetTime()) * radius;
//        view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//		
//		//transform = view * transform ;
//
//		GLuint tranformLoc = glGetUniformLocation(shader.shaderProgram,"transform");
//		//glUniformMatrix4fv(tranformLoc,1,GL_FALSE,value_ptr(transform));
//		glUniformMatrix4fv(proLoc,1,GL_FALSE,value_ptr(projection));
//
//		
//
//		glUseProgram(shader.shaderProgram);  
//
//		glBindVertexArray(VAO);
//		/*glDrawArrays(GL_TRIANGLES,0,36);*/
//
//		for (GLuint i = 0; i < 10; i++)
//        {
//            // Calculate the model matrix for each object and pass it to shader before drawing
//            mat4 transform;
//            transform = translate(transform, cubePositions[i]);
//            //GLfloat angle = 20.0f * i;
//           // transform = rotate(transform, angle, vec3(1.0f, 0.3f, 0.5f));
//			transform = view * transform ;
//            glUniformMatrix4fv(tranformLoc, 1, GL_FALSE, value_ptr(transform));
//
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//        }
//		glBindVertexArray(0);
//
//		glfwSwapBuffers(window);
//	}
//
//	glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//	glDeleteProgram(shader.shaderProgram);
//    glfwTerminate();
//
//	return 0 ;
//}
//
//void createCam_callback(GLFWwindow * window,int key,int scancode,int action,int mode)
//{
//	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//	{
//		glfwSetWindowShouldClose(window,true);
//	}
//	else if(key == GLFW_KEY_Z && action == GLFW_PRESS)
//	{
//		shaderControlVal = 1;
//	}
//	else if(key == GLFW_KEY_X && action == GLFW_PRESS)
//	{
//		shaderControlVal = 0 ;
//	}
//	else if(key == GLFW_KEY_W && action == GLFW_PRESS)
//	{
//		pos_y += 0.1f;
//	}
//	else if(key == GLFW_KEY_A && action == GLFW_PRESS)
//	{
//		pos_x -= 0.1f;
//	}
//	else if(key == GLFW_KEY_S && action == GLFW_PRESS)
//	{
//		pos_y -= 0.1f;
//	}
//	else if(key == GLFW_KEY_D && action == GLFW_PRESS)
//	{
//		pos_x += 0.1f;
//	}
//	else if(key == GLFW_KEY_J && action == GLFW_PRESS)
//	{
//		pos_z += 0.1f;
//	}
//	else if(key == GLFW_KEY_K && action == GLFW_PRESS)
//	{
//		pos_z -= 0.1f;
//	}
//}
