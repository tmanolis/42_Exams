#include "TargetGenerator.hpp"
	
TargetGenerator::TargetGenerator() {}

TargetGenerator::TargetGenerator(TargetGenerator const &src)
{
	*this = src;
}

TargetGenerator	&TargetGenerator::operator=(TargetGenerator const &rhs)
{
	if (this != &rhs)
		this->target_array = rhs.getTargetArray();

	return (*this);
}

TargetGenerator::~TargetGenerator() {}

std::map<std::string, ATarget *>	TargetGenerator::getTargetArray() const
{
	return (target_array);
}

void		TargetGenerator::learnTargetType(ATarget *target_type)
{
	if (target_array.find(target_type->getType()) == target_array.end())
		target_array.insert(std::pair<std::string, ATarget *>(target_type->getType(), target_type));
}

void		TargetGenerator::forgetTargetType(std::string const &target_type)
{
	std::map<std::string, ATarget *>::iterator it = target_array.find(target_type);
	if (it != target_array.end())
		target_array.erase(it);
}

ATarget*	TargetGenerator::createTarget(std::string const &target_type)
{
	std::map<std::string, ATarget *>::iterator it = target_array.find(target_type);
	if (it != target_array.end())
		return (it->second);
	else
		return (NULL);
}