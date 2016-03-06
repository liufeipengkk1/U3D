#pragma once

#ifndef LCCAMERA_H_
#define LCCAMERA_H_

#include <iostream>
#include <vector>

#include <gl\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

using namespace std ;
using namespace glm;
using namespace std ;

enum Camera_Movement{
	FORWORD,
	BACKWARD,
	LEFT,
	RIGHT
};

const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 3.0f;
const GLfloat SENSITIVITY = 0.25f;
const GLfloat ZOOM = 45.0f;


// 控制上下左右（只用pitch 和 yaw）  放大缩小
class LCCamera
{
public:
	// camera attributes
	vec3 camPosition ;// cam pos
	vec3 camFront ; // cam front axis 
	vec3 camUp ;	// cam space up axis
	vec3 camRight; // cam space right axis
	vec3 worldUp; // world space up axis setting

	//Eular Angles
	GLfloat camPitch;
	GLfloat camYaw ;
	//GLfloat camRoll ;

	//camera option
	GLfloat camMovementSpeed ;
	GLfloat camMouseSensitivity;
	GLfloat camZoom;  // frustum fov setting

public:

	LCCamera(vec3 pos = vec3(0.0f,0.0f,0.0f),vec3 worldUp = vec3(0.0f,1.0f,0.0f),GLfloat yaw=YAW,GLfloat pitch = PITCH):camFront(vec3(0.0f,0.0f,-1.0f)),
		camMovementSpeed(SPEED),camMouseSensitivity(SENSITIVITY),camZoom(ZOOM)
	{
		this->camPosition = pos ;
		this->worldUp =worldUp;
		this->camYaw = yaw ;
		this->camPitch = pitch;

		this->updateCameraVectors();
	}

	mat4 getViewMatrix()
	{
		return lookAt(this->camPosition,this->camPosition + camFront,camUp);
	}

	void processKeyboard(Camera_Movement direction,GLfloat deltaTime)
	{
		GLfloat velocity = camMovementSpeed * deltaTime;
		if(direction == FORWORD)
			this->camPosition += this->camFront * velocity;
        if (direction == BACKWARD)
            this->camPosition -= this->camFront * velocity;
        if (direction == LEFT)
            this->camPosition -= this->camRight * velocity;
        if (direction == RIGHT)
            this->camPosition += this->camRight * velocity;
	}

	void processMouseMovement(GLfloat xoffset,GLfloat yoffset ,GLboolean constrainPitch = true)
	{
		xoffset *= this->camMouseSensitivity;
		yoffset *= this->camMouseSensitivity;

		this->camYaw += xoffset;
		this->camPitch += yoffset;

		if(constrainPitch)
		{
			if(this->camPitch >89.0f)
				this->camPitch = 89.0f;
			if(this->camPitch <-89.0)
				this->camPitch = -89.0f;
		}

		updateCameraVectors();
	}
	
	void processMouseScroll(GLfloat yoffset)
	{
		if(this->camZoom >= 1.0f && this->camZoom <= 45.0f)
			this->camZoom -= yoffset;
		else if(camZoom <= 1.0)
			camZoom = 1.0f;
		else if(camZoom >= 45.0f)
			camZoom = 45.0f;
	}

	LCCamera(void);
	~LCCamera(void);

private:
	void updateCameraVectors()
	{
		vec3 front ;
		front.x = cos(radians(camYaw));
		front.y = sin(glm::radians(camPitch));
		front.z = sin(glm::radians(camYaw)) * cos(glm::radians(camPitch));
		this->camFront = normalize(front);
		this->camRight = normalize(cross(camFront,worldUp));
		this->camUp = normalize(cross(camRight,camFront));
	}
};

#endif
