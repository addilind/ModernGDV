#pragma once

#include "../../ModernGDV/OGLInc.h"

#include "../../ModernGDV/ModernGDV.h"
#include "Torso.h"
#include "Thigh.h"
#include "Shank.h"
#include "Foot.h"
#include "ShoulderJoint.h"
#include "ThighJoint.h"
#include "Head.h"
#include "Neck.h"
#include "Ski.h"

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
			ThighJoint thighJoint;
			Head head;
			Neck neck;
			Ski ski;


		public:
			explicit Robot( ModernGDV::Driver* mgdv );
			~Robot();

			void Render(const glm::mat4& transform);
		};
	}
}
