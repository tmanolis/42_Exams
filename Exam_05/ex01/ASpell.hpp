#ifndef	ASPELL_HPP
#define ASPELL_HPP

# include <cstdlib>
# include <iostream>
# include <string>

class	ATarget;

class	ASpell
{
	private:
	std::string	name;
	std::string	effects;

	public:
	ASpell();
	ASpell(ASpell const &src);
	ASpell(std::string Name, std::string Effects);
	virtual ~ASpell();
	ASpell	&operator=(ASpell const &rhs);

	std::string getName();
	std::string getEffects();

	virtual ASpell	*clone() const = 0;

	void	launch(ATarget const &src);

};

#endif