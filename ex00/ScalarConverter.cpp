#include "ScalarConverter.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <cmath>
#include <climits>

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter &other) { (void)other; }
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other) { (void)other; return *this; }
ScalarConverter::~ScalarConverter() {}

enum LiteralType {
	TYPE_CHAR,
	TYPE_INT,
	TYPE_FLOAT,
	TYPE_DOUBLE,
	TYPE_INVALID
};

static LiteralType detectType(const std::string &literal) {
	if (literal.length() == 1 && !std::isdigit(literal[0]))
		return TYPE_CHAR;
	
	if (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'')
		return TYPE_CHAR;
	
	if (literal == "nanf" || literal == "+inff" || literal == "-inff")
		return TYPE_FLOAT;
	
	if (literal == "nan" || literal == "+inf" || literal == "-inf")
		return TYPE_DOUBLE;
	
	if (literal.find('.') != std::string::npos && literal[literal.length() - 1] == 'f')
		return TYPE_FLOAT;
	
	if (literal.find('.') != std::string::npos)
		return TYPE_DOUBLE;
	
	return TYPE_INT;
}

static void printChar(double value) {
	std::cout << "char: ";
	if (std::isnan(value) || std::isinf(value) || value < 0 || value > 255) {
		std::cout << "impossible" << std::endl;
	} else if (value < 32 || value > 126) {
		std::cout << "Non displayable" << std::endl;
	} else {
		std::cout << "'" << static_cast<char>(value) << "'" << std::endl;
	}
}

static void printInt(double value) {
	std::cout << "int: ";
	if (std::isnan(value) || std::isinf(value) || value < INT_MIN || value > INT_MAX) {
		std::cout << "impossible" << std::endl;
	} else {
		std::cout << static_cast<int>(value) << std::endl;
	}
}

static void printFloat(double value) {
	std::cout << "float: ";
	if (std::isnan(value)) {
		std::cout << "nanf" << std::endl;
	} else if (std::isinf(value)) {
		if (value > 0)
			std::cout << "+inff" << std::endl;
		else
			std::cout << "-inff" << std::endl;
	} else {
		float f = static_cast<float>(value);
		std::cout << f;
		if (f == static_cast<int>(f))
			std::cout << ".0";
		std::cout << "f" << std::endl;
	}
}

static void printDouble(double value) {
	std::cout << "double: ";
	if (std::isnan(value)) {
		std::cout << "nan" << std::endl;
	} else if (std::isinf(value)) {
		if (value > 0)
			std::cout << "+inf" << std::endl;
		else
			std::cout << "-inf" << std::endl;
	} else {
		std::cout << value;
		if (value == static_cast<int>(value))
			std::cout << ".0";
		std::cout << std::endl;
	}
}

void ScalarConverter::convert(const std::string &literal) {
	LiteralType type = detectType(literal);
	double value = 0.0;
	
	try {
		switch (type) {
			case TYPE_CHAR:
				if (literal.length() == 1)
					value = static_cast<double>(literal[0]);
				else if (literal.length() == 3)
					value = static_cast<double>(literal[1]);
				break;
			case TYPE_INT: {
				std::stringstream ss(literal);
				int intVal;
				if (!(ss >> intVal) || !ss.eof())
					throw std::exception();
				value = static_cast<double>(intVal);
				break;
			}
			case TYPE_FLOAT:
				if (literal == "nanf")
					value = std::numeric_limits<double>::quiet_NaN();
				else if (literal == "+inff")
					value = std::numeric_limits<double>::infinity();
				else if (literal == "-inff")
					value = -std::numeric_limits<double>::infinity();
				else {
					std::string floatStr = literal.substr(0, literal.length() - 1);
					std::stringstream ss(floatStr);
					float floatVal;
					if (!(ss >> floatVal) || !ss.eof())
						throw std::exception();
					value = static_cast<double>(floatVal);
				}
				break;
			case TYPE_DOUBLE:
				if (literal == "nan")
					value = std::numeric_limits<double>::quiet_NaN();
				else if (literal == "+inf")
					value = std::numeric_limits<double>::infinity();
				else if (literal == "-inf")
					value = -std::numeric_limits<double>::infinity();
				else {
					std::stringstream ss(literal);
					if (!(ss >> value) || !ss.eof())
						throw std::exception();
				}
				break;
			case TYPE_INVALID:
				throw std::exception();
		}
	} catch (...) {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return;
	}
	
	printChar(value);
	printInt(value);
	printFloat(value);
	printDouble(value);
}