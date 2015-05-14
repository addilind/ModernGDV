namespace Geometries
{
	namespace Robot
	{
		namespace Dim
		{
			//TORSO
			static const float TOR_LOWEST = -0.14f;
			static const float TOR_PYR_HEIGHT = 0.10f; //Bottom pyramid
			static const float TOR_PYR_WIDTH = 0.20f;
			static const float TOR_PYR_DEPTH = 0.16f;
			static const float TOR_SCB_HEIGHT = 0.15f; //Bottom small cuboid
			static const float TOR_SCB_WIDTH = 0.20f;
			static const float TOR_SCB_DEPTH = 0.20f;
			static const float TOR_TPR_HEIGHT = 0.20f; //Truncated pyramid
			static const float TOR_TPR_BWIDTH = 0.40f; //Bottom
			static const float TOR_TPR_BDEPTH = 0.24f;
			static const float TOR_TPR_TWIDTH = 0.50f; //Top
			static const float TOR_TPR_TDEPTH = 0.26f;
			static const float TOR_BCB_HEIGHT = 0.55f; //Big cuboid
			static const float TOR_BCB_WIDTH = 0.70f;
			static const float TOR_BCB_DEPTH = 0.30f;

			//THIGH
			static const float THG_DEPTH = 0.15f;

			//THIGH JOINT
			static const float THJ_HEIGHT = 0.1f;
			static const float THJ_WIDTH = 0.1875f;
			static const float THJ_IWIDTH = 0.05f; //Inner width
			static const float THJ_DEPTH = 0.25f;
			static const float THJ_IDEPTH = THG_DEPTH; //Inner depth
			static const float THJ_THIGH_LOC = 0.15f;
		}
	}
}
