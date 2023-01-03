
#ifndef CASM_SYMBOL_TYPE_H
#define CASM_SYMBOL_TYPE_H

namespace Casm
{
	namespace SymbolType
	{
		enum value
		{
			unknown = 0,
			data = 1,
			function = 2,
			section = 3,
			object_section = 4,

			force_32b = 1 << 30,
		};
	}
}

#endif