#pragma once

#ifndef CASM_CASM_H
#define CASM_CASM_H

namespace Casm
{

}

#ifdef WIN32

#ifdef CASM_DLL_EXPORT
#define CASM_DLL_API __declspec(dllexport)
#else
#define CASM_DLL_API __declspec(dllimport)
#endif

#endif

extern "C"
{
	
}

#endif