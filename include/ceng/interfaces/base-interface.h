/*****************************************************************************
*
* base-interface.h
*
* By Jari Korkala 10/2012
*
*****************************************************************************/

#ifndef _CONCEPT2_BASE_INTERFACE_H
#define _CONCEPT2_BASE_INTERFACE_H

#include "../datatypes/basic-types.h"

//*************************************************************

namespace Ceng
{
	// class Inteface is the base class for all classes
	// implemented in external libraries because it forces
	// all allocations and deallocations to be done with library
	// code

	// NOTE: Must be pure virtual

	class Interface
	{
	protected:
		virtual ~Interface()
		{
		}
	
	public:
		Interface()
		{
		}
		
		virtual void Release()=0;
		//virtual UINT32 GetReferenceCount()=0;
	};

	typedef Interface BASE_INTERFACE;

} // Namespace Ceng

#endif // Include guard