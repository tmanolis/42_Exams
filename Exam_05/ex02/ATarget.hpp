#ifndef	ATARGET_HPP
#define ATARGET_HPP

# include <cstdlib>
# include <iostream>
# include <string>

class ASpell;

class ATarget
{
private:
	std::string	type;

public:
	ATarget();
	ATarget(ATarget const &src);
	ATarget(std::string Type);
	virtual ~ATarget();

	ATarget	&operator=(ATarget const &rhs);

	std::string const	&getType() const;

	virtual ATarget	*clone() const = 0;

	void	getHitBySpell(ASpell const &src) const;

};

# include "ASpell.hpp"

#endif