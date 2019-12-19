#include <iostream>
#include "AbstractVM.hpp"
#include "Number.hpp"
#include "Factory.hpp"
#include <regex>

int main()
{
    // std::vector<IOperand const *> stack;
    // Factory fac;
    // stack.push_back(fac.createOperand(Int32, "5"));
    // stack.push_back(fac.createOperand(Float, "10"));
    // stack.push_back(*stack[0] / *stack[1]);
    // for (std::vector<IOperand const *>::iterator it = stack.begin(); it != stack.end(); ++it)
    //     std::cout << "Value: " << (*it)->toString() 
    //             << "  Type: " << (*it)->getType() 
    //             << "  Precision:" << (*it)->getPrecision() << std::endl; 
    // std::cout << eight.toString() << std::endl;
    //Factory fac;
	// AbstractVM avm;
	// avm.push(Float, "5");
	// avm.push(Int32, "2");
	// try
	// {
	// 	avm.print();
	// 	avm.div();
	// }
	// catch(const std::exception& e)
	// {
	// 	std::cerr << e.what() << '\n';
	// }
	// avm.dump();
	std::string str("word1 asd");
	std::string st2("word2 asd123");
	std::regex rx("word1+.");
	std::cout << std::regex_match(str, rx) << std::endl;

}