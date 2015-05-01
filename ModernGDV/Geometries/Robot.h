#ifndef ROBOT_H
#define ROBOT_H

#include <epoxy/gl.h>
#include <epoxy/wgl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../ModernGDV/ModernGDV.h"
#include "Robot/Torso.h"
#include "Robot/Thigh.h"
#include "Robot/Shank.h"
#include "Robot/Foot.h"
#include "Robot/ShoulderJoint.h"

class Robot
{
private:
	ModernGDV::Driver* mgdv;
	
	Torso torso;
	Thigh thigh;
	Shank shank;
	Foot foot;
	ShoulderJoint shoulderJoint;
public:
	explicit Robot(ModernGDV::Driver* mgdv);
	~Robot();

	void Render();
};

#endif