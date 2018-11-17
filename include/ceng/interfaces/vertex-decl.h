/*****************************************************************************
*
* vertex-decl.h
*
* By Jari Korkala 4/2013
*
*****************************************************************************/

#ifndef _CENG_VERTEX_DECL_H
#define _CENG_VERTEX_DECL_H

#include <ceng/datatypes/ce-string.h>

#include "../datatypes/basic-types.h"

#include "../enums/vtx-datatype.h"
#include "../enums/shader-semantic.h"

namespace Ceng
{
	/**
	* The vertex input format is defined by a list of
	* VertexDeclarationData objects.
	*/
	class VertexDeclData
	{
	public:

		Ceng::StringUtf8 name;

		Ceng::UINT32 streamSource;
		Ceng::UINT32 offset;
		
		Ceng::VTX_DATATYPE::value format;

		Ceng::UINT32 stride;


		
		Ceng::SHADER_SEMANTIC::value semantic; 
		Ceng::UINT32 semanticIndex;
	public:
		VertexDeclData() {}

		VertexDeclData(Ceng::UINT32 stream, Ceng::UINT32 offset, Ceng::VTX_DATATYPE::value format, Ceng::UINT32 stride,
			Ceng::StringUtf8 &name)
			: streamSource(stream), offset(offset),stride(stride),format(format), name(name)
		{
		}

		VertexDeclData(UINT32 stream, UINT32 offset, Ceng::VTX_DATATYPE::value format, Ceng::UINT32 stride,
			const char *name)
			: streamSource(stream), offset(offset),stride(stride),format(format), name(name)
		{
		}
		
		VertexDeclData(UINT32 stream, UINT32 offset, Ceng::VTX_DATATYPE::value format, Ceng::UINT32 stride,
							Ceng::SHADER_SEMANTIC::value semantic)
							: streamSource(stream) , offset(offset) , stride(stride),
							format(format) , semantic(semantic)
		{
		} 
	};

	const VertexDeclData VTX_DECL_END = VertexDeclData(255,255,Ceng::VTX_DATATYPE::FORMAT_END,0,
																	Ceng::SHADER_SEMANTIC::FORMAT_END);
	
};

#endif