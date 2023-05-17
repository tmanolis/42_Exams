#include "Warlock.hpp"

Warlock::Warlock()
{

}

Warlock::Warlock(Warlock const &src)
{
	*this = src;
}

Warlock::Warlock(std::string const &Name, std::string const &Title) : name(Name), title(Title)
{
	std::cout << name << ": This looks like another boring day." << std::endl;
}

Warlock::~Warlock()
{
	std::cout << name << ": My job here is done!" << std::endl;
}

// Operator Overload
Warlock	&Warlock::operator=(Warlock const &rhs)
{
	if (this != &rhs)
	{
		this->name = rhs.getName();
		this->title = rhs.getTitle();
	}

	return (*this);
}

// Accessors
std::string const	&Warlock::getName() const
{
	return (name);
}
std::string const	&Warlock::getTitle() const
{
	return (title);
}
void				Warlock::setTitle(std::string const &title)
{
	this->title = title;
}

// Member Functions
void	Warlock::introduce() const
{
	std::cout << name << ": I am " << name << ", " << title << "!" << std::endl;
}