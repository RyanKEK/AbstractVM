#include "AbstractVM.hpp"
#include <algorithm>
#include <fstream>

AbstractVM::AbstractVM() : _fac(Factory())
{
	this->_commands = {
		"push", "pop",
		"dump", "assert",
		"add", "sub",
		"mul", "div",
		"mod", "print",
		"exit"
	};
}

AbstractVM::~AbstractVM()
{
}

void AbstractVM::push(eOperandType type, std::string const & value)
{
	this->_stack.push(this->_fac.createOperand(type, value));
}

void AbstractVM::pop()
{
	this->_stack.pop();
}

void AbstractVM::dump()
{
	std::stack<IOperand const *> tmp = this->_stack;
	while (!tmp.empty())
	{
		std::cout << tmp.top()->toString() << std::endl;
		tmp.pop();
	}
}

void AbstractVM::assert(eOperandType type, std::string const & value)
{
	if (this->_stack.top()->getType() != type)
		throw AbstractVM::AssertFailException();

	IOperand const * compareTo = this->_fac.createOperand(type, value);

	if (this->_stack.top()->toString() != compareTo->toString()){
		delete compareTo;	
		throw AbstractVM::AssertFailException();
	}
	delete compareTo;
}

void AbstractVM::add()
{
	if (this->_stack.size() < 2)
		throw AbstractVM::TooSmallStackException();
	IOperand const * firstOp = this->_stack.top();
	this->_stack.pop();
	IOperand const * res = *this->_stack.top() + *firstOp;
	this->_stack.pop();
	this->_stack.push(res);
}

void AbstractVM::sub()
{
	if (this->_stack.size() < 2)
		throw AbstractVM::TooSmallStackException();
	IOperand const * firstOp = this->_stack.top();
	this->_stack.pop();
	IOperand const * res = *this->_stack.top() - *firstOp;
	this->_stack.pop();
	this->_stack.push(res);
}

void AbstractVM::mul()
{
	if (this->_stack.size() < 2)
		throw AbstractVM::TooSmallStackException();
	IOperand const * firstOp = this->_stack.top();
	this->_stack.pop();
	IOperand const * res = *this->_stack.top() * *firstOp;
	this->_stack.pop();
	this->_stack.push(res);
}

void AbstractVM::div()
{
	if (this->_stack.size() < 2)
		throw AbstractVM::TooSmallStackException();
	IOperand const * firstOp = this->_stack.top();
	if (firstOp->toString().find_first_not_of("0.") == std::string::npos)
		throw DivisionByZeroException();
	this->_stack.pop();
	IOperand const * res = *this->_stack.top() / *firstOp;
	this->_stack.pop();
	this->_stack.push(res);
}

void AbstractVM::mod()
{
	if (this->_stack.size() < 2)
		throw AbstractVM::TooSmallStackException();
	IOperand const * firstOp = this->_stack.top();
	if (firstOp->toString().find_first_not_of("0.") == std::string::npos)
		throw DivisionByZeroException();
	this->_stack.pop();
	IOperand const * res = *this->_stack.top() % *firstOp;
	this->_stack.pop();
	this->_stack.push(res);
}

void AbstractVM::print()
{
	assert(Int8, this->_stack.top()->toString());
	std::cout << static_cast<char>(std::stoi(this->_stack.top()->toString())) << std::endl;
}

void AbstractVM::exit()
{
	std::exit(42);
}

void AbstractVM::start(std::string const filename)
{
	std::ifstream ifs;
	std::string line;

	ifs.open(filename);

	while (std::getline(ifs, line))
	{
		if (std::find(this->_commands.begin(), this->_commands.end(), line.substr(0, line.find_first_of(" \n"))) == this->_commands.end())
		{
			
		}



	}

}






















AbstractVM::AssertFailException::AssertFailException()
{
}

AbstractVM::AssertFailException::AssertFailException(AbstractVM::AssertFailException const & copyFrom)
{
	*this = copyFrom;
}

AbstractVM::AssertFailException::~AssertFailException() throw()
{
}

AbstractVM::AssertFailException & AbstractVM::AssertFailException::operator=(AbstractVM::AssertFailException const &)
{
	return (*this);
}

char const* AbstractVM::AssertFailException::what() const throw()
{
	return "Assert instruction failed";
}

AbstractVM::TooSmallStackException::TooSmallStackException()
{
}

AbstractVM::TooSmallStackException::TooSmallStackException(AbstractVM::TooSmallStackException const & copyFrom)
{
	*this = copyFrom;
}

AbstractVM::TooSmallStackException::~TooSmallStackException() throw()
{
}

AbstractVM::TooSmallStackException & AbstractVM::TooSmallStackException::operator=(AbstractVM::TooSmallStackException const &)
{
	return (*this);
}

char const* AbstractVM::TooSmallStackException::what() const throw()
{
	return "Stack is too small to do arithmetic";
}

AbstractVM::DivisionByZeroException::DivisionByZeroException()
{
}

AbstractVM::DivisionByZeroException::DivisionByZeroException(AbstractVM::DivisionByZeroException const & copyFrom)
{
	*this = copyFrom;
}

AbstractVM::DivisionByZeroException::~DivisionByZeroException() throw()
{
}

AbstractVM::DivisionByZeroException & AbstractVM::DivisionByZeroException::operator=(AbstractVM::DivisionByZeroException const &)
{
	return (*this);
}

char const* AbstractVM::DivisionByZeroException::what() const throw()
{
	return "Division by zero";
}