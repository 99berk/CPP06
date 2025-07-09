#ifndef BASE_HPP
#define BASE_HPP

class Base
{
	protected:

	public:
		virtual ~Base();

		Base *genereate();
		void idenitify(Base* p);
		void idenitify(Base& p);
};

#endif