#include "hex-dump.h"

namespace Casm
{

	void HexDump(std::wostream& out, uint32_t groupSize, uint32_t length, const uint8_t* buffer)
	{
		if (length == 0) return;

		uint32_t groups = length / groupSize;

		uint32_t remainder = length % groupSize;

		for (uint32_t k = 0; k < groups; k++)
		{
			out << "    ";

			for (uint32_t j = 0; j < groupSize; j++)
			{
				out << "0x" << std::hex << buffer[k * groupSize + j] << " ";
			}

			out << std::endl;
		}

		out << "    ";

		for (uint32_t j = 0; j < remainder; j++)
		{
			out << "0x" << std::hex << buffer[groups * groupSize + j] << " ";
		}

		out << std::endl;

		out << std::dec;
	}

}