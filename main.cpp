#include <iostream>
#include "AbstractVM.hpp"
#include "Number.hpp"
#include "Factory.hpp"
#include <regex>
#include <iomanip>

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
	// std::string str("push Int8(32)");
	// std::string str2("assert Double(25.4)");
	// std::string space = "asd ";
	std::regex rx("push (Int(8|16|32)|Float|Double)\\((-|+)?[0-9]+\\.?[0-9]*\\)(;.*)?\n");
	std::cout << std::regex_match("push Float(1.9512312)\n", rx) << std::endl;
	double d = 0.0012 + 1.0;
	double d1 = 1.123123123123123123123123123123123123;
	std::cout.precision(1);
	std::cout << std::fixed << d << std::endl << d1 << std::endl << "1.123123123123123123123123123123123123" << std::endl;
	//std::cout << std::regex_match(str2, rx) << std::endl;
}