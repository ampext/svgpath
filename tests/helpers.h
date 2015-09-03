#pragma once

#include "../src/svgutils.h"
#include "catch.hpp"

#include <iterator>
#include <functional>

typedef std::vector<SvgPath::PathElement> PathElements;

double readNumber(const std::string& str)
{
	auto it = str.begin();
	return SvgUtils::readNumber(it, str.end());
}

std::pair<double, double> readCoordinate(const std::string& str)
{
	auto it = str.begin();
	return SvgUtils::readCoordinatePair(it, str.end());
}

void readSvgCommand(const std::string &str, std::vector<SvgPath::PathElement> &commands, std::vector<double> &coords)
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

void readSvgPath(const std::string &str, std::vector<SvgPath::PathElement> &commands, std::vector<double> &coords)
{
	commands.clear();
	coords.clear();
	
	auto it = str.begin();
	SvgUtils::readSvgPath(it, str.end(), std::back_inserter(commands), std::back_inserter(coords));
}

namespace Catch {
	namespace Matchers {
	    namespace Impl {
	    	namespace DoubleVector
	    	{
				struct Equals: MatcherImpl<Equals, std::vector<double>>
				{
				    Equals(const std::vector<double> &vec): m_vec(vec)
				    {

				    }

				    Equals(const Equals &other): m_vec(other.m_vec)
				    {

				    }

			        Equals& epsilon(double epsilon)
			        {
			            m_epsilon = epsilon;
			            return *this;
			        }

				    virtual bool match(const std::vector<double> &expr) const
				    {
				        if (expr.size() == m_vec.size())
				        {
				        	for (size_t i = 0; i < m_vec.size(); i++)
				        		if (expr[i] != Approx(m_vec[i]).epsilon(m_epsilon))
				        			return false;

				        	return true;
				        } 

				        return false;
				    }

				    virtual std::string toString() const
				    {
				        std::ostringstream stream;

				        stream << "== { ";

				        for (size_t i = 0; i < m_vec.size(); i++)
				        	stream << (i > 0 ? ", " : "") << Catch::toString(m_vec[i]);

				        stream << " }";
				    
				        return stream.str();
				    }

				    double m_epsilon = std::numeric_limits<float>::epsilon() * 100;
				    std::vector<double> m_vec;
				};
			}
		}

		inline Impl::DoubleVector::Equals Equals(std::initializer_list<double> l)
		{
			 return Impl::DoubleVector::Equals(std::vector<double>(l));
		}

	    inline Impl::DoubleVector::Equals Equals(const std::vector<double>& vec)
	    {
	        return Impl::DoubleVector::Equals(vec);
	    }
	}
}