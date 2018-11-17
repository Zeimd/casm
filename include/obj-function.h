/*****************************************************************************
*
* obj-function.h
*
* By Jari Korkala 2/2014
*
*****************************************************************************/

#ifndef X86_OBJ_FUNCTION_H
#define X86_OBJ_FUNCTION_H

#include "symbol.h"
#include "symbol-ref.h"
#include "relocation-data.h"

#include <datatypes/basic-types.h>
#include <datatypes/return-val.h>
#include <memory>

namespace X86
{
	class ObjectFunction : public Symbol
	{
	public:

		std::vector<std::shared_ptr<SymbolRef>> *references;
		std::vector<Ceng::UINT8> *codeBuffer;

		ObjectFunction();
	

		ObjectFunction(const Ceng::String &name,
						std::vector<std::shared_ptr<SymbolRef>> *references,
						std::vector<Ceng::UINT8> *codeBuffer);		

		virtual ~ObjectFunction();		

		const Ceng::UINT32 SizeBytes() const
		{
			return codeBuffer->size();
		}

		Ceng::CRESULT ReferenceAll(std::vector<std::shared_ptr<Symbol>> *dataList,
									std::vector<std::shared_ptr<Symbol>> *functionList);

		Ceng::CRESULT WriteAllOffsets();

		Ceng::CRESULT Append(std::vector<Ceng::UINT8> &destBuffer) const;

		Ceng::CRESULT ToCodeBuffer(Ceng::UINT8 *buffer) const;

		Ceng::CRESULT AppendRelocationData(std::vector<RelocationData> &relocationData) const;
	};
}

#endif