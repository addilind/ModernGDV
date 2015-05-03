#pragma once

#include "../../ModernGDV/OGLInc.h"

#include "../../ModernGDV/ModernGDV.h"
#include "Torso.h"
#include "Thigh.h"
#include "Shank.h"
#include "Foot.h"
#include "ShoulderJoint.h"

namespace Geometries
{
	namespace Robot
	{
		class Robot
		{
		private:
			ModernGDV::Driver* mgdv;

			Torso torso;
			Thigh thigh;
			Shank shank;
			Foot foot;
			ShoulderJoint shoulderJoint;
		public:
			explicit Robot( ModernGDV::Driver* mgdv );
			~Robot();

			void Render(const glm::mat4& transform);
		};
	}
}
