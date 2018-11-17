/*****************************************************************************
*
* blend-state-desc.h
*
* Created By Jari Korkala 10/11/2015
*
*****************************************************************************/

#ifndef CENG_BLEND_STATE_DESC_H
#define CENG_BLEND_STATE_DESC_H

#include "boolean.h"

namespace Ceng
{
	namespace BlendType
	{
		enum value
		{
			zero = 1,
			one = 2 ,

			source_color = 3 ,
			invert_source_color = 4 ,

			source_alpha = 5 ,
			invert_source_alpha = 6 ,

			dest_alpha = 7 ,
			invert_dest_alpha = 8 ,

			dest_color = 9 ,
			invert_dest_color = 10  ,

			source_alpha_saturate = 11 ,

			blend_factor = 12 ,

			invert_blend_factor = 13 ,



		};
	}

	namespace BlendOp
	{
		enum value
		{
			add = 1 ,
			subtract = 2 ,
			reverse_subtract = 3 ,
			min = 4 ,
			max = 5 ,
		};
	}

	class RenderTargetBlendDesc
	{
	public:
		Ceng::BOOL blendEnable;
		
		/**
		 * Operation done on the color value written by pixel shader.
		 */
		Ceng::BlendType::value sourceBlend;

		/**
		 * Operation done on the color value read from render target.
		 */
		Ceng::BlendType::value destBlend;

		/**
		 * How to combine source color and destination color.
		 */
		Ceng::BlendOp::value blendOp;

		/**
		 * Operation done on the alpha value written by pixel shader.
		 */
		Ceng::BlendType::value sourceBlendAlpha;

		/**
		* Operation done on the alpha value read from render target.
		*/
		Ceng::BlendType::value destBlendAlpha;

		/**
		* How to combine source alpha and destination alpha.
		*/
		Ceng::BlendOp::value blendAlphaOp;

		Ceng::UINT8 writeMask;
	};

	class BlendStateDesc
	{
	public:

		/**
		 * Enabled alpha to coverage multisampling technique.
		 */
		Ceng::BOOL alphaToCoverage;

		/**
		 * Enables independent blend mode for each render target.
		 */
		Ceng::BOOL independentBlend;

		Ceng::UINT32 targets;
		RenderTargetBlendDesc *descList;
	};
	
}

#endif