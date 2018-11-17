/*****************************************************************************
*
* image-formats.h
*
* By Jari Korkala 4/2013
*
* File created as part of project refactoring.
*
*****************************************************************************/

#ifndef _CENG_IMAGE_FORMATS_H
#define _CENG_IMAGE_FORMATS_H

namespace Ceng
{
	namespace IMAGE_FORMAT
	{ 
		enum value
		{
			UNKNOWN = 0 , // User defined data
		
			//***************************
			// Depth-stencil formats
		
			D16 = 1 , // Pseudo-depth as 0.16 fixed point
			D16_S8 = 2 , // With 8-bit stencil
			D16_S16 = 3 , // With 16-bit stencil
		
			D24_S8 = 4 , // With 8-bit stencil
			D24_S16 = 5 , // With 16-bit stencil
		
			D32F = 6 , // Pseudo-depth as FLOAT32 [0,1]
			D32F_S8 = 7 , // With 8-bit stencil
			D32F_S16 = 8 , // With 16-bit stencil
		
			D32F_IW = 9 , // 1/W -buffer as FLOAT32
			D32F_IW_S8 = 10 , // With 8-bit stencil
			D32F_IW_S16 = 11 , // With 16-bit stencil
		
			D32F_W = 12 , // W-buffer as FLOAT32
			D32F_W_S8 = 13 , // With 8-bit integer stencil
			D32F_W_S16 = 14 , // With 8-bit integer stencil
		
			D64F = 15 , // Pseudo-depth as FLOAT64 [0,1]
			D64F_S8 = 16 , // With 8-bit stencil
			D64F_S16 = 17 , // With 16-bit stencil
		
			D64F_IW = 18 , // 1/W -buffer as FLOAT64
			D64F_IW_S8 = 19 , // With 8-bit stencil
			D64F_IW_S16 = 20 , // With 16-bit stencil
		
			D64F_W = 21 , // W-buffer as FLOAT64
			D64F_W_S8 = 22 , // With 8-bit integer stencil
			D64F_W_S16 = 23 , // With 8-bit integer stencil
		
			//**********************************
			// Color formats (input & output)
		
			C16 = 24 , // R5,G6,B5

			// 16-bit format (alpha=1,red=5,green=5,blue=5) little endian
			C16_A1 = 25 ,
		
			C32_ARGB = 26 , // A8,R8,G8,B8
			C32_ABGR = 27 , // A8,B8,G8,R8
			
			// 32-bit format (alpha=2,red=10,green=10,blue=10) little endian
			C32_A2_RGB = 28 ,

			// 64-bit format (alpha=16,blue=16,green=16,red=16) little endian
			C64_ABGR = 29 ,
		
			// FLOAT32 for alpha,red,green,blue
			CF32_ABGR = 30 ,
		
			// Single color channel float for depth texture generation
			CF32_R = 31 , 
		
			// Two float32 color channels 
			CF32_GR = 32 ,
		
			//***************************
			// Input buffers only
		
			// Single color channel
			GRAY8 = 33 ,		
		
			// Expanded to (alpha=255,red,green,blue)
			C24_RGB = 34 ,
		
			//***************************
			// These are only used for pixel shader outputs
		
			STENCIL8 = 35 ,
			STENCIL16 = 36 ,

			// 32-bit format (empty,red,green,blue) little endian
			C32_XRGB = 37,

			// 32-bit format (empty,blue,green,red) little endian
			C32_XBGR = 38,

			// 16-bit format (empty=1,red=5,green=5,blue=5) little endian
			C16_X1 = 39 ,

			// 16-bit format (alpha=4,red=4,green=4,blue=4) little endian
			C16_ARGB = 40 ,

			// 8-bit format (alpha=8)
			ALPHA_8 = 41 ,

			// 16-bit format (alpha=8,red=3,green=3,blue=2) little endian
			C16_A8RGB = 42 ,

			// 8-bit format (red=3,green=3,blue=2) little endian
			C8_RGB = 43 ,

			// 32-bit format (alpha=2,blue=10,green=10,red=10) little endian
			C32_A2_BGR = 44 ,

			// 16-bit format (empty=4,red=4,green=4,blue=4) little endian
			C16_XRGB = 45 ,

			// 32-bit format (green=16,red=16) little endian
			C32_GR_16 = 46 ,

			CF16_ABGR = 47 ,
			CF16_R = 48 ,
			CF16_GR = 49 ,

			// 32-bit integer depth buffer
			D32 = 50 ,

			// 16-bit (stencil=1,depth=15) little endian
			D15_S1 = 51 ,

			// 32-bit (empty=8,depth=24) little endian
			D24_X8 = 52,

			// 32-bit format (stencil=4,empty=4,depth=24) little endian
			D24_X4_S4 = 53 ,

			// 32-bit format (stencil=8,float depth=24) little endian
			D24F_S8 = 54,

			// 32-bit float depth with CPU access
			D32F_LOCKABLE = 55 ,

			// 32-bit depth buffer with CPU access
			D32_LOCKABLE = 56 ,

			// 16-bit depth buffer with CPU access
			D16_LOCKABLE = 57 ,

			dxt1 = 58 ,
			dxt2 = 59 ,
			dxt3 = 60 ,
			dxt4 = 61 ,
			dxt5 = 62 ,

			normal_3dc = 63 ,

			C24_BGR = 64 ,

			bc7_rgba_unorm = 65 ,
			bc7_srgb_alpha_unorm = 66 ,
			
			bc6_rgb_float = 67 ,
			bc6_rgb_unsigned_float = 68 ,

			etc2_rgb8 = 69,
			etc2_srgb8 = 70 ,

			etc2_rgb8_a1 = 71 ,
			etc2_srgb8_a1 = 72 ,

			etc2_rgba8 = 73 ,
			etc2_srgb8_a8 = 74 ,

			eac_r11_unsigned = 75 ,
			eac_r11_signed = 76 ,

			eac_rg11_unsigned = 77 ,
			eac_rg11_signed = 78 ,

			etc1_rgb = 79 ,

			bc5_rg_unorm = 80 ,
			bc5_rg_snorm = 81 ,

			bc4_r_unorm = 82 ,
			bc4_r_snorm = 83 ,

			// 64-bit, 16 per channel (alpha,red,green,blue) little endian
			c64_argb = 84 ,

			uint_g8_r8 = 85 ,
			uint_r8 = 86 ,

			cf32_bgr = 89 ,

			uint_r16 = 91 ,

			uint_r32 = 92 ,
			uint_g32_r32 = 93 ,

			uint_b32_g32_r32 = 94 ,
			uint_a32_b32_g32_r32 = 95 ,


			FORCE_32B = 1 << 30 ,
		}; // enum

	}; // namespace IMAGE_FORMAT

}; // namespace Ceng

#endif