#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

std::string executablePath = "";

int main(int argc, char* argv[])
{
	executablePath = argv[0];
	size_t p = std::string::npos;

	#ifdef __WIN32__
		p = executablePath.rfind('\\');
	#else
		p = executablePath.rfind('/');
	#endif

	if (p == std::string::npos) executablePath = ".";
	else executablePath = executablePath.substr(0, p);

	return Catch::Session().run(argc, argv);
}
