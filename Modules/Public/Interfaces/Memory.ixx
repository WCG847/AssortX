export module AssortX:Memory;
import :Types;
namespace AssortX::Memory {
	export class MemoryUtils {
	  public:
		static void Copy(Types::SIZE Count, unsigned char *Destination,
						 const unsigned char *Source);
		};
	}
