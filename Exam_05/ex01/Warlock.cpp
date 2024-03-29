#include "Warlock.hpp"

Warlock::Warlock()
{

}

Warlock::Warlock(Warlock const &src)
{
	*this = src;
}

Warlock::Warlock(std::string const &Name, std::string const &Title) : name(Name), title(Title)
{
	std::cout << name << ": This looks like another boring day." << std::endl;
}

Warlock::~Warlock()
{
	std::cout << name << ": My job here is done!" << std::endl;
}

// Operator Overload
Warlock	&Warlock::operator=(Warlock const &rhs)
{
	if (this != &rhs)
	{
		this->name = rhs.getName();
		this->title = rhs.getTitle();
	}

	return (*this);
}

// Accessors
std::string const	&Warlock::getName() const
{
	return (name);
}
std::string const	&Warlock::getTitle() const
{
	return (title);
}
void				Warlock::setTitle(std::string const &title)
{
	this->title = title;
}

// Member Functions
void	Warlock::introduce() const
{
	std::cout << name << ": I am " << name << ", " << title << "!" << std::endl;
}

void	Warlock::learnSpell(ASpell *spell)
{
	if (spell && spellbook.find(spell->getName()) == spellbook.end())
		spellbook.insert(std::pair<std::string, ASpell*>(spell->getName(), spell));
}

void	Warlock::forgetSpell(std::string spell_name)
{
	std::map<std::string, ASpell*>::iterator	it = spellbook.find(spell_name);
	if (it != spellbook.end())
		spellbook.erase(it);
}

void	Warlock::launchSpell(std::string spell_name, ATarget const &target)
{
	std::map<std::string, ASpell*>::iterator	it = spellbook.find(spell_name);
	if (it != spellbook.end())
		it->second->launch(target);
}