#ifndef ROBOT_H
#define ROBOT_H

#include <epoxy/gl.h>
#include <epoxy/wgl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../ModernGDV/ModernGDV.h"
#include "Torso.h"
#include "Thigh.h"
#include "Shank.h"

class Robot
{
private:
	ModernGDV::Driver* mgdv;
	
	Torso torso;
	Thigh thigh;
	Shank shank;

public:
	explicit Robot(ModernGDV::Driver* mgdv);
	~Robot();

	void Render();
};

#endif