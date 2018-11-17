/*****************************************************************************
*
* graphics-2d.h
*
* By Jari Korkala 10/2012
*
*****************************************************************************/

#ifndef _CONCEPT2_GRAPHICS_2D_H
#define _CONCEPT2_GRAPHICS_2D_H

#include "base-interface.h"
#include "image-buffer.h"
#include "../datatypes/return-val.h"

namespace Ceng
{
	class Graphics2D : public Ceng::BASE_INTERFACE
	{
	protected:
		virtual ~Graphics2D()
		{
		}
	public:
		Graphics2D()
		{
		}

		virtual const CRESULT Restore()=0;

		virtual const CRESULT ShowFrame(Ceng::ImageBuffer *frameBuffer)=0;
		
		virtual const CRESULT ChangeWindowSize(const Ceng::UINT32 width,const Ceng::UINT32 height)=0;

		virtual const CRESULT FillDisplay(const Ceng::UINT8 red,const Ceng::UINT8 green,const Ceng::UINT8 blue)=0;
	};

} // Namespace Ceng

#endif // Include guard