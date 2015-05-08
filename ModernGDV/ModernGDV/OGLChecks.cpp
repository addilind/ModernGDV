#include "OGLChecks.h"
#include <iostream>

void ModernGDV::CheckRequiredOGLFeatures()
{
	if (!epoxy_has_gl_extension("GL_EXT_texture_compression_s3tc"))
		std::clog << "S3TC texture compression not available, please update your drivers!" << std::endl;
}