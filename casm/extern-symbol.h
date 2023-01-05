
#ifndef CASM_EXTERN_SYMBOL_H
#define CASM_EXTERN_SYMBOL_H

#include "enums/symbol-type.h"

namespace Casm
{
	struct ExternSymbol
	{
		const char* name;
		SymbolType::value type;
		void* address;
	};
}

#endif