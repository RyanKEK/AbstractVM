#ifndef ABSTRACTVM_HPP
#define ABSTRACTVM_HPP

#include "Factory.hpp"
#include <stack>
#include <stdexcept>

class AbstractVM
{
private:

	std::stack<IOperand const *>		_stack;
	Factory								_fac;
	std::deque<void (AbstractVM::*)()>	_commands;
	//std::vector<std::string>			_operands;

public:

	AbstractVM();
	~AbstractVM();

	void push(eOperandType type, std::string const & value);
	void pop();
	void dump();
	void assert(eOperandType type, std::string const & value);
	void add();
	void sub();
	void mul();
	void div();
	void mod();
	void print();
	void exit();

	void start(std::string const filename);





	class AssertFailException : public std::exception
	{
	public:
		AssertFailException();
		AssertFailException(AssertFailException const & copyFrom);
		virtual ~AssertFailException() throw();

		virtual char const* what() const throw();

		AssertFailException & operator=(AssertFailException const &);
	};

	class TooSmallStackException : public std::exception
	{
	public:
		TooSmallStackException();
		TooSmallStackException(TooSmallStackException const & copyFrom);
		virtual ~TooSmallStackException() throw();

		virtual char const* what() const throw();

		TooSmallStackException & operator=(TooSmallStackException const &);
	};
	
	class DivisionByZeroException : public std::exception
	{
	public:
		DivisionByZeroException();
		DivisionByZeroException(DivisionByZeroException const & copyFrom);
		virtual ~DivisionByZeroException() throw();

		virtual char const* what() const throw();

		DivisionByZeroException & operator=(DivisionByZeroException const &);
	};

};




#endif