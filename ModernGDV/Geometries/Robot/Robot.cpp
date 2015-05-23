#include "Robot.h"
#include "Dimensions.h"

Geometries::Robot::Robot::Robot( ModernGDV::Driver* mgdv )
	: frontTilt(0.5f), maxLegLength(0.8f), torso( mgdv ), thigh( mgdv ), shank( mgdv ), foot( mgdv ), shoulderJoint( mgdv ), thighJoint( mgdv ), head( mgdv ),
	neck(mgdv), ski(mgdv), mgdv(mgdv)
{
}

Geometries::Robot::Robot::Robot(const Robot& source)
	: frontTilt(source.frontTilt), maxLegLength(source.maxLegLength), torso(source.torso), thigh(source.thigh), shank(source.shank), foot(source.foot),
	shoulderJoint( source.shoulderJoint ), thighJoint( source.thighJoint ), head( source.head ), neck( source.neck ), ski( source.ski ), mgdv( source.mgdv )
{
}

Geometries::Robot::Robot::~Robot()
{
}

void Geometries::Robot::Robot::Render(  )
{
	glm::mat4 transform =
		glm::rotate(
			glm::rotate(
				glm::rotate(
					glm::translate(
						glm::mat4(),
						position + glm::vec3( 0, originHeight, 0 ) ),
					orientation,
					glm::vec3( 0, 1, 0 ) ),
				frontTilt,
				glm::vec3(1, 0, 0) ),
			tilt,
			glm::vec3( 0, 0, 1 ) );

	mgdv->ShaderLib.UseShader( mgdv->ShaderLib.GetShaderID( "default" ) );
	mgdv->ShaderLib.SetSpecularProperties( glm::vec3( 0.5f, 0.5f, 0.5f ), 10.f );

	glm::mat4 subtransform = transform; //Push


	mgdv->ShaderLib.SetModel( subtransform );
	torso.Render();

	//================================================ Kopf

	subtransform = transform; //Pop, Push

	subtransform = glm::translate( subtransform, glm::vec3( 0.f, 0.860f, 0.f ) );
	mgdv->ShaderLib.SetModel( subtransform );
	neck.Render();

	subtransform = glm::translate( subtransform, glm::vec3( 0.f, 0.15f, 0.f ) );
	mgdv->ShaderLib.SetModel( subtransform );
	head.Render();

	//================================================ Linkes Bein

	subtransform = transform; //Pop, Push

	subtransform = glm::translate( subtransform, glm::vec3( -0.5f * Dim::TOR_SCB_WIDTH, 0.f, 0.f ) ); //Linkes Hüftgelenk
	subtransform = glm::rotate( subtransform, rotationLeftLegThigh, glm::vec3( 1, 0, 0 ) );
	subtransform = glm::rotate( subtransform, glm::pi<float>(), glm::vec3( 0, 1, 0 ) ); //Drehung Hüftgelenk
	mgdv->ShaderLib.SetModel( subtransform );
	thighJoint.Render();
	subtransform = glm::rotate( subtransform, glm::pi<float>(), glm::vec3( 0, 1, 0 ) ); //Drehung zurück für die restlichen Teile

	subtransform = glm::translate( subtransform, glm::vec3( -Dim::THJ_THIGH_LOC, 0.f, 0.f ) );
	subtransform = glm::rotate( subtransform, rotationLeftLegLateral, glm::vec3( 0, 0, 1 ) ); //Linker Oberschenkel
	mgdv->ShaderLib.SetModel( subtransform );
	thigh.Render();

	subtransform = glm::translate( subtransform, glm::vec3( 0.f, -1.f*(Dim::THG_HEIGHT - Dim::THG_SHEIGHT), 0.f ) ); //Linker Unterschenkel
	subtransform = glm::rotate( subtransform, rotationLeftLegShank, glm::vec3( 1, 0, 0 ) );
	mgdv->ShaderLib.SetModel( subtransform );
	shank.Render();

	subtransform = glm::translate( subtransform, glm::vec3( 0.f, -1.f*(Dim::SNK_HEIGHT - 0.5f * Dim::FOT_HEIGHT), 0.f ) ); //Linker Fuß
	subtransform = glm::rotate( subtransform, rotationLeftLegFoot, glm::vec3( 1, 0, 0 ) );
	mgdv->ShaderLib.SetModel( subtransform );
	foot.Render();

	subtransform = glm::translate( subtransform, glm::vec3( 0.f, -0.5f * Dim::FOT_HEIGHT, 0.f ) ); //Linker Ski
	mgdv->ShaderLib.SetModel( subtransform );
	ski.Render();

	//================================================ Rechtes Bein

	subtransform = transform; //Pop, Push

	subtransform = glm::translate( subtransform, glm::vec3( 0.5f * Dim::TOR_SCB_WIDTH, 0.f, 0.f ) ); //Rechtes Hüftgelenk
	subtransform = glm::rotate( subtransform, rotationRightLegThigh, glm::vec3( 1, 0, 0 ) );
	mgdv->ShaderLib.SetModel( subtransform );
	thighJoint.Render();

	subtransform = glm::translate( subtransform, glm::vec3( Dim::THJ_THIGH_LOC, 0.f, 0.f ) );
	subtransform = glm::rotate( subtransform, rotationRightLegLateral, glm::vec3( 0, 0, 1 ) );  //Rechter Oberschenkel
	mgdv->ShaderLib.SetModel( subtransform );
	thigh.Render();

	subtransform = glm::translate( subtransform, glm::vec3( 0.f, -1.f*(Dim::THG_HEIGHT - Dim::THG_SHEIGHT), 0.f ) ); //Rechter Unterschenkel
	subtransform = glm::rotate( subtransform, rotationRightLegShank, glm::vec3( 1, 0, 0 ) );
	mgdv->ShaderLib.SetModel( subtransform );
	shank.Render();

	subtransform = glm::translate( subtransform, glm::vec3( 0.f, -1.f*(Dim::SNK_HEIGHT - 0.5f * Dim::FOT_HEIGHT), 0.f ) ); //Rechter Fuß
	subtransform = glm::rotate( subtransform, rotationRightLegFoot, glm::vec3( 1, 0, 0 ) );
	mgdv->ShaderLib.SetModel( subtransform );
	foot.Render();

	subtransform = glm::translate( subtransform, glm::vec3( 0.f, -0.5f * Dim::FOT_HEIGHT, 0.f ) ); //Rechter Ski
	mgdv->ShaderLib.SetModel( subtransform );
	ski.Render();

	//================================================ Linker Arm

	subtransform = transform; //Pop, Push

	subtransform = glm::translate( subtransform, glm::vec3( -0.425, 0.81f, 0.f ) ); //Linkes Schultergelenk
	subtransform = glm::rotate( subtransform, -rotationLeftArmFront, glm::vec3( 1, 0, 0 ) ); //rotationFront
	mgdv->ShaderLib.SetModel( subtransform );
	shoulderJoint.Render();

	subtransform = glm::rotate( subtransform, glm::pi<float>()*0.5f, glm::vec3( 0, 1, 0 ) ); //Linker Oberarm 
	subtransform = glm::rotate( subtransform, rotationLeftArmLateral, glm::vec3( 1, 0, 0 ) ); //rotationLiteral
	subtransform = glm::scale( subtransform, glm::vec3( 0.5f, 0.9f, 0.7f ) );
	mgdv->ShaderLib.SetModel( subtransform );
	shank.Render();

	subtransform = glm::translate( subtransform, glm::vec3( 0.f, -0.40f, 0.f ) ); //Linker Unterarm
	subtransform = glm::rotate( subtransform, rotationLeftArmLower, glm::vec3( 1, 0, 0 ) ); //rotationLowerArm
	mgdv->ShaderLib.SetModel( subtransform );
	thigh.Render();

	//================================================ Rechter Arm

	subtransform = transform; //Pop

	subtransform = glm::translate( subtransform, glm::vec3( +0.425, 0.81f, 0.f ) ); //Rechtes Schultergelenk
	subtransform = glm::rotate(subtransform, -rotationRightArmFront, glm::vec3(1, 0, 0)); //rotationFront
	mgdv->ShaderLib.SetModel( subtransform );
	shoulderJoint.Render();

	subtransform = glm::rotate( subtransform, glm::pi<float>()*0.5f, glm::vec3( 0, 1, 0 ) );  //Rechter Oberarm
	subtransform = glm::rotate(subtransform, rotationRightArmLateral, glm::vec3(1, 0, 0)); //rotationLiteral
	subtransform = glm::scale( subtransform, glm::vec3( 0.5f, 0.9f, 0.7f ) );
	mgdv->ShaderLib.SetModel( subtransform );
	shank.Render();

	subtransform = glm::translate( subtransform, glm::vec3( 0.f, -0.40f, 0.f ) ); //Rechter Unterarm
	subtransform = glm::rotate(subtransform, rotationRightArmLower, glm::vec3(1, 0, 0)); //rotationLowerArm
	mgdv->ShaderLib.SetModel( subtransform );
	thigh.Render();
}

