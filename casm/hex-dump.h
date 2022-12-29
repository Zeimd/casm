
#ifndef CASM_HEX_DUMP_H
#define CASM_HEX_DUMP_H

#include <ostream>

namespace Casm
{
	void HexDump(std::wostream& out, uint32_t groupSize, uint32_t length, const uint8_t* buffer);

}

#endif