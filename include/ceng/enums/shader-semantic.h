/*****************************************************************************
*
* shader-semantic.h
*
* By Jari Korkala 5/2013
*
*****************************************************************************/

#ifndef _CENG_SHADER_SEMANTIC_H
#define _CENG_SHADER_SEMANTIC_H

namespace Ceng
{
	/**
	 * Input variable semantic ID's that are used internally by the
	 * Concept Renderer.
	 */
	namespace SHADER_SEMANTIC
	{
		enum value
		{
			POSITION = 1 ,
			SCREENPOS = (1 << 1) ,

			NORMAL = (1 << 2) ,
			BINORMAL = (1 << 3) ,
			TANGENT = (1 << 4) ,

			COLOR_0 = (1 << 18) ,
			COLOR_1 = (1 << 19) ,

			TEXCOORD_0 = 1 << 20 ,
			TEXCOORD_1 = 1 << 21 ,
			TEXCOORD_2 = 1 << 22 ,
			TEXCOORD_3 = 1 << 23 ,
			TEXCOORD_4 = 1 << 24 ,
			TEXCOORD_5 = 1 << 25 ,
			TEXCOORD_6 = 1 << 26 ,
			TEXCOORD_7 = 1 << 27 ,

			FORMAT_END = 1 << 29 ,

			FORCE_32B = 1 << 30 ,
		};
	};
};

#endif