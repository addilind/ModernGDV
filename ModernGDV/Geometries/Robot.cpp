#include "Robot.h"

Robot::Robot(ModernGDV::Driver* mgdv)
: torso(mgdv), thigh(mgdv), shank(mgdv), foot(mgdv), shoulderJoint(mgdv)
{
	this->mgdv = mgdv;
}

Robot::~Robot()
{
}

void Robot::Render()
{
	mgdv->SetSpecularProperties( glm::vec3( 0.5f, 0.5f, 0.5f ), 50.f );
	mgdv->PushTransform();
	torso.Render();

	mgdv->SetTransform( glm::translate( *mgdv->Transform(), glm::vec3( -0.2f, 0.15f, 0.f) ) ); //Linker Oberschenkel
	mgdv->SetTransform( glm::rotate( *mgdv->Transform(), static_cast<float>(glm::sin( glfwGetTime() )), glm::vec3( 1, 0, 0 ) ) );
	thigh.Render();

	mgdv->SetTransform(glm::translate(*mgdv->Transform(), glm::vec3(0.f, -0.40f, 0.f))); //Linker Unterschenkel
	//mgdv->SetTransform(glm::rotate(*mgdv->Transform(), static_cast<float>(-glm::sin(glfwGetTime())), glm::vec3(1, 0, 0)));
	shank.Render();

	
	mgdv->SetTransform(glm::translate(*mgdv->Transform(), glm::vec3(0.f, -0.4f, 0.f))); //Linker Fuß
	foot.Render();
	
	mgdv->ReloadTransform();

	mgdv->SetTransform(glm::translate(*mgdv->Transform(), glm::vec3(+0.2f, 0.15f, 0.f))); //Rechter Oberschenkel
	thigh.Render();

	mgdv->SetTransform(glm::translate(*mgdv->Transform(), glm::vec3(0.f, -0.40f, 0.f))); //Rechter Unterschenkel
	mgdv->SetTransform(glm::rotate(*mgdv->Transform(), static_cast<float>(glm::cos(glfwGetTime())), glm::vec3(1, 0, 0)));
	shank.Render();

	mgdv->SetTransform(glm::translate(*mgdv->Transform(), glm::vec3(0.f, -0.4f, 0.f))); //Rechter Fuß
	foot.Render();
	
	mgdv->ReloadTransform();

	mgdv->SetTransform(glm::translate(*mgdv->Transform(), glm::vec3(-0.375f, 0.95f, 0.f))); //Linkes Armgelenk
	mgdv->SetTransform(glm::rotate(*mgdv->Transform(), static_cast<float>(glm::sin(glfwGetTime())), glm::vec3(1, 0, 0)));
	shoulderJoint.Render();

	mgdv->SetTransform(glm::rotate(*mgdv->Transform(), glm::pi<float>()*0.5f, glm::vec3(0, 1, 0))); //Linker Oberarm 
	mgdv->SetTransform(glm::scale(*mgdv->Transform(), glm::vec3(0.5f, 0.9f, 0.7f)));
	shank.Render();

	mgdv->SetTransform(glm::translate(*mgdv->Transform(), glm::vec3(0.f, -0.40f, 0.f))); //Linker Unterarm
	thigh.Render();

	mgdv->ReloadTransform();

	mgdv->SetTransform(glm::translate(*mgdv->Transform(), glm::vec3(+0.375f, 0.95f, 0.f))); //Rechtes Armgelenk
	mgdv->SetTransform(glm::rotate(*mgdv->Transform(), static_cast<float>(glm::sin(glfwGetTime())), glm::vec3(1, 0, 0)));
	shoulderJoint.Render();

	mgdv->SetTransform(glm::rotate(*mgdv->Transform(), glm::pi<float>()*0.5f, glm::vec3(0, 1, 0)));  //Rechter Oberarm
	mgdv->SetTransform(glm::scale(*mgdv->Transform(), glm::vec3(0.5f, 0.9f, 0.7f)));
	shank.Render();

	mgdv->SetTransform(glm::translate(*mgdv->Transform(), glm::vec3(0.f, -0.40f, 0.f))); //Rechte Unterarm
	thigh.Render();

	mgdv->PopTransform();


}