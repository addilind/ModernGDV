#include "Robot.h"

Geometries::Robot::Robot::Robot( ModernGDV::Driver* mgdv )
	: torso( mgdv ), thigh( mgdv ), shank( mgdv ), foot( mgdv ), shoulderJoint( mgdv )
{
	this->mgdv = mgdv;
}

Geometries::Robot::Robot::~Robot()
{
}

void Geometries::Robot::Robot::Render( const glm::mat4& transform )
{

	mgdv->ShaderLib.UseShader( mgdv->ShaderLib.GetShaderID( "default" ) );
	mgdv->ShaderLib.SetSpecularProperties( glm::vec3( 0.5f, 0.5f, 0.5f ), 50.f );
	mgdv->ShaderLib.SetModel( transform );
	torso.Render();

	glm::mat4 subtransform = transform; //Push
	subtransform = glm::translate( subtransform, glm::vec3( -0.2f, 0.15f, 0.f ) ); //Linker Oberschenkel
	subtransform = glm::rotate( subtransform, static_cast<float>(glm::sin( glfwGetTime() )), glm::vec3( 1, 0, 0 ) );
	mgdv->ShaderLib.SetModel( subtransform );
	thigh.Render();

	subtransform = glm::translate( subtransform, glm::vec3( 0.f, -0.40f, 0.f ) ); //Linker Unterschenkel
	shank.Render();

	subtransform = glm::translate( subtransform, glm::vec3( 0.f, -0.4f, 0.f ) ); //Linker Fuﬂ
	foot.Render();

	subtransform = transform; //Pop, Push

	subtransform = glm::translate( subtransform, glm::vec3( +0.2f, 0.15f, 0.f ) ); //Rechter Oberschenkel
	thigh.Render();

	subtransform = glm::translate( subtransform, glm::vec3( 0.f, -0.40f, 0.f ) ); //Rechter Unterschenkel
	subtransform = glm::rotate( subtransform, static_cast<float>(glm::cos( glfwGetTime() )), glm::vec3( 1, 0, 0 ) );
	shank.Render();

	subtransform = glm::translate( subtransform, glm::vec3( 0.f, -0.4f, 0.f ) ); //Rechter Fuﬂ
	foot.Render();

	subtransform = transform; //Pop, Push

	subtransform = glm::translate( subtransform, glm::vec3( -0.375f, 0.95f, 0.f ) ); //Linkes Schultergelenk
	subtransform = glm::rotate( subtransform, static_cast<float>(glm::sin( glfwGetTime() )), glm::vec3( 1, 0, 0 ) );
	shoulderJoint.Render();

	subtransform = glm::rotate( subtransform, glm::pi<float>()*0.5f, glm::vec3( 0, 1, 0 ) ); //Linker Oberarm 
	subtransform = glm::scale( subtransform, glm::vec3( 0.5f, 0.9f, 0.7f ) );
	shank.Render();

	subtransform = glm::translate( subtransform, glm::vec3( 0.f, -0.40f, 0.f ) ); //Linker Unterarm
	thigh.Render();

	subtransform = transform; //Pop

	subtransform = glm::translate( subtransform, glm::vec3( +0.375f, 0.95f, 0.f ) ); //Rechtes Schultergelenk
	subtransform = glm::rotate( subtransform, static_cast<float>(glm::sin( glfwGetTime() )), glm::vec3( 1, 0, 0 ) );
	shoulderJoint.Render();

	subtransform = glm::rotate( subtransform, glm::pi<float>()*0.5f, glm::vec3( 0, 1, 0 ) );  //Rechter Oberarm
	subtransform = glm::scale( subtransform, glm::vec3( 0.5f, 0.9f, 0.7f ) );
	shank.Render();

	subtransform = glm::translate( subtransform, glm::vec3( 0.f, -0.40f, 0.f ) ); //Rechte Unterarm
	thigh.Render();


}