#ifndef	TARGETGENERATOR_HPP
#define TARGETGENERATOR_HPP

# include <cstdlib>
# include <iostream>
# include <string>
# include <map>

# include "ATarget.hpp"

class TargetGenerator
{
private:
	std::map<std::string, ATarget *>	target_array;

	TargetGenerator(TargetGenerator const &src);
	TargetGenerator	&operator=(TargetGenerator const &rhs);
	
public:
	TargetGenerator();
	~TargetGenerator();

	std::map<std::string, ATarget *>	getTargetArray() const
	;

	void		learnTargetType(ATarget *target_type);
	void		forgetTargetType(std::string const &target_type);
	ATarget*	createTarget(std::string const &target_type);
};

#endif