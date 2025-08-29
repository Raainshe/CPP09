/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakoni <rmakoni@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 09:48:03 by rmakoni           #+#    #+#             */
/*   Updated: 2025/08/29 10:44:36 by rmakoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <ctime>
#include <cctype>

class PmergeMe
{
    private:
        std::vector<int> _vector;
        std::deque<int> _deque;
        bool validateArgs(char **args);
        bool isSorted(std::vector<int> &vector);
        bool isSorted(std::deque<int> &deque);
        void fordJohnsonSortVector(std::vector<int> &vector);
        void fordJohnsonSortDeque(std::deque<int> &deque);
        void printContainer(const std::vector<int> &vector, const std::string &label);
        void printContainer(const std::deque<int> &deque, const std::string &label);
    public:
        PmergeMe();
        PmergeMe(char **args);
        ~PmergeMe();
        void processAndDisplay(); // Triggers sorting, timing, and output
};

#endif