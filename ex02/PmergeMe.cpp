/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakoni <rmakoni@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 09:47:57 by rmakoni           #+#    #+#             */
/*   Updated: 2025/07/25 10:29:19 by rmakoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
    std::cout << "PmergeMe default constructor" << std::endl;
}

PmergeMe::PmergeMe(char **args)
{
    std::cout << "PmergeMe constructor" << std::endl;
    if (!validateArgs(args))
        throw std::invalid_argument("Invalid arguments");
    // add args to vector and deque
    for (int i = 0; args[i]; i++)
    {
        _vector.push_back(atoi(args[i]));
        _deque.push_back(atoi(args[i]));
    }

    //check if one of them is already sorted
    if (isSorted(_vector))
    {
        std::cout << "The given arguments are already sorted" << std::endl;
        return;
    }

    //sort them
    std::cout << "Before: ";
    for (size_t i = 0; i < _vector.size(); i++)
        std::cout << _vector[i] << " ";
    std::cout << std::endl;
}

bool PmergeMe::isSorted(std::vector<int> &vector)
{
    for (size_t i = 0; i < vector.size() - 1; i++)
        if (vector[i] > vector[i + 1])
            return false;
    return true;
}

PmergeMe::~PmergeMe()
{
    std::cout << "PmergeMe destructor" << std::endl;
}

bool PmergeMe::validateArgs(char **args)
{
    for (int i = 0; args[i]; i++)
    {
        for (int j = 0; args[i][j]; j++)
        {
            if (!isdigit(args[i][j]))
                return false;
        }
    }
    return true;
}