/*****************************************************************************
*
* return-val.h
*
* By Jari Korkala 10/2012
*
*****************************************************************************/

#ifndef _CONCEPT2_RETURN_VAL_H
#define _CONCEPT2_RETURN_VAL_H

//******************************************************************
// Function return codes

namespace Ceng
{
	enum CRESULT 
	{ 
		CE_OK = 1,
		CE_EXIT = 2,
		
		CE_WARNING_INCOMPATIBLE_VERTEX_SHADER = 3,
		CE_WARNING_NO_VERTEX_SHADER = 4,
		CE_WARNING_INCOMPATIBLE_PIXEL_SHADER = 5,
		CE_WARNING_NO_PIXEL_SHADER = 6,
		CE_WARNING_SCENE_DISABLED = 7,
		
		CE_ERR_FAIL = 8,
		
		CE_ERR_INCOMPATIBLE_FORMAT = 9,
		
		CE_ERR_INVALID_PARAM = 10,
		CE_ERR_NOT_SUPPORTED = 11,
		CE_ERR_OUT_OF_MEMORY = 12,
		
		CE_ERR_DATA_ALIGNMENT = 13,
		
		CE_ERR_PARAM = 14,
		CE_ERR_NULL_PTR = 15,
		CE_ERR_ALLOC = 16,
		CE_ERR_IO = 17, 
		CE_ERR_FILE_WRITE = 18,
		CE_ERR_FILE_READ = 19,

		CE_ERR_WAIT_TIMEOUT = 20 ,
		CE_ERR_ABANDONED_OBJECT = 21 ,

		CE_ERR_OUT_OF_VIDEO_MEMORY = 22 ,
		
		CRESULT_FORCE_32BIT = (1 << 30) ,
	};

} // Namespace Ceng

#endif