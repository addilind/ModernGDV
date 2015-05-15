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

			glm::vec3 position;

			float tilt;
			float orientation;
			float frontTilt;
			float maxLegLength;
			float originHeight;
			
			float rotationLeftLegLateral;
			float rotationLeftLegThigh;
			float rotationLeftLegShank;
			float rotationLeftLegFoot;
			float rotationRightLegLateral;
			float rotationRightLegThigh;
			float rotationRightLegShank;
			float rotationRightLegFoot;
			float rotationLeftArmFront;
			float rotationLeftArmLateral;
			float rotationLeftArmLower;

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

			void Render();

			void SetLeftLeg(const float& length, const float& rotationFront, const float& rotationLateral, const float& rotationFoot );
			void SetRightLeg(const float& length, const float& rotationFront, const float& rotationLateral, const float& rotationFoot);
			void SetLeftArm(const float& rotationFront, const float& rotationLateral, const float& rotationLowerArm);

			void SetTilt( const float& tilt );
			void SetOrientation( const float& orient );
			void SetPosition( const glm::vec3& pos );
		};
	}
}
