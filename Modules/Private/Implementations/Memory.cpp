module;
#include <intrin.h>
module AssortX:Memory;
import :Types;

extern "C" __declspec(dllimport) int NtAllocateVirtualMemory(void *, void **, unsigned long long,
									   unsigned long long *, unsigned int,
									   unsigned int);


extern "C" __declspec(dllimport) int
	NtFreeVirtualMemory(void *, void **, unsigned long long *, unsigned int);


namespace AssortX::Memory {
	void MemoryUtils::Copy(Types::SIZE Count, ByteStream Destination,
						   const ByteStream Source) {
		__movsb(Destination, Source, Count);
	}
	Types::UPTR MemoryUtils::AlignAddress(Types::SIZE Alignment,
										  Types::UPTR Address) {
		Alignment -= 1;
		return (Address + Alignment) & ~Alignment;
		}
	ByteStream MemoryManager::Allocate(Types::SIZE Size) {
		void *Base = nullptr;
		void *ph = reinterpret_cast<void *>(-1);
		unsigned int Flag = 0x0000'1000 | 0x0000'2000;
		unsigned int Page = 0x40;
		NtAllocateVirtualMemory(ph, &Base, 0, &Size, Flag, Page);
		return reinterpret_cast<ByteStream>(Base);
		}
	void MemoryManager::Free(ByteStream Page) {
			void *ph = reinterpret_cast<void *>(-1);
			unsigned int Flag = 0x0000'8000;
			unsigned long long Size = 0;
			NtFreeVirtualMemory(ph, reinterpret_cast<void **>(&Page), &Size,
								Flag);
		}
}
