#include "ATarget.hpp"

ATarget::ATarget()
{

}

ATarget::ATarget(ATarget const &src)
{
	*this = src;
}

ATarget::ATarget(std::string Type) : type(Type)
{

}

ATarget::~ATarget()
{

}

ATarget	&ATarget::operator=(ATarget const &rhs)
{
	if (this != &rhs)
	{
		this->type = rhs.getType();
	}

	return (*this);
}


std::string const	&ATarget::getType() const
{
	return (type);
}

void	ATarget::getHitBySpell(ASpell const &src) const
{
	std::cout << type << " has been " << src.getEffects() << "!" << std::endl;
}
