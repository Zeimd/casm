/*****************************************************************************
*
* vertex-format.h
*
* By Jari Korkala 4/2013
*
*****************************************************************************/

#ifndef _CENG_VERTEX_FORMAT_H
#define _CENG_VERTEX_FORMAT_H

#include "base-interface.h"

namespace Ceng
{
	/**
	* Interface to an API-specific vertex format container.
	*/
	class VertexFormat : public BASE_INTERFACE
	{
	protected:
		virtual ~VertexFormat()
		{
		}
	
	public:
		
		VertexFormat()
		{
		}
	};
	
};

#endif