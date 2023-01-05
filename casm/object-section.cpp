
#include "object-section.h"
#include "symbol.h"
#include "symbol-ref.h"
#include "code-label.h"

#include "relocation-data.h"

#include "hex-dump.h"

using namespace Casm;

ObjectSection::ObjectSection() : options(0)
{
}

ObjectSection::ObjectSection(const Ceng::String& name, const Ceng::UINT32 options)
	: Symbol(name, this, Casm::SymbolType::section, true, false),
	options(options)
{

}

ObjectSection::ObjectSection(const Ceng::String& name,
	const Ceng::UINT32 options,
	std::vector<Ceng::UINT8>&& codeBuffer)
	: Symbol(name, this, Casm::SymbolType::section, true, false),
	options(options), codeBuffer(codeBuffer)
{
}

ObjectSection::~ObjectSection()
{
	
}

void ObjectSection::Print(std::wostream& out) const
{
	if (SizeBytes() == 0) return;

	out << "section " << name << " (size=" <<
		std::dec << SizeBytes() << ")" << std::endl;

	Casm::HexDump(out, 16, SizeBytes(), &codeBuffer[0]);

	out << "end section" << std::endl;
}

Ceng::CRESULT ObjectSection::Append(std::vector<Ceng::UINT8>& destBuffer) const
{
	std::copy(codeBuffer.begin(), codeBuffer.end(), std::back_inserter(destBuffer));

	return Ceng::CE_OK;
}

Ceng::CRESULT ObjectSection::ToCodeBuffer(Ceng::UINT8* buffer) const
{
	memcpy(buffer, &codeBuffer[0], codeBuffer.size());

	return Ceng::CE_OK;
}

