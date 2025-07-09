#include "Serializer.hpp"
#include <iostream>

Serializer::Serializer()
{
	std::cout << "Serializer default constructor called" << std::endl;
}

Serializer::Serializer(Serializer const &other)
{
	std::cout << "Serializer copy constructor called" << std::endl;
	*this = other;
}

Serializer::~Serializer(void)
{
	std::cout << "Serializer destructor called" << std::endl;
}

Serializer const	&Serializer::operator=(const Serializer &copy)
{
	(void)copy;
	std::cout << "Serializer assignment operator called" << std::endl;
	return (*this);
}

uintptr_t	Serializer::serialize(Data* ptr)
{
	uintptr_t	ret;

	ret = reinterpret_cast<uintptr_t>(ptr);
	return ret;
}

Data	*Serializer::deserialize(uintptr_t raw)
{
	Data *ret;

	ret = reinterpret_cast<Data *>(raw);
	return ret;
}
