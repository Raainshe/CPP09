/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakoni <rmakoni@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:20:06 by rmakoni           #+#    #+#             */
/*   Updated: 2025/07/24 13:32:06 by rmakoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <expression>" << std::endl;
        return (1);
    }
    try {
        RPN rpn(argv[1]);
        rpn.calculate(argv[1]);
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return (1);
    }
    return (0);
}