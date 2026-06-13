module;
#include <cstdarg>
#include <cwchar>
module AssortX:String;
import :Types;
import :Memory;
extern "C" __declspec(dllimport) void
	OutputDebugStringW(const char16_t *String);
namespace AssortX::String {
	String::String(Types::SIZE Length, const char32_t *const Data) {
		if (Length < 1 || Data == nullptr) {
			return;
		}
		Info.Length = Length;
		Info.Size = Length * sizeof(char32_t);
		Memory::MemoryUtils::Copy(
			Info.Size, reinterpret_cast<unsigned char *>(Info.Data),
			reinterpret_cast<const unsigned char *const>(Data));
	}
	Types::SIZE String::GetLength() const { return Info.Length; }
	const char32_t &String::operator*() const { return *Info.Data; }
	const char32_t &String::operator[](Types::U64 Key) const {
		return Info.Data[Key];
	}
	const char32_t *String::operator&() const { return Info.Data; }
	void *StringUtils::Convert(const String &Source, OutputType Out) {
		void *Result = nullptr;
		switch (Out) {
			case OutputType::UTF_16:
				// Actually UCS-2 because UTF-16 is complicated.
				static char16_t ScratchData[128] = {0};
				for (Types::SIZE i = 0; i < Source.GetLength(); i++) {
					if (Source[i] > 0xFFFF) {
						ScratchData[i] = 0xFFFD;
						continue;
					}
					ScratchData[i] = static_cast<char16_t>(Source[i]);
				}
				Result = reinterpret_cast<void *>(ScratchData);
				break;
		}
		return Result;
	}
	void StringUtils::Print(const char16_t *Format, PrintType Type,
							char *Extra) {
		static char16_t Out[1'024] = {0};
		std::vswprintf(reinterpret_cast<wchar_t *>(Out),
					   1024,
					   reinterpret_cast<const wchar_t *>(Format),
					   reinterpret_cast<std::va_list>(Extra));
		switch (Type) {
			case PrintType::DEBUG:
				OutputDebugStringW(Out);
				break;
			case PrintType::CONSOLE:
				wprintf(L"%ls", reinterpret_cast<wchar_t *>(Out));
				break;
		}
	}
	void StringUtils::DebugPrint(const char16_t *Format, ...) {
		va_list args;
		va_start(args, Format);
		Print(Format, PrintType::DEBUG, args);
		va_end(args);
	}
	void StringUtils::ConsolePrint(const char16_t *Format, ...) {
		va_list args;
		va_start(args, Format);
		Print(Format, PrintType::CONSOLE, args);
		va_end(args);
	}
}
