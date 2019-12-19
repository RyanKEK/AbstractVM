#include "Factory.hpp"
#include "Number.hpp"

Factory::Factory()
{
}

Factory::~Factory()
{
}

IOperand const * Factory::createInt8(std::string const & value) const
{
    return (new Number<int8_t>(std::stoi(value)));
}

IOperand const * Factory::createInt16(std::string const & value) const
{
    return (new Number<int16_t>(std::stoi(value)));
}

IOperand const * Factory::createInt32(std::string const & value) const
{
    return (new Number<int32_t>(std::stoi(value)));
}

IOperand const * Factory::createFloat(std::string const & value) const
{
    return (new Number<float>(std::stof(value)));
}

IOperand const * Factory::createDouble(std::string const & value) const
{
    return (new Number<double>(std::stod(value)));
}

IOperand const * Factory::createOperand(eOperandType type, std::string const & value) const
{
    std::vector<IOperand const *(Factory::*)(std::string const &) const> vec = {
        &Factory::createInt8,
        &Factory::createInt16,
        &Factory::createInt32,
        &Factory::createFloat,
        &Factory::createDouble
    };
    return ((this->*vec[type])(value));
}