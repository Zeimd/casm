/*****************************************************************************
*
* buffer-binding.h
*
* Created By Jari Korkala 2/3/2015
*
*****************************************************************************/

#ifndef CENG_BUFFER_BINDING_H
#define CENG_BUFFER_BINDING_H

namespace Ceng
{
	namespace BufferBinding
	{
		enum value
		{
			vertex_buffer = 1 ,
			index_buffer = 1 << 1 ,
			constant_buffer = 1 << 2 ,
			
			stream_output = 1 << 3,
			render_target = 1 << 4,
			depth_stencil = 1 << 5,
			
			shader_resource = 1 << 6 ,
			
			force32b = 1 << 30 ,
		};
	}
}


#endif