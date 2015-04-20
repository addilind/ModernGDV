#include "Robot.h"

Robot::Robot(ModernGDV::ModernGDV* mgdv)
{
	this->mgdv = mgdv;
}

Robot::~Robot()
{
}

void Robot::Render()
{
	mgdv->PushTransform();
	torso.Render();

	mgdv->AddTransform( glm::translate( glm::mat4(), glm::vec3( -0.2f, 0.2f, 0.f) ) ); //Linker Oberschenkel
	thigh.Render();

	mgdv->PopTransform();
}