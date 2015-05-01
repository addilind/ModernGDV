#pragma once

#include "../Geometries/Skybox.h"

namespace ModernGDV
{
	class Camera
	{
	private:
		Driver* mgdv;
		Skybox skybox;
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

		void Run(float deltaT);
	private:
		void updateViewMat();
	};
}