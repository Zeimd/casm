
#include "data-item.h"

using namespace Casm;

void DataItem::Print(std::wostream& out) const
{
	out << '\t';

	if (initializer == nullptr)
	{

	}
	else
	{
		switch (elementSize)
		{
		case X86::OPERAND_SIZE::BYTE:
			out << "db";
			break;
		case X86::OPERAND_SIZE::WORD:
			out << "dw";
			break;
		case X86::OPERAND_SIZE::DWORD:
			out << "dd";
			break;
		case X86::OPERAND_SIZE::QWORD:
			out << "dq";
			break;
		case X86::OPERAND_SIZE::XMMWORD:
			out << "dxmm";
			break;
		case X86::OPERAND_SIZE::YMMWORD:
			out << "dymm";
			break;
		case X86::OPERAND_SIZE::ZMMWORD:
			out << "dzmm";
			break;
		default:
			out << "unk";
			break;
		}
	}	

	out << ' ';

	if (initializer != nullptr)
	{
		initializer->Print(out);
	}

	out << std::endl;
}