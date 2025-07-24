/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakoni <rmakoni@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:14:37 by rmakoni           #+#    #+#             */
/*   Updated: 2025/07/24 13:36:40 by rmakoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN()
{
    std::cout << "RPN default constructor called" << std::endl;
}

RPN::RPN(const std::string &expression)
{
    _result = 0;
    std::cout << "RPN constructor called" << std::endl;
    if (!validateExpression(expression))
    {
        throw std::invalid_argument("Invalid expression");
    }
    calculate(expression);
    std::cout << "Result: " << _result << std::endl;
}

bool RPN::validateExpression(const std::string &expression)
{
    std::stack<double> validationStack;  // Use separate stack for validation
    std::stringstream ss(expression);
    std::string token;
    
    while (ss >> token)
    {
        if (isOperator(token))
        {
            if (validationStack.size() < 2) {
                return (false);
            }
            validationStack.pop();
            validationStack.pop();
            validationStack.push(1.0);  // Push dummy result
        }
        else
        {
            try {
                StringToNumber(token);
                validationStack.push(1.0);  // Push dummy number
            } catch (std::invalid_argument &e) {
                return (false);
            }
        }
    }
    
    // Valid RPN should have exactly one element left
    return (validationStack.size() == 1);
}

RPN::~RPN()
{
    std::cout << "RPN destructor called" << std::endl;
}

RPN::RPN(const RPN &other)
{
    std::cout << "RPN copy constructor called" << std::endl;
    *this = other;
}

RPN &RPN::operator=(const RPN &other)
{
    std::cout << "RPN assignment operator called" << std::endl;
    if (this != &other)
    {
        _operandStack = other._operandStack;
    }
    return (*this);
}

double RPN::performOperation(const std::string &op, const double &a, const double &b)
{
    if(op == "+")
        return (a + b);
    else if(op == "-")
        return (a - b);
    else if(op == "*")
        return (a * b);
    else if(op == "/")
    {
        if (b == 0)
            throw std::runtime_error("Division by zero");
        return (a / b);
    }
    else
        throw std::invalid_argument("Invalid operator");
}
bool RPN::isOperator(const std::string &c) const
{
    return (c == "+" || c == "-" || c == "*" || c == "/");
}

double RPN::StringToNumber(const std::string &str)
{
    try {
        return (std::stod(str));
    } catch (std::invalid_argument &e) {
        throw std::invalid_argument("Invalid number");
    }
}

void RPN::calculate(const std::string &expression)
{
    // Clear the stack to ensure clean calculation
    while (!_operandStack.empty()) {
        _operandStack.pop();
    }
    
    std::stringstream ss(expression);
    std::string token;
    
    while (ss >> token)
    {
        if (isOperator(token))
        {
            if (_operandStack.size() < 2) {
                throw std::runtime_error("Not enough operands for operator: " + token);
            }
          
            double b = _operandStack.top(); _operandStack.pop();
            double a = _operandStack.top(); _operandStack.pop();
            double result = performOperation(token, a, b);
            _operandStack.push(result);
        }
        else
        {
            double number = StringToNumber(token);
            _operandStack.push(number);
        }
    }
    
    // After processing all tokens, stack should have exactly one element
    if (_operandStack.size() != 1) {
        throw std::runtime_error("Invalid expression - final stack size: " + 
                               std::to_string(_operandStack.size()));
    }
    
    _result = _operandStack.top();
}