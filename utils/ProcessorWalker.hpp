#pragma once

#include <sal.h>
#include <ntifs.h>

//TODO : change to iterattor pattern
class CProcessorWalker
{
public:
	static
	__checkReturn
	bool 
	NextCore(
		__inout BYTE* coreId
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
