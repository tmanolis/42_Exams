#ifndef WARLOCK_HPP
#define WARLOCK_HPP

# include <cstdlib>
# include <iostream>
# include <string>
# include <map>

# include "ASpell.hpp"

class	Warlock
{
	private:
		std::string	name;
		std::string	title;
		std::map<std::string, ASpell*>	spellbook;

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
		void	forgetSpell(std::string	spell_name);



};

#endif

