#include "Camera.h"

ModernGDV::Camera::Camera( Driver* mgdv )
	:mgdv( mgdv ), skybox( mgdv ), lookAt( 0.f, 4.f, 0.f ), xzAngle( 0.f ), heightAngle( 0.f ), distance( 2.f ),
	sunXZAngle( 2.3f ), sunHeight( 0.45f ), sunColor(  1.0f, 0.937f, 0.709f )
{
	updateViewMat();
}

ModernGDV::Camera::~Camera()
{
}

void ModernGDV::Camera::Render()
{
	glEnable( GL_CULL_FACE );
	mgdv->ShaderLib.SetView( viewMat );

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glDisable( GL_DEPTH_TEST ); //Z-Buffer deaktivieren, um Sky-Cube zu zeichnen

	mgdv->ShaderLib.SetLight( glm::vec3( 0.f ), glm::vec3( 0.f ), 0.f, 1.f );//Beleuchtung für SkyBox deaktivieren
	mgdv->ShaderLib.SetSun( glm::vec3( 0.f ), glm::vec3( 0.f ) );
	mgdv->ShaderLib.SetSpecularProperties( glm::vec3( 0.f ), 1.f );

	mgdv->ShaderLib.SetModel( skyboxTransform );
	skybox.Render();

	glEnable( GL_DEPTH_TEST ); //Z-Buffer aktivieren
	mgdv->ShaderLib.SetSun( sunDirectionCam, sunColor );
}

void ModernGDV::Camera::Update( float deltaT )
{
	const float twopi = glm::two_pi<float>();
	const float heightbound = glm::pi<float>() * 0.499f;//Nicht ganz gerade von oben/unten
	const float speedUpDown = 0.75f;
	const float speedRightLeft = 1.f;
	const float speedZoom = 2.f;
	const float moveSpeed = 4.f;

	bool dirty = false;
	if (glfwGetKey(mgdv->GetWindow(), GLFW_KEY_UP))
	{
		heightAngle += speedUpDown * deltaT;
		if (heightAngle > heightbound)
			heightAngle = heightbound;
		dirty = true;
	}
	if (glfwGetKey(mgdv->GetWindow(), GLFW_KEY_DOWN))
	{
		heightAngle -= speedUpDown * deltaT;
		if (heightAngle < -heightbound)
			heightAngle = -heightbound;
		dirty = true;
	}
	if (glfwGetKey(mgdv->GetWindow(), GLFW_KEY_LEFT))
	{
		xzAngle -= speedRightLeft * deltaT;
		if (xzAngle < 0.f)
			xzAngle += twopi;
		dirty = true;
	}
	if (glfwGetKey(mgdv->GetWindow(), GLFW_KEY_RIGHT))
	{
		xzAngle += speedRightLeft * deltaT;
		if (xzAngle >= twopi)
			xzAngle -= twopi;
		dirty = true;
	}
	if (glfwGetKey(mgdv->GetWindow(), GLFW_KEY_W))
	{
		lookAt += glm::vec3(moveSpeed * -1.f * deltaT * glm::sin(xzAngle), 0.f, moveSpeed* - 1.f * deltaT * glm::cos(xzAngle));
		dirty = true;
	}
	if (glfwGetKey(mgdv->GetWindow(), GLFW_KEY_S))
	{
		lookAt += glm::vec3(moveSpeed * 1.f * deltaT * glm::sin(xzAngle), moveSpeed * 0.f, 1.f * deltaT * glm::cos(xzAngle));
		dirty = true;
	}
	if (glfwGetKey(mgdv->GetWindow(), GLFW_KEY_A))
	{
		lookAt += glm::vec3(moveSpeed * -1.f * deltaT * glm::cos(xzAngle), 0.f, moveSpeed * 1.f * deltaT * glm::sin(xzAngle));
		dirty = true;
	}
	if (glfwGetKey(mgdv->GetWindow(), GLFW_KEY_D))
	{
		lookAt += glm::vec3(moveSpeed * 1.f * deltaT * glm::cos(xzAngle), 0.f, moveSpeed * -1.f * deltaT * glm::sin(xzAngle));
		dirty = true;
	}
	if (glfwGetKey( mgdv->GetWindow(), GLFW_KEY_PAGE_UP ))
	{
		distance -= speedZoom * deltaT;
		if (distance < 0.2f)
			distance = 0.2f;
		dirty = true;
	}
	if (glfwGetKey( mgdv->GetWindow(), GLFW_KEY_PAGE_DOWN ))
	{
		distance += speedZoom * deltaT;
		if (distance > 30.f)
			distance = 30.f;
		dirty = true;
	}

	if (dirty)
		updateViewMat();
}

void ModernGDV::Camera::updateViewMat()
{
	float y = sin( heightAngle ) * distance;
	float xzRadius = cos( heightAngle ) * distance;
	float x = sin( xzAngle ) * xzRadius;
	float z = cos( xzAngle ) * xzRadius;
	const glm::vec3 up( 0.f, 1.f, 0.f );

	location = glm::vec3( x, y, z ) + lookAt;
	skyboxTransform = glm::translate( glm::mat4(), location );
	viewMat = glm::lookAt( location, lookAt, up );

	y = sin( sunHeight );
	xzRadius = cos( sunHeight );
	x = sin( sunXZAngle ) * xzRadius;
	z = cos( sunXZAngle ) * xzRadius;

	sunDirectionCam = glm::vec3( viewMat * glm::vec4( x, y, z, 0.f ) );
}