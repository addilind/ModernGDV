#include "Robot.h"

Geometries::Robot::Robot::Robot( ModernGDV::Driver* mgdv )
: torso(mgdv), thigh(mgdv), shank(mgdv), foot(mgdv), shoulderJoint(mgdv), thighJoint(mgdv), head(mgdv), neck(mgdv), ski(mgdv)
{
	this->mgdv = mgdv;
}

Geometries::Robot::Robot::~Robot()
{
}
#include <iostream>
void Geometries::Robot::Robot::setHeight(float h ){
	float tmp = (0.45f*0.45f - 0.5f*0.5f - h*h) / (-2 * 0.5f*h);
	std::cout << tmp << "\n";
	float rotationLeftThigh = glm::acos( tmp);
	float rotationLeftShank = glm::acos((h*h - 0.5f*0.5f - 0.45f*0.45f) / (-2 * 0.5f*0.45f));
	float rotationRightThigh = glm::acos((0.45f*0.45f - 0.5f*0.5f - h*h) / (-2 * 0.5f*h));
	float rotationRightShank = glm::acos((h*h - 0.5f*0.5f - 0.45f*0.45f) / (-2 * 0.5f*0.45f));
	
}

void Geometries::Robot::Robot::Render( const glm::mat4& transform )
{

	mgdv->ShaderLib.UseShader( mgdv->ShaderLib.GetShaderID( "default" ) );
	mgdv->ShaderLib.SetSpecularProperties( glm::vec3( 0.5f, 0.5f, 0.5f ), 10.f );
	mgdv->ShaderLib.SetModel( transform );
	torso.Render();

	glm::mat4 subtransform = transform; //Push

	subtransform = glm::translate( subtransform, glm::vec3( 0.f, 1.0f, 0.f ) );
	mgdv->ShaderLib.SetModel( subtransform );
	neck.Render();
	
	subtransform = glm::translate(subtransform, glm::vec3(0.f, 0.15f, 0.f));
	mgdv->ShaderLib.SetModel(subtransform);
	head.Render();
	
	subtransform = transform;

	subtransform = glm::translate( subtransform, glm::vec3( -0.25f, 0.14f, 0.f ) ); //Linkes Hüftgelenk
	subtransform = glm::rotate(subtransform, -rotationLeftThigh, glm::vec3(1, 0, 0));
	mgdv->ShaderLib.SetModel( subtransform );
	thighJoint.Render();

	
	
	mgdv->ShaderLib.SetModel(subtransform);
	thigh.Render();

	subtransform = glm::translate( subtransform, glm::vec3( 0.f, -0.40f, 0.f ) ); //Linker Unterschenkel
	subtransform = glm::rotate(subtransform, rotationLeftShank, glm::vec3(1, 0, 0));	
	mgdv->ShaderLib.SetModel( subtransform );
	shank.Render();

	subtransform = glm::translate( subtransform, glm::vec3( 0.f, -0.4f, 0.f ) ); //Linker Fuß
	mgdv->ShaderLib.SetModel( subtransform );
	foot.Render();

	subtransform = glm::translate(subtransform, glm::vec3(0.f, -0.05f, 0.f)); //Linker Ski
	subtransform = glm::scale(subtransform, glm::vec3(1.0f, 4.0f, 1.0f)); //zum Test, ob Spitzen passen
	mgdv->ShaderLib.SetModel(subtransform);
	ski.Render();

	subtransform = transform; //Pop, Push

	subtransform = glm::translate( subtransform, glm::vec3( +0.25f, 0.14f, 0.f ) ); //Rechtes Hüftgelenk
	subtransform = glm::rotate(subtransform, glm::pi<float>(), glm::vec3(0, 0, 1)); //Drehung Hüftgelenk
	mgdv->ShaderLib.SetModel( subtransform );
	thighJoint.Render();

	subtransform = glm::rotate(subtransform, glm::pi<float>(), glm::vec3(0, 0, 1));  //Rechter Oberschenkel
	mgdv->ShaderLib.SetModel( subtransform );
	thigh.Render();

	subtransform = glm::translate( subtransform, glm::vec3( 0.f, -0.40f, 0.f ) ); //Rechter Unterschenkel
	//subtransform = glm::rotate( subtransform, static_cast<float>(glm::cos( glfwGetTime() )), glm::vec3( 1, 0, 0 ) );
	mgdv->ShaderLib.SetModel( subtransform );
	shank.Render();

	subtransform = glm::translate( subtransform, glm::vec3( 0.f, -0.4f, 0.f ) ); //Rechter Fuß
	mgdv->ShaderLib.SetModel( subtransform );
	foot.Render();

	subtransform = glm::translate(subtransform, glm::vec3(0.f, -0.05f, 0.f)); //Rechter Ski
	subtransform = glm::scale(subtransform, glm::vec3(1.0f, 4.0f, 1.0f)); //zum Test, ob Spitzen passen
	mgdv->ShaderLib.SetModel(subtransform);
	ski.Render();

	subtransform = transform; //Pop, Push

	subtransform = glm::translate( subtransform, glm::vec3( -0.425, 0.95f, 0.f ) ); //Linkes Schultergelenk
	//subtransform = glm::rotate( subtransform, static_cast<float>(glm::sin( glfwGetTime() )), glm::vec3( 1, 0, 0 ) );
	mgdv->ShaderLib.SetModel( subtransform );
	shoulderJoint.Render();

	subtransform = glm::rotate( subtransform, glm::pi<float>()*0.5f, glm::vec3( 0, 1, 0 ) ); //Linker Oberarm 
	subtransform = glm::scale( subtransform, glm::vec3( 0.5f, 0.9f, 0.7f ) );
	mgdv->ShaderLib.SetModel( subtransform );
	shank.Render();

	subtransform = glm::translate( subtransform, glm::vec3( 0.f, -0.40f, 0.f ) ); //Linker Unterarm
	mgdv->ShaderLib.SetModel( subtransform );
	thigh.Render();

	subtransform = transform; //Pop

	subtransform = glm::translate( subtransform, glm::vec3( +0.425, 0.95f, 0.f ) ); //Rechtes Schultergelenk
	//subtransform = glm::rotate( subtransform, static_cast<float>(glm::sin( glfwGetTime() )), glm::vec3( 1, 0, 0 ) );
	mgdv->ShaderLib.SetModel( subtransform );
	shoulderJoint.Render();

	subtransform = glm::rotate( subtransform, glm::pi<float>()*0.5f, glm::vec3( 0, 1, 0 ) );  //Rechter Oberarm
	subtransform = glm::scale( subtransform, glm::vec3( 0.5f, 0.9f, 0.7f ) );
	mgdv->ShaderLib.SetModel( subtransform );
	shank.Render();

	subtransform = glm::translate( subtransform, glm::vec3( 0.f, -0.40f, 0.f ) ); //Rechte Unterarm
	mgdv->ShaderLib.SetModel( subtransform );
	thigh.Render();
}