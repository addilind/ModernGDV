#include "Robot.h"

Robot::Robot(ModernGDV::Driver* mgdv)
: torso(mgdv), thigh(mgdv), shank(mgdv)
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

	mgdv->SetTransform( glm::translate( *mgdv->Transform(), glm::vec3( -0.2f, 0.15f, 0.f) ) ); //Linker Oberschenkel
	mgdv->SetTransform( glm::rotate( *mgdv->Transform(), static_cast<float>(glm::sin( glfwGetTime() )), glm::vec3( 1, 0, 0 ) ) );
	thigh.Render();

	mgdv->SetTransform(glm::translate(*mgdv->Transform(), glm::vec3(0.f, -0.40f, 0.f))); //Linker Unterschenkel
	mgdv->SetTransform(glm::rotate(*mgdv->Transform(), static_cast<float>(-glm::sin(glfwGetTime())), glm::vec3(1, 0, 0)));
	shank.Render();

	mgdv->ReloadTransform();

	mgdv->SetTransform(glm::translate(*mgdv->Transform(), glm::vec3(+0.2f, 0.15f, 0.f))); //Rechter Oberschenkel
	thigh.Render();

	mgdv->SetTransform(glm::translate(*mgdv->Transform(), glm::vec3(0.f, -0.40f, 0.f))); //Rechter Unterschenkel
	mgdv->SetTransform(glm::rotate(*mgdv->Transform(), static_cast<float>(glm::cos(glfwGetTime())), glm::vec3(1, 0, 0)));
	shank.Render();

	mgdv->ReloadTransform();

	mgdv->SetTransform(glm::translate(*mgdv->Transform(), glm::vec3(-0.40f, 0.95f, 0.f))); //Linker Oberarm
	mgdv->SetTransform(glm::rotate(*mgdv->Transform(), static_cast<float>(glm::sin(glfwGetTime())), glm::vec3(1, 0, 0)));
	mgdv->SetTransform(glm::rotate(*mgdv->Transform(), glm::pi<float>()*0.5f, glm::vec3(0, 1, 0)));
	mgdv->SetTransform(glm::scale(*mgdv->Transform(), glm::vec3(0.5f, 0.9f, 0.7f)));
	shank.Render();

	mgdv->SetTransform(glm::translate(*mgdv->Transform(), glm::vec3(0.f, -0.40f, 0.f))); //Linker Unterarm
	thigh.Render();

	mgdv->ReloadTransform();

	mgdv->SetTransform(glm::translate(*mgdv->Transform(), glm::vec3(+0.40f, 0.95f, 0.f))); //Linker Oberarm
	mgdv->SetTransform(glm::rotate(*mgdv->Transform(), static_cast<float>(glm::sin(glfwGetTime())), glm::vec3(1, 0, 0)));
	mgdv->SetTransform(glm::rotate(*mgdv->Transform(), glm::pi<float>()*0.5f, glm::vec3(0, 1, 0)));
	mgdv->SetTransform(glm::scale(*mgdv->Transform(), glm::vec3(0.5f, 0.9f, 0.7f)));
	shank.Render();

	mgdv->SetTransform(glm::translate(*mgdv->Transform(), glm::vec3(0.f, -0.40f, 0.f))); //Linker Unterarm
	thigh.Render();

	mgdv->PopTransform();


}