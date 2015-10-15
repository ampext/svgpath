#pragma once

#include "svgpath.h"

#include <cctype>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <limits>
#include <tuple>
#include <algorithm>

namespace SvgUtils
{
	inline bool isCommaOrWhitespace(char ch)
	{
		return ch == ',' || std::isspace(ch);
	}

	inline double toDouble(const std::string &str)
	{
		std::istringstream stream(str);
		stream.imbue(std::locale::classic());

		double value;
		stream >> value;

		if (stream.fail() || !stream.eof())
			throw std::runtime_error("failure to convert from string \"" + str + "\" to double");

		return value;
	}

	template <class Iterator>
	bool skipToNextNumber(Iterator &it, Iterator last)
	{

		while (it != last && isCommaOrWhitespace(*it))
			it++;

		return it != last && (std::isdigit(*it) || *it == '-');
	}

	template <class Iterator>
	void skipWhitespace(Iterator &it, Iterator last)
	{
		while (it != last && std::isspace(*it))
			it++;		
	}

	template <class Iterator>
	double readNumber(Iterator &it, Iterator last)
	{
		skipWhitespace(it, last);
		
		Iterator from = it;
		
		if (it != last)
		{
			if (*it == '-') 
				it++;
			
			if (it != last)
			{
				while (it != last && std::isdigit(*it))
					it++;
				
				if (it != last && *it == '.')
				{
					it++;

					if (it != last)
					{
						while (it != last && std::isdigit(*it))
							it++;
						
						if (it != last)
						{
							if (*it == 'e' || *it == 'E')
							{
								it++;

								if (it == last) throw std::runtime_error("failure to read number, expected power after exponent symbol");
								
								if (*it == '-') 
									it++;
								
								if (it == last) throw std::runtime_error("failure to read number, expected digits after sign");
								
								while (it != last && std::isdigit(*it))
									it++;
							}
						}
					}
				}
			}
			
			if (it == last || !std::isdigit(*it) || isCommaOrWhitespace(*it))
				return toDouble({ from, it });
		}
		
		throw std::runtime_error("failure to read number, something wrong here");
	}

	template <class Iterator>
	std::pair<double, double> readCoordinatePair(Iterator &it, Iterator last)
	{
		double x;
		double y;

		try
		{
			x = readNumber(it, last);
		}
		catch (std::runtime_error &)
		{
			throw std::runtime_error("expected x coordinate");
		}

		if (it == last)
			throw std::runtime_error("expected comma or whitespace before y coordinate");
		
		if (!isCommaOrWhitespace(*it) && *it != '-') 
			throw std::runtime_error(std::string("expected comma or whitespace before y coordinate, but \"") + *it + "\" found");
		
		bool commaFound = false;

		while (it != last && isCommaOrWhitespace(*it))
		{
			if (*it++ == ',')
			{
				if (commaFound) throw std::runtime_error("expected y coordinate");
				commaFound = true;
			}
		}

		try
		{
			y = readNumber(it, last);
		}
		catch (std::exception &)
		{
			throw std::runtime_error("expected y coordinate");
		}

		return { x, y };
	}

	template<class InputIt, class OutCmdIt, class OutCoordIt>
	void readSvgCommand(InputIt &it, InputIt last, OutCmdIt commandIt, OutCoordIt coordIt)
	{
		skipWhitespace(it, last);

		if (it == last) return;

		std::pair<double, double> xy;
		SvgPath::PathElement command;

		 if (*it == 'M' || *it == 'm' || *it == 'L' || *it == 'l')
		{
			if(*it == 'M') command = SvgPath::PathElement::MoveTo;
			else if(*it == 'm') command = SvgPath::PathElement::MoveToRel;
			else if(*it == 'L') command = SvgPath::PathElement::LineTo;
			else if(*it == 'l') command = SvgPath::PathElement::LineToRel;

			it++;

			do
			{
				xy = readCoordinatePair(it, last);

				*commandIt++ = command;
				*coordIt++ = xy.first;
				*coordIt++ = xy.second;
			}
			while (skipToNextNumber(it, last));
		}
		else if (*it == 'H' || *it == 'h' || *it == 'V' || *it == 'v')
		{
			if(*it == 'H') command = SvgPath::PathElement::LineToHorizontal;
			else if(*it == 'h') command = SvgPath::PathElement::LineToHorizontalRel;
			else if(*it == 'V') command = SvgPath::PathElement::LineToVertical;
			else if(*it == 'v') command = SvgPath::PathElement::LineToVerticalRel;

			it++;

			do
			{
				*commandIt++ = command;
				*coordIt++ = readNumber(it, last);
			}
			while (skipToNextNumber(it, last));
		}
		else if (*it == 'Z' || *it == 'z')
		{
			*it++;
			*commandIt++ = SvgPath::PathElement::ClosePath;
		}
		else if (*it == 'C' || *it == 'c' || *it == 'S' || *it == 's' ||
			*it == 'Q' || *it == 'q' || *it == 'T' || *it == 't')
		{
			if(*it == 'C') command = SvgPath::PathElement::CurveToCubic;
			else if(*it == 'c') command = SvgPath::PathElement::CurveToCubicRel;
			else if(*it == 'S') command = SvgPath::PathElement::CurveToCubicSmooth;
			else if(*it == 's') command = SvgPath::PathElement::CurveToCubicSmoothRel;
			else if(*it == 'Q') command = SvgPath::PathElement::CurveToQuadratic;
			else if(*it == 'q') command = SvgPath::PathElement::CurveToQuadraticRel;
			else if(*it == 'T') command = SvgPath::PathElement::CurveToQuadraticSmooth;
			else if(*it == 't') command = SvgPath::PathElement::CurveToQuadraticSmoothRel;

			it++;

			do
			{
				xy = readCoordinatePair(it, last);

				*commandIt++ = command;
				*coordIt++ = xy.first;
				*coordIt++ = xy.second;

				if (command != SvgPath::PathElement::CurveToQuadraticSmooth &&
					command != SvgPath::PathElement::CurveToQuadraticSmoothRel)
				{
					xy = readCoordinatePair(it, last);

					*coordIt++ = xy.first;
					*coordIt++ = xy.second;

					if (command != SvgPath::PathElement::CurveToCubicSmooth &&
						command != SvgPath::PathElement::CurveToCubicSmoothRel &&
						command != SvgPath::PathElement::CurveToQuadratic &&
						command != SvgPath::PathElement::CurveToQuadraticRel)
					{
						xy = readCoordinatePair(it, last);

						*coordIt++ = xy.first;
						*coordIt++ = xy.second;
					}
				}
			}
			while (skipToNextNumber(it, last));
		}
		else throw std::runtime_error(std::string("unexpected command \"") + *it + "\"");

	}
	
	template<class InputIt, class OutCmdIt, class OutCoordIt>
	void readSvgPath(InputIt &it, InputIt last, OutCmdIt commandIt, OutCoordIt coordIt)
	{
		InputIt originIt = it;

		while (it != last)
		{
			skipWhitespace(it, last);

			if (it == last)
				break;

			try
			{
				readSvgCommand(it, last, commandIt, coordIt);
			}
			catch (std::runtime_error &e)
			{
				std::ostringstream msg;
				msg << "failure to read svg path at " << std::distance(originIt, it) << ": " << e.what();

				throw std::runtime_error(msg.str());
			}
		}
	}

	inline bool isCommandRelative(SvgPath::PathElement element)
	{
		return	element == SvgPath::PathElement::MoveToRel ||
			element == SvgPath::PathElement::LineToRel ||
			element == SvgPath::PathElement::LineToHorizontalRel ||
			element == SvgPath::PathElement::LineToVerticalRel ||
			element == SvgPath::PathElement::CurveToCubicRel ||
			element == SvgPath::PathElement::CurveToCubicSmoothRel ||
			element == SvgPath::PathElement::CurveToQuadraticRel ||
			element == SvgPath::PathElement::CurveToQuadraticSmoothRel;
	}

	inline bool isCurveToCubic(SvgPath::PathElement element)
	{
		return element == SvgPath::PathElement::CurveToCubic ||
			element == SvgPath::PathElement::CurveToCubicRel ||
			element == SvgPath::PathElement::CurveToCubicSmooth ||
			element == SvgPath::PathElement::CurveToCubicSmoothRel;
	}

	inline bool isCurveToQuadratic(SvgPath::PathElement element)
	{
		return element == SvgPath::PathElement::CurveToQuadratic ||
			element == SvgPath::PathElement::CurveToQuadraticRel ||
			element == SvgPath::PathElement::CurveToQuadraticSmooth ||
			element == SvgPath::PathElement::CurveToQuadraticSmoothRel;
	}

	inline std::tuple<double, double, double, double> getCurveBoundingRect(double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3)
	{
		double xMin = std::numeric_limits<double>::max();
		double xMax = std::numeric_limits<double>::lowest();
		double yMin = std::numeric_limits<double>::max();
		double yMax = std::numeric_limits<double>::lowest();

		const size_t n = 100;

		for (size_t i = 0; i < n + 1; i++)
		{
			double t = 1.0 / n * i;

			double x = (1 - t) * (1 - t) * (1 - t) * x0 + 3 * t * (1 - t) * (1 - t) * x1 + 3 * t * t * (1 - t) * x2 + t * t * t * x3;
			double y = (1 - t) * (1 - t) * (1 - t) * y0 + 3 * t * (1 - t) * (1 - t) * y1 + 3 * t * t * (1 - t) * y2 + t * t * t * y3;

			xMin = std::min<double>(xMin, x);
			xMax = std::max<double>(xMax, x);
			yMin = std::min<double>(yMin, y);
			yMax = std::max<double>(yMax, y);
		}

		return std::make_tuple(xMin, yMin, xMax - xMin, yMax - yMin);
	}
}
 
