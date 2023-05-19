#include "SpellBook.hpp"

SpellBook::SpellBook()
{

}

SpellBook::SpellBook(SpellBook const &src)
{
	*this = src;
}

SpellBook::~SpellBook()
{

}

SpellBook	&SpellBook::operator=(SpellBook const &rhs)
{
	if (this != &rhs)
		this->spellbook = rhs.getSpellbook();

	return (*this);
}

std::map<std::string, ASpell*>	SpellBook::getSpellbook() const
{
	return (spellbook);
}

void	SpellBook::learnSpell(ASpell *spell)
{
	if (spell && spellbook.find(spell->getName()) == spellbook.end())
		spellbook.insert(std::pair<std::string, ASpell*>(spell->getName(), spell));
}

void	SpellBook::forgetSpell(std::string const &spell_name)
{
	std::map<std::string, ASpell*>::iterator	it = spellbook.find(spell_name);
	if (it != spellbook.end())
		spellbook.erase(it);
}

ASpell	*SpellBook::createSpell(std::string const &spell_name)
{
	std::map<std::string, ASpell*>::iterator	it = spellbook.find(spell_name);
	if (it != spellbook.end())
		return (it->second);
	else
		return (NULL);
}