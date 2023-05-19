#ifndef WARLOCK_HPP
#define WARLOCK_HPP

# include <cstdlib>
# include <iostream>
# include <string>

# include "ASpell.hpp"
# include "SpellBook.hpp"

class	Warlock
{
	private:
		std::string	name;
		std::string	title;
		SpellBook	spellbook;

		Warlock();
		Warlock(Warlock const &src);
		// Operator Overload
		Warlock	&operator=(Warlock const &rhs);
		
	public:
		Warlock(std::string const &name, std::string const &title);
		~Warlock();
		// Accessors
		std::string const	&getName() const;
		std::string const	&getTitle() const;
		void				setTitle(std::string const &title);
		// Member Functions
		void 	introduce() const;
		void	learnSpell(ASpell *spell);
		void	forgetSpell(std::string	spell_name); // si pb ajouter const &
		void	launchSpell(std::string spell_name, ATarget const &target);



};

#endif

