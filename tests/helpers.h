#pragma once

#include <svgutils.h>
#include "catch.hpp"

typedef std::vector<SvgPath::PathElement> PathElements;

inline double readNumber(const std::string& str)
{
	auto it = str.begin();
	return SvgUtils::readNumber(it, str.end());
}

inline std::pair<double, double> readCoordinate(const std::string& str)
{
	auto it = str.begin();
	return SvgUtils::readCoordinatePair(it, str.end());
}

inline void readSvgCommand(const std::string &str, std::vector<SvgPath::PathElement> &commands, std::vector<double> &coords)
{
	commands.clear();
	coords.clear();

	auto it = str.begin();

	try
	{
		SvgUtils::readSvgCommand(it, str.end(), std::back_inserter(commands), std::back_inserter(coords));
	}
	catch (std::exception &e)
	{
		std::ostringstream msg;
		msg << "failure to read command at " << std::distance(str.begin(), it) << ": " << e.what();

		throw std::runtime_error(msg.str());
	}
}

inline void readSvgPath(const std::string &str, std::vector<SvgPath::PathElement> &commands, std::vector<double> &coords)
{
	commands.clear();
	coords.clear();
	
	auto it = str.begin();
	SvgUtils::readSvgPath(it, str.end(), std::back_inserter(commands), std::back_inserter(coords));
}

class DoubleVectorMatcher: public Catch::MatcherBase<std::vector<double>>
{
private:
	const std::vector<double> &m_values;
	double m_epsilon;
public:
	DoubleVectorMatcher(
		const std::vector<double> &values,
		double epsilon = std::numeric_limits<float>::epsilon() * 100): m_values(values), m_epsilon(epsilon)
	{

	}

	virtual bool match(const std::vector<double> &values) const override
	{
		if (m_values.size() == values.size())
		{
			for (size_t i = 0; i < m_values.size(); i++)
				if (values[i] != Approx(m_values[i]).epsilon(m_epsilon))
					return false;

			return true;
		} 

		return false;		
	}

	virtual std::string describe() const override
	{
		return "Equals: " + Catch::Detail::stringify(m_values);
	}
};

inline DoubleVectorMatcher Equals(const std::vector<double> &values)
{
	return DoubleVectorMatcher(values);
}