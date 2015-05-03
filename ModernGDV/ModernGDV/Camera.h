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

		//Ergeben sich aus obigen Variablen, sollen aber nicht andauernd neu berechnet werden müssen:
		glm::vec3 location;
		glm::mat4 skyboxTransform;
		glm::mat4 viewMat;
	public:
		Camera( Driver* mgdv );
		~Camera();

		void Update( float deltaT );
		void Render( );
	private:
		void updateViewMat();
	};
}