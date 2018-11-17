/*****************************************************************************
*
* plat-keyboard.h
*
* By Jari Korkala 10/2012
*
*****************************************************************************/

#ifndef _CONCEPT2_PLAT_KEYBOARD_H
#define _CONCEPT2_PLAT_KEYBOARD_H

#include "../interfaces/base-interface.h"

#include "../enums/keyboard-key.h"

#include "../datatypes/return-val.h"
#include "../datatypes/basic-types.h"

namespace Ceng
{
	class PlatformWindow;

	class KeyboardDevice : public Ceng::BASE_INTERFACE
	{
	protected:
		virtual ~KeyboardDevice() 
		{
		}

		KeyboardDevice() 
		{
		}
		
	
	public:
	
		virtual const Ceng::UINT32 IsPressed(const Ceng::KEYBOARD_KEY::value key)=0;
		
		/**
		* Ensures that the application receives
		* keyboard input after an another application
		* has been on the foreground.
		*/
		virtual const CRESULT Restore()=0;
	};

} // Namespace Ceng

#endif // Include guard