void Geometries::Robot::Robot::SetLeftLeg( const float& length, const float& rotationFront, const float& rotationLateral, const float& rotationFoot )
{
	rotationLeftLegLateral = -rotationLateral;
	static const float effectiveShank = (Dim::SNK_HEIGHT - 0.5f * Dim::FOT_HEIGHT);
	static const float effectiveTigh = (Dim::THG_HEIGHT - Dim::THG_SHEIGHT);
	rotationLeftLegThigh = -glm::acos( (effectiveShank * effectiveShank - effectiveTigh * effectiveTigh - length*length) / (-2 * effectiveTigh * length) ) - rotationFront;
	rotationLeftLegShank = glm::pi<float>() - glm::acos( (length*length - effectiveTigh*effectiveTigh - effectiveShank*effectiveShank) / (-2 * effectiveTigh*effectiveShank) );
	rotationLeftLegFoot = rotationFoot - rotationLeftLegThigh - rotationLeftLegShank;
}

void Geometries::Robot::Robot::SetRightLeg( const float& length, const float& rotationFront, const float& rotationLateral, const float& rotationFoot )
{
	rotationRightLegLateral = -rotationLateral;
	static const float effectiveShank = (Dim::SNK_HEIGHT - 0.5f * Dim::FOT_HEIGHT); //Länge vom Bein ohne Gelenküberschneidung
	static const float effectiveTigh = (Dim::THG_HEIGHT - Dim::THG_SHEIGHT);
	rotationRightLegThigh = -glm::acos( (effectiveShank * effectiveShank - effectiveTigh * effectiveTigh - length*length) / (-2 * effectiveTigh * length) ) - rotationFront;
	rotationRightLegShank = glm::pi<float>() - glm::acos( (length*length - effectiveTigh*effectiveTigh - effectiveShank*effectiveShank) / (-2 * effectiveTigh*effectiveShank) );
	rotationRightLegFoot = rotationFoot - rotationRightLegThigh - rotationRightLegShank;
}

void Geometries::Robot::Robot::SetLeftArm( const float& rotationFront, const float& rotationLateral, const float& rotationLowerArm )
{
	rotationLeftArmFront = rotationFront;
	rotationLeftArmLateral = rotationLateral;
	rotationLeftArmLower = rotationLowerArm;
}

void Geometries::Robot::Robot::SetRightArm(const float& rotationFront, const float& rotationLateral, const float& rotationLowerArm)
{
	rotationRightArmFront = rotationFront;
	rotationRightArmLateral = -rotationLateral;
	rotationRightArmLower = -rotationLowerArm;
}

void Geometries::Robot::Robot::SetTilt( const float& tilt )
{
	this->tilt = -tilt;
	float heightOuterThigh = maxLegLength * glm::cos( 1.3f * glm::abs( tilt ) ); //Höhe von äußerer Hüfte
	float xDiffTigh = 0.5f * Dim::TOR_SCB_WIDTH + Dim::THJ_THIGH_LOC; 
	originHeight = heightOuterThigh - xDiffTigh * glm::sin( glm::abs( tilt ) );
	float heightInnerThigh = originHeight - xDiffTigh * glm::sin( glm::abs( tilt ) );
	float lengthInnerLeg = heightInnerThigh / glm::cos( 0.3f * glm::abs( tilt ) );

	if (tilt > 0)
	{ //Nach rechts neigen
		SetLeftLeg( maxLegLength, 0.5f, 0.3f * glm::abs( tilt ), -0.27f ); //Außen
		SetRightLeg( lengthInnerLeg, 0.5f, -0.3f * glm::abs( tilt ), -0.27f ); //Innen
	}
	else
	{
		SetRightLeg( maxLegLength, 0.5f, -0.3f * glm::abs( tilt ), -0.27f ); //Außen
		SetLeftLeg( lengthInnerLeg, 0.5f, 0.3f * glm::abs( tilt ), -0.27f ); //Innen
	}

}

void Geometries::Robot::Robot::SetOrientation(const float& orient)
{
	orientation = orient;
}

void Geometries::Robot::Robot::SetPosition(const glm::vec3& pos)
{
	position = pos;
}