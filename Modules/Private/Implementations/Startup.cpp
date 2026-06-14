import AssortX;
extern "C" __declspec(dllimport) int NtTerminateProcess(void *, int);


extern "C" __declspec(dllimport) const char16_t **
	CommandLineToArgvW(const char16_t *lpCmdLine, int *pNumArgs);
extern "C" __declspec(dllimport) const char16_t *GetCommandLineW();

extern "C" __declspec(dllimport) void *LocalFree(void *hMem);

extern "C" long long Startup(int argc, const char16_t *argv[]);
extern "C" void AssortX_Startup() {
	AssortX::String::StringUtils::DebugPrint(
		u"%ls v%d.%.02d\r\n", AssortX::Build::Information.ProductName,
		AssortX::Build::Information.Version.Major,
		AssortX::Build::Information.Version.Minor);
	int nArgs;
	const char16_t **argv = CommandLineToArgvW(GetCommandLineW(), &nArgs);
	long long Result = Startup(nArgs, argv);
	LocalFree(argv);
	NtTerminateProcess(reinterpret_cast<void *>(-1), static_cast<int>(Result));
}
