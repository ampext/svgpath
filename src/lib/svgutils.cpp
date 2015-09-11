#include "svgutils.h"

bool isCommaOrWhitespace(char ch)
{
	return ch == ',' || std::isspace(ch);
}

double toDouble(const std::string &str)
{
	std::istringstream stream(str);
	stream.imbue(std::locale::classic());

	double value;
	stream >> value;

	if (stream.fail() || !stream.eof())
		throw std::runtime_error("failure to convert from string to double");

	return value;
}