#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

std::string executablePath = "";

int main(int argc, char* const argv[])
{
	executablePath = argv[0];
	size_t p = executablePath.rfind('/');

	if (p != std::string::npos)
		executablePath = executablePath.substr(0, p);

	return Catch::Session().run(argc, argv);
}
