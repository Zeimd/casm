
#ifndef CASM_X86_SYMBOL_TYPE_H
#define CASM_X86_SYMBOL_TYPE_H

namespace X86
{
	namespace SymbolType
	{
		enum value
		{
			unknown = 0,
			data = 1,
			function = 2,
			object_function = 4,
			section = 5,

			force_32b = 1 << 30,
		};
	}
}

#endif