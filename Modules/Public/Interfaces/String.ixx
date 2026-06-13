export module AssortX:String;
import :Types;

namespace AssortX::String {
	export class String {
	  private:
		  struct STRING_INFO {
			Types::U32 Length : 8, Size : 10;
			char32_t Data[128];
			} Info;

		public:
			String(Types::SIZE Length, const char32_t *const Data);
			template <Types::SIZE Length>
			[[deprecated("It is preferrable to use the explicit length constructor whenever possible to reduce template instantisation repetition upon compilation.")]]
			String(const char32_t (&Data)[Length])
				: String(Length - 1, Data) {};
			Types::SIZE GetLength() const;
			const char32_t &operator[](Types::U64 Key) const;
			const char32_t &operator*() const;
			const char32_t *operator&() const;
		};
	export class StringUtils {
		  public:
		enum class OutputType : Types::U8 { UTF_16 };
		static void *Convert(const String &Source, OutputType Out);
		enum class PrintType : Types::U8 {DEBUG, CONSOLE};
		static void Print(const char16_t *Format, PrintType Type, char *Extra);
		static void DebugPrint(const char16_t *Format, ...);
		static void ConsolePrint(const char16_t *Format, ...);
		};
	}
