/*****************************************************************************
*
* primitive-type.h
*
* By Jari Korkala 4/2013
*
*****************************************************************************/

#ifndef _CENG_PRIMITIVE_TYPE_H
#define _CENG_PRIMITIVE_TYPE_H

namespace Ceng
{
	namespace PRIMITIVE_TYPE 
	{
		enum value
		{
			/**
			 * All triangles share one vertex.
			 */
			TRIANGLE_FAN ,
		
			/**
			 * Two consecutive triangles share
			 * an edge.
			 */
			TRIANGLE_STRIP ,
		
			/**
			 * Completely separate triangles.
			 */
			TRIANGLE_LIST ,
		
			/**
			 * Separate points.
			 */
			POINT_LIST ,
		
			/**
			 * Separate lines.
			 */
			LINE_LIST ,
		
			/**
			 * A list of lines where the
			 * next line starts from the
			 * previous one's endpoint.
			 */
			LINE_STRIP ,
		
			/**
			 * Forces the enumeration to
			 * compile to a 32-bit variable.
			 */
			FORCE_32B = 1 << 30 ,
		};
	};

}; // namespace Ceng

#endif