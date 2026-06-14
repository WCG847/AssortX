module;
#include <windows.h>
module AssortX:IO;
import :Types;

namespace AssortX::IO {
	File FileManager::Open(const char16_t *&Name) {
		HANDLE hfile = CreateFileW(reinterpret_cast<const wchar_t *>(Name),
					GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, nullptr,
					OPEN_EXISTING, 0x80, nullptr);
		HANDLE hmem = CreateFileMappingW(hfile, nullptr, PAGE_EXECUTE_READWRITE, 0, 0,
						   reinterpret_cast<const wchar_t *>(Name));
		void *mem = MapViewOfFile(hmem, FILE_MAP_READ | FILE_MAP_EXECUTE | FILE_MAP_WRITE,
					  0, 0, 0);
		CloseHandle(hmem);
		File f(hfile, reinterpret_cast<unsigned char *>(mem));
		return f;
		}
	bool File::Read(Types::SIZE Size, unsigned char *Out) const {
			return ReadFile(Info.ID, reinterpret_cast<void *>(Out), static_cast<DWORD>(Size), 0, nullptr);
		}
	unsigned char *File::GetData() { return Info.Data; }
		File::~File() {
			CloseHandle(Info.ID);
			UnmapViewOfFile(Info.Data);
		}
	}
