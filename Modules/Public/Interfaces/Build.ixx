export module AssortX:Build;
import :Types;
namespace AssortX::Build {
	struct VERSION {
		Types::U8 Major : 4, Minor : 4;
	};
	enum class STATUS : Types::U8 { DEBUG, PRERELEASE, RELEASE };
	struct BUILD {
		VERSION Version;
		STATUS Build;
		const char16_t *ProductName;

	};
	export constexpr inline BUILD Information = {
		.Version = {.Major = 0, .Minor = 0},
		.Build = STATUS::DEBUG,
		.ProductName = u"AssortX"};

}
