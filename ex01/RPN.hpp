/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakoni <rmakoni@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:20:17 by rmakoni           #+#    #+#             */
/*   Updated: 2025/07/24 13:25:03 by rmakoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <string>
#include <stack>
#include <sstream>

class RPN
{
    private:
        std::stack<double> _operandStack;
        double _result;
        bool isOperator(const std::string &c) const;
        double StringToNumber(const std::string &str);
        double performOperation(const std::string &op, const double &a, const double &b);
        bool validateExpression(const std::string &expression);
        
    public:
        RPN(const std::string &expression);
        RPN();
        RPN(const RPN &other);
        RPN &operator=(const RPN &other);
        ~RPN();


        void calculate(const std::string &expression);

};

#endif