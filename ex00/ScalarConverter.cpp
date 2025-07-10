#include "ScalarConverter.hpp"
#include <iostream>
#include <ctype.h>
#include <cstdlib>
#include <limits>
#include <iomanip>

ScalarConverter::ScalarConverter()
{
	std::cout << "Constuctor called" << std::endl;
}

ScalarConverter::ScalarConverter(ScalarConverter const &other)
{
	std::cout << "Copy constuctor called" << std::endl;
	*this = other;
}

ScalarConverter::~ScalarConverter() 
{
	std::cout << "Destructor called" << std::endl;
}

ScalarConverter	&ScalarConverter::operator=(const ScalarConverter &copy)
{
	(void)copy;
	std::cout << "Copy assignment op called" << std::endl;
	return (*this);
}

static int isChar(std::string input)
{
	if (input.size() > 1)
		return false;
	if (std::isprint(input[0]) && !isdigit(input[0]))
		return 1;
	return false;
}

static int isInt(std::string input)
{
	int hasSign = 0;

	for (size_t i = 0; i < input.size(); i++)
	{
		if (i == 0 && (input[i] == '+' || input[i] == '-') && !hasSign)
		{
			hasSign = 1;
			continue;
		}
		if (!std::isdigit(input[i]))
			return false;
	}
	double number = std::strtod(input.c_str(), NULL);
	if (std::numeric_limits<int>::min() > number || std::numeric_limits<int>::max() < number)
		return false;
	return 2;
}

static int isFloat(std::string input)
{
	int hasSign = 0;
	int hasF = 0;
	int hasPoint = 0;

	for (size_t i = 0; i < input.size(); i++)
	{
		if (i == 0 && (input[i] == '+' || input[i] == '-') && !hasSign)
		{
			hasSign = 1;
			continue;
		}
		if ((input[i] == 'f' || input[i] == 'F') && !hasF)
		{
			hasF = 1;
			continue;
		}
		if (i + 1 < input.size() && input[i] == '.' && std::isdigit(input[i + 1]) && !hasPoint)
		{
			if (i == 0 || input[i + 1] == '\0')
				return -1;
			hasPoint = 1;
			continue;
		}
		if (!std::isdigit(input[i]))
			return -1;
	}

    if (hasPoint)
    {
        size_t dotPos = input.find('.');
        size_t endPos = input.size();

        if (hasF)
            endPos--;

        size_t decimalLength = endPos - dotPos - 1;

        std::string decimalPart = input.substr(dotPos + 1, decimalLength);

        while (!decimalPart.empty() && decimalPart[decimalPart.size() - 1] == '0')
            decimalPart.erase(decimalPart.size() - 1);

        size_t meaningfulDecimals = decimalPart.length();

        if (meaningfulDecimals > 6)
            return false;
    }

	double number = std::strtod(input.c_str(), NULL);
	if (-std::numeric_limits<float>::max() > number
		|| std::numeric_limits<float>::max() < number)
		return false;
	// float toFloat = static_cast<float>(number);
	// double roundTrip = static_cast<double>(toFloat);
	// double tolerance = std::numeric_limits<float>::epsilon() * std::abs(number);
	// if (std::abs(roundTrip - number) > tolerance)
	// 	return false;
	return 3;
}

static int isDouble(std::string input)
{
	int hasF = 0;
	int hasPoint = 0;
	int hasSign = 0;

	for (size_t i = 0; i < input.size(); i++)
	{
		if ((input[i] == '+' || input[i] == '-') && !hasSign)
		{
			hasSign = 1;
			continue;
		}
		if ((input[i] == 'f' || input[i] == 'F') && !hasF)
		{
			hasF = 1;
			continue;
		}
		if (input[i] == '.' && !hasPoint)
		{
			hasPoint = 1;
			continue;
		}
 		if (!std::isdigit(input[i]))
			return -1;
	}
	return 4;
}

static int detectType(std::string input)
{
	int (*detectFunctions[])(std::string input) = {
		&isChar,
		&isInt,
		&isFloat,
		&isDouble
	};
	
	if (input == "inf" || input == "-inf" || input == "+inf" || input == "nan")
		return 4;
	if (input == "inff" || input == "-inff" || input == "+inff" || input == "nanf")
		return 3;
	for (size_t i = 0; i < 4; i++)
	{
		int ret;
		
		ret = detectFunctions[i](input);
		if (ret != false)
			return ret;
	}
	return 0;
}

static void printChar(std::string input)
{
	char c = input[0];
	std::cout << "char: '" << c << "'" << std::endl;
	int i = c;
	std::cout << "int: " << i << std::endl;
	std::cout << std::fixed << std::setprecision(1);
	float f = static_cast<float>(c);
	std::cout << "float: " << f << "f" << std::endl;
	double d = static_cast<double>(c);
	std::cout << "double: " << d << std::endl;
}

static void printInt(std::string input)
{
	int i = static_cast<int>(std::strtod(input.c_str(), NULL));
	if (i < 128 && i >= 0)
	{
		char c = static_cast<char>(i);
		if (std::isprint(c))
			std::cout << "char: '" << c << "'" << std::endl;
		else
			std::cout << "char: " << "Non displayable" << std::endl;
	}
	else
		std::cout << "char: " << "impossible" << std::endl;
		
	std::cout << std::fixed << std::setprecision(1);
	std::cout << "int: " << i << std::endl;
	float f = static_cast<float>(i);
	std::cout << "float: " << f << "f" << std::endl;
	double d = static_cast<double>(i);
	std::cout << "double: " << d << std::endl;
}

static int findPrecision(std::string input)
{
	int p = -1;
	int size = static_cast<int>(input.size());
	while (++p < size)
		if (input[p] == '.')
			break;

	if (input[size - 1] == 'f')
		size = size - 1;
	if (p == size)
		return 1;
	return size - (p + 1);
 }

static void printFloat(std::string input)
{
	char* end;
	float f = std::strtod(input.c_str(), &end);
	if (f < 128 && f >= 0)
	{
		char c = static_cast<char>(f);
		if (std::isprint(c))
			std::cout << "char: '" << c << "'" << std::endl;
		else
			std::cout << "char: " << "Non displayable" << std::endl;
	}
	else
		std::cout << "char: " << "impossible" << std::endl;
	if (std::numeric_limits<int>::min() < f &&  std::numeric_limits<int>::max() > f)
	{
		int i = static_cast<int>(f);
		std::cout << "int: " << i << std::endl;
	}
	else
		std::cout << "int: " << "impossible" << std::endl;
	std::cout << std::fixed << std::setprecision(findPrecision(input));
	std::cout << "float: " << f << "f" << std::endl;
	double d = static_cast<double>(f);
	std::cout << "double: " << d << std::endl;
}

static void printDouble(std::string input)
{
	std::cout << "DOUBLE->" << std::endl;
	char* end;
	double d = std::strtod(input.c_str(), &end);
	if (d < 128 && d >= 0)
	{
		char c = static_cast<char>(d);
		if (std::isprint(c))
			std::cout << "char: '" << c << "'" << std::endl;
		else
			std::cout << "char: " << "Non displayable" << std::endl;
	}
	else
		std::cout << "char: " << "impossible" << std::endl;
	if (std::numeric_limits<int>::min() < d &&  std::numeric_limits<int>::max() > d)
	{
		int i = static_cast<int>(d);
		std::cout << "int: " << i << std::endl;
	}
	else
		std::cout << "int: " << "impossible" << std::endl;
	float f = static_cast<float>(d);
	(f == 0) ? std::cout << std::fixed << std::setprecision(1) : std::cout << std::fixed << std::setprecision(findPrecision(input));
	std::cout << "float: " << f << "f" << std::endl;
	std::cout << std::fixed << std::setprecision(findPrecision(input));
	std::cout << "double: " << d << std::endl;
}

void ScalarConverter::convert(std::string input)
{
	switch (detectType(input))
	{
		case 1:
			printChar(input);
			break;
		case 2:
			printInt(input);
			break;
		case 3:
			printFloat(input);
			break;
		case 4:
			printDouble(input);
			break;
		case -1:
			std::cout << "It's illegal" << std::endl;
			break;
		default:	
			std::cout << "I don't know what it is." << std::endl;
			break;
	}
}
