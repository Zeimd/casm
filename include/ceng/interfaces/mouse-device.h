/*****************************************************************************
*
* mouse-device.h
*
* By Jari Korkala 15/12/2015
*
*****************************************************************************/

#ifndef CENG_MOUSE_DEVICE_H
#define CENG_MOUSE_DEVICE_H

#include "base-interface.h"

#include "../datatypes/return-val.h"
#include "../datatypes/boolean.h"

namespace Ceng
{
	struct MouseState
	{
		Ceng::INT32 xPos;
		Ceng::INT32 yPos;
		Ceng::INT32 xRelative;
		Ceng::INT32 yRelative;
		Ceng::INT32 buttonMask;
		Ceng::BOOL relative;
	};

	class MouseDevice : public BASE_INTERFACE
	{
	protected:
		virtual ~MouseDevice()
		{
		}
	public:
		MouseDevice()
		{
		}

		virtual const Ceng::CRESULT Restore() = 0;

		virtual const Ceng::CRESULT RelativeMode(const Ceng::BOOL state) = 0;

		virtual const Ceng::CRESULT GetState(MouseState *state) = 0;

		virtual const Ceng::CRESULT ClipToWindow(const Ceng::BOOL clip) = 0;
	};
}

#endif