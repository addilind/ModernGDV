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

	/*mgdv->SetTransform( glm::translate( *mgdv->Transform(), glm::vec3( -0.2f, 0.15f, 0.f) ) ); //Linker Oberschenkel
	mgdv->SetTransform( glm::rotate( *mgdv->Transform(), static_cast<float>(glm::sin( glfwGetTime() )), glm::vec3( 1, 0, 0 ) ) );
	thigh.Render();

	mgdv->AddTransform(glm::translate(glm::mat4(), glm::vec3(0.f, -0.40f, 0.f))); //Linker Unterschenkel
	mgdv->AddTransform(glm::rotate(glm::mat4(), static_cast<float>(-glm::sin(glfwGetTime())), glm::vec3(1, 0, 0)));
	shank.Render();

	mgdv->ReloadTransform();

	mgdv->AddTransform(glm::translate(glm::mat4(), glm::vec3(+0.2f, 0.15f, 0.f))); //Rechter Oberschenkel
	thigh.Render();

	mgdv->AddTransform(glm::translate(glm::mat4(), glm::vec3(0.f, -0.40f, 0.f))); //Rechter Unterschenkel
	mgdv->AddTransform(glm::rotate(glm::mat4(), static_cast<float>(glm::cos(glfwGetTime())), glm::vec3(1, 0, 0)));
	shank.Render();*/

	mgdv->PopTransform();
}