#ifndef WARLOCK_HPP
#define WARLOCK_HPP

# include <cstdlib>
# include <iostream>
# include <string>

class	Warlock
{
	private:
		std::string	name;
		std::string	title;

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
		void introduce() const;
};

#endif

