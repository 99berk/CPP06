#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>
#include <stdint.h>

typedef struct Data
{
	std::string		name;
	unsigned int	age;
	Data			*next;
} Data;

class Serializer
{
	private:
		Serializer();
		Serializer(Serializer const &other);
		~Serializer();

	public:
		Serializer const	&operator=(Serializer const &copy);

		static uintptr_t	serialize(Data* ptr);
		static Data 		*deserialize(uintptr_t raw);
};

#endif
