#include "AbstractVM.hpp"
#include <algorithm>
#include <fstream>
#include <regex>
#include <map>

AbstractVM::AbstractVM() : _fac(Factory())
{

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
	std::map<std::string, int> mapOfMarks = { { "Riti", 2 }, { "Jack", 4 } };
	std::map<std::string, void (AbstractVM::*)()> fPtrs = {
		{"pop", AbstractVM::pop},
		{"dump", AbstractVM::dump},
		{"add", AbstractVM::add},
		{"sub", AbstractVM::sub},
		{"mul", AbstractVM::mul},
		{"div", AbstractVM::div},
		{"mod", AbstractVM::mod},
		{"print", AbstractVM::print},
		{"exit", AbstractVM::exit}
	};
	std::regex pushAssertRegex("(push|assert) (Int(8|16|32)|Float|Double)\\(-?[0-9]+\\.?[0-9]+\\)\n");
	std::regex otherRegex("(pop|dump|add|sub|mul|div|mod|print|exit)(;.*)?\n");

	ifs.open(filename);	

	while (std::getline(ifs, line))
	{
		if (line == "\n")
			continue ;
		if (line == ";;\n")
		if (std::regex_match(line, otherRegex))
		{
			_commands.push_back(fPtrs[line.substr(0, line.find('\n'))]);
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