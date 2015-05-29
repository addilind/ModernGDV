#pragma once

#include "../Geometries/Skybox.h"

namespace ModernGDV
{
	class Camera
	{
	private:
		Driver* mgdv;
		Geometries::Skybox skybox;
		glm::vec3 lookAt;

		float xzAngle;
		float heightAngle;
		float distance;

		float sunXZAngle;
		float sunHeight;
		glm::vec3 sunColor;

		//Ergeben sich aus obigen Variablen, sollen aber nicht andauernd neu berechnet werden müssen:
		glm::vec3 location;
		glm::mat4 skyboxTransform;
		glm::mat4 viewMat;
		glm::vec3 sunDirectionCam;//Richtung der Lichtstrahlen im Kamerakoordinatensystem
	public:
		Camera( Driver* mgdv );
		~Camera();

		void Update( float deltaT );
		void Render( );
		glm::vec3 GetLocation();
		glm::vec3 GetLookAt();
	private:
		void updateViewMat();
	};
}