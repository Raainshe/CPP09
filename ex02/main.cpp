/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakoni <rmakoni@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:27:52 by rmakoni           #+#    #+#             */
/*   Updated: 2025/07/25 17:26:18 by rmakoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    try {
        PmergeMe pmergeMe(argv + 1);
        pmergeMe.processAndDisplay();
    } catch (const std::exception &e) {
        // Error already printed in constructor
        return 1;
    }
    return 0;
}