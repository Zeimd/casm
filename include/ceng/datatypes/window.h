/*****************************************************************************
*
* ce-window.h
*
* By Jari Korkala 10/2012
*
*****************************************************************************/

#ifndef _CONCEPT2_CE_WINDOW_H
#define _CONCEPT2_CE_WINDOW_H

#include "../interfaces/base-interface.h"

#include "../enums/window-status.h"
#include "../enums/window-options.h"

#include "basic-types.h"
#include "return-val.h"
#include "ce-string.h"

namespace Ceng
{
	class PlatformWindow : public Ceng::BASE_INTERFACE
	{
	protected:
		virtual ~PlatformWindow() 
		{
		}

		PlatformWindow() 
		{
		}
	
	public:
	
		virtual void Show()=0;
		virtual void Hide()=0;
		
		virtual void Minimize()=0;
		virtual void Maximize()=0;
		
		virtual const CRESULT SetCaption(const String &text)=0;
		virtual const CRESULT SetCaptionExtra(const String &extra)=0;
		
		virtual void GetClientArea(Ceng::UINT32 *widthPtr,Ceng::UINT32 *heightPtr)=0;
		
		virtual const CRESULT ProcessMessages()=0;
		
		virtual const Ceng::BOOL IsDestroyed()=0;
		virtual const Ceng::BOOL IsActive()=0;
		virtual const Ceng::BOOL IsResized()=0;
		virtual const Ceng::BOOL IsVisible()=0;

		virtual const Ceng::BOOL IsForeground() = 0;

		virtual const Ceng::BOOL KeyboardFocus() = 0;
		
		virtual const CRESULT Redraw()=0;
	};

} // Namespace Ceng

#endif // Include guard