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

std::string	ASpell::getName()
{
	return (name);
}

std::string	Spell::getEffects()
{
	return (effects);
}

void	Spell::launch(ATarget const &src)
{
	src.getHitBySpell(*this);
}