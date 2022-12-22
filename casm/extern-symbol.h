
#ifndef CASM_EXTERN_SYMBOL_H
#define CASM_EXTERN_SYMBOL_H

namespace Casm
{
	struct ExternSymbol
	{
		const char* name;
		void* address;
	};
}

#endif