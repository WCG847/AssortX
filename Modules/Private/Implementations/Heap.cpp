module AssortX:Memory;
import :Types;

namespace AssortX::Memory {
	HeapManager::HHEAP HeapManager::Create(Types::U64 Tag) {
		HEAP &GotHeap = Heaps[Counter++];
		GotHeap.Base = MemoryManager::Allocate(512 * 1'024 * 1'024);
		GotHeap.Tag = Tag;
		HHEAP Ret(&GotHeap);
		return Ret;
	}
	HeapManager::HHEAP HeapManager::Create(const char (&Tag)[8]) {
		char alignas(8) New[8] = {0};
		New[0] = Tag[7];
		New[1] = Tag[6];
		New[2] = Tag[5];
		New[3] = Tag[4];
		New[4] = Tag[3];
		New[5] = Tag[2];
		New[6] = Tag[1];
		New[7] = Tag[0];
		return Create(*reinterpret_cast<const unsigned long long *>(New));
	}
	ByteStream HeapManager::Allocate(HHEAP Heap, Types::SIZE Size) {
		HEAP *GotHeap = Heap.GetToken();
		if (GotHeap->AccumulatedSize + Size > 512 * 1'024 * 1'024 ||
			GotHeap->PagesAllocated >= 14) {
			return nullptr;
		}
		ByteStream Start = GotHeap->Base + GotHeap->AccumulatedSize;
		GotHeap->AccumulatedSize += Size;
		HEAP::PAGE &Page = GotHeap->Pages[GotHeap->PagesAllocated];
		Page.Index = GotHeap->PagesAllocated++;
		Page.Page = Start;
		Page.Size = Size;
		return Start;
	}
}
