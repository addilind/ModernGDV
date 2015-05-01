#ifndef MGDV_TEXTURES_DDSDEFS_H
#define MGDV_TEXTURES_DDSDEFS_H
#include <stdint.h>

namespace ModernGDV
{
	namespace Textures
	{
		struct DDS_PIXELFORMAT {
			enum FourCC : uint32_t {
				DXT1 = 0x31545844, // "DXT1" in ASCII
				DXT3 = 0x33545844, // "DXT3" in ASCII
				DXT5 = 0x35545844  // "DXT5" in ASCII
			};
			uint32_t Size;
			uint32_t Flags;
			FourCC   FourCC;
			uint32_t RGBBitCount;
			uint32_t RBitMask;
			uint32_t GBitMask;
			uint32_t BBitMask;
			uint32_t ABitMask;
		};
		struct DDS_HEADER {
			enum Flag : uint32_t {
				DDSD_CAPS = 0x1,
				DDSD_HEIGHT = 0x2,
				DDSD_WIDTH = 0x4,
				DDSD_PITCH = 0x8,
				DDSD_PIXELFORMAT = 0x1000,
				DDSD_MIPMAPCOUNT = 0x20000,
				DDSD_LINEARSIZE = 0x80000,
				DDSD_DEPTH = 0x800000
			};

			//Size of structure. This member must be set to 124.
			uint32_t          Size;
			//Flags to indicate which members contain valid data. 
			Flag              Flags;
			//Surface height (in pixels).
			uint32_t          Height;
			//Surface width (in pixels).
			uint32_t          Width;
			//The pitch or number of bytes per scan line in an uncompressed texture; the total number of bytes in the top level texture for a compressed texture.
			uint32_t          PitchOrLinearSize;
			//Depth of a volume texture (in pixels), otherwise unused. 
			uint32_t          Depth;
			//Number of mipmap levels, otherwise unused.
			uint32_t          MipMapCount;
			uint32_t          Reserved1[11];
			//The pixel format.
			DDS_PIXELFORMAT   ddspf;
			uint32_t          Caps;
			uint32_t          Caps2;
			uint32_t          Caps3;
			uint32_t          Caps4;
			uint32_t          Reserved2;
		};
	}
}

#endif