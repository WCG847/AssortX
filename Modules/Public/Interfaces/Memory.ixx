export module AssortX:Memory;
import :Types;
import :Access;
namespace AssortX::Memory {
	using ByteStream = unsigned char *;
	export class MemoryUtils {
	  public:
		static void Copy(Types::SIZE Count, ByteStream Destination,
						 const ByteStream Source);
		static Types::UPTR AlignAddress(Types::SIZE Alignment,
										Types::UPTR Address);
		};
	export class MemoryManager {
		  public:
		static ByteStream Allocate(Types::SIZE Size);
			static void Free(ByteStream Page);
		};

	export class HeapManager {
		  private:
		static inline Types::SIZE Counter = 0;
			  static inline struct HEAP {
				unsigned long long Tag;
				  ByteStream Base;
				  unsigned char PagesAllocated : 5;
				unsigned long long AccumulatedSize;
				  struct PAGE {
					  unsigned char Index;
					  Types::SIZE Size;
					  ByteStream Page;
					} Pages[20];
			  } Heaps[14] = {0};
			  using HHEAP = Access::Handle<HEAP>;
			  static HHEAP Create(Types::U64 Tag);
			public:
			  static HHEAP Create(const char (&Tag)[8]);
			  static ByteStream Allocate(HHEAP Heap, Types::SIZE Size);
		};
	}
