#ifndef SPELLBOOK_HPP
#define SPELLBOOK_HPP

# include <map>

# include "ASpell.hpp"

class	SpellBook
{
	private:
	std::map<std::string, ASpell*>	spellbook;
	
	SpellBook(SpellBook const &src);
	SpellBook	&operator=(SpellBook const &rhs);

	public:
	SpellBook();
	~SpellBook();

	std::map<std::string, ASpell*>	getSpellbook() const;

	void	learnSpell(ASpell* spell);
	void	forgetSpell(std::string const &spell_name);
	ASpell	*createSpell(std::string const &spell_name);
	
};


#endif