#include "ASpell.hpp"

ASpell::ASpell()
{

}

ASpell::ASpell(ASpell const &src)
{
	*this = src;
}

ASpell::ASpell(std::string Name, std::string Effects) : name(Name), effects(Effects)
{

}

ASpell::~ASpell()
{

}
ASpell	&ASpell::operator=(ASpell const &rhs)
{
	if (this != &rhs)
	{
		this->name = rhs.getName();
		this->effects = rhs.getEffects();
	}

	return (*this);
}

std::string const	ASpell::getName() const
{
	return (name);
}

std::string const	ASpell::getEffects() const
{
	return (effects);
}

void	ASpell::launch(ATarget const &src)
{
	src.getHitBySpell(*this);
}