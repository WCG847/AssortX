export module AssortX:IO;
import :Types;


namespace AssortX::IO {
	export class File {

	  private:
		struct FILE_INFO {
			void *ID;
			unsigned char *Data;
		} Info = {0};

	  public:
		File(void *ID, unsigned char *Data) : Info{.ID = ID, .Data = Data} {}
		~File();
		bool Read(Types::SIZE Size, unsigned char *Out) const;
		unsigned char *GetData();
	};
	export class FileManager {
	  public:
		static File Open(const char16_t *&Name);
		static File Create(const char16_t *&Name);
	};
}
