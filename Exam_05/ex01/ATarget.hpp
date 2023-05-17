#ifndef	ATARGET_HPP
#define ATARGET_HPP

# include "ASpell.hpp"

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

	std::string const	&getType();

	virtual ATarget	*clone() const = 0;

	void	getHitBySpell(ASpell const &src);
};


#endif