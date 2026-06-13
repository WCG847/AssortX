module;
#include <intrin.h>
module AssortX:Memory;
import :Types;
namespace AssortX::Memory {
	void MemoryUtils::Copy(Types::SIZE Count, unsigned char *Destination,
							   const unsigned char *Source) {
		__movsb(Destination, Source, Count);
		}
	}
