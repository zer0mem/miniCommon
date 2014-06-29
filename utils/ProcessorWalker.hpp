#pragma once

#include <sal.h>
#include <ntifs.h>

#define	PROCID(cpu) (KAFFINITY)((ULONG_PTR)KeQueryActiveProcessors() & (ULONG_PTR)(1 << (USHORT)cpu))

//TODO : change to iterattor pattern
class CProcessorWalker
{
public:
	static
	__checkReturn
	bool 
	NextCore(
		__inout unsigned char* coreId
		)
	{
		if (*coreId > (sizeof(ULONG) << 3))
			return false;

		unsigned char core_id = *coreId;
		while (0 == PROCID(core_id))
		{
			if (KeQueryActiveProcessorCount(nullptr) == core_id)
				return false;
			core_id++;
		}

		*coreId = core_id;
		return true;
	}
};
