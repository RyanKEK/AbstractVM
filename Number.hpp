#ifndef NUMBER_HPP
#define NUMBER_HPP

#include "IOperand.hpp"
#include "Factory.hpp"
#include <typeinfo>
#include <limits>
#include <math.h>

template<typename T>
class Number : public IOperand
{
private:

    T			_value;
    std::string	_strValue;
    Factory		_fac;

public:
    
    Number(T value) : _value(value), _strValue(std::to_string(value)), _fac(Factory()){};
    ~Number(){};

    virtual int getPrecision( void ) const {return (std::numeric_limits<T>::digits10);};
    virtual eOperandType getType( void ) const {
        char type = typeid(T).name()[0];
        switch (type)
        {
        case 'a':
            return (eOperandType(Int8));
            break;
        case 's':
            return (eOperandType(Int16));
            break;
        case 'i':
            return (eOperandType(Int32));
            break;
        case 'f':
            return (eOperandType(Float));
            break;
        case 'd':
            return (eOperandType(Double));
            break;
        default:
            break;
        }
    };
    virtual IOperand const * operator+( IOperand const & rhs ) const {
        eOperandType type = this->getType() > rhs.getType() ? this->getType() : rhs.getType();

        if (type < Float)
        {
            return (_fac.createOperand(type, std::to_string(this->_value + std::stoi(rhs.toString()))));
        }
        return (_fac.createOperand(type, std::to_string(this->_value + std::stod(rhs.toString()))));
    };

    virtual IOperand const * operator-( IOperand const & rhs ) const {
        eOperandType type = this->getType() > rhs.getType() ? this->getType() : rhs.getType();

        if (type < Float)
        {
            return (_fac.createOperand(type, std::to_string(this->_value - std::stoi(rhs.toString()))));
        }
        return (_fac.createOperand(type, std::to_string(this->_value - std::stod(rhs.toString()))));
    };

    virtual IOperand const * operator*( IOperand const & rhs ) const {
        eOperandType type = this->getType() > rhs.getType() ? this->getType() : rhs.getType();

        if (type < Float)
        {
            return (_fac.createOperand(type, std::to_string(this->_value * std::stoi(rhs.toString()))));
        }
        return (_fac.createOperand(type, std::to_string(this->_value * std::stod(rhs.toString()))));
    };

    virtual IOperand const * operator/( IOperand const & rhs ) const {
        eOperandType type = this->getType() > rhs.getType() ? this->getType() : rhs.getType();

        if (type < Float)
        {
            return (_fac.createOperand(type, std::to_string(this->_value / std::stoi(rhs.toString()))));
        }
        return (_fac.createOperand(type, std::to_string(this->_value / std::stod(rhs.toString()))));
    };
    virtual IOperand const * operator%( IOperand const & rhs ) const {
        eOperandType type = this->getType() > rhs.getType() ? this->getType() : rhs.getType();

        if (type < Float)
        {
            return (_fac.createOperand(type, std::to_string(static_cast<int64_t>(this->_value) % std::stoi(rhs.toString()))));
        }
        return (_fac.createOperand(type, std::to_string(fmod(this->_value, std::stod(rhs.toString())))));
    };
    virtual std::string const & toString(void) const {return (this->_strValue);};
};

#endif
