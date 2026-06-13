module;
#include <cstdint>
#include <cstddef>
export module AssortX:Types;


export namespace AssortX::Types {
	using U8 = std::uint8_t;
	using U16 = std::uint16_t;
	using U32 = std::uint32_t;
	using U64 = std::uint64_t;

	using S8 = std::int8_t;
	using S16 = std::int16_t;
	using S32 = std::int32_t;
	using S64 = std::int64_t;

	using SIZE = std::size_t;
	using UPTR = std::uintptr_t;
	using SPTR = std::intptr_t;
	using BOOL = bool;
	enum class BoolStates : BOOL {
		FALSE = false, TRUE = true
		};
	}
