/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakoni <rmakoni@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 09:47:57 by rmakoni           #+#    #+#             */
/*   Updated: 2025/07/25 17:26:10 by rmakoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <chrono>
#include <iomanip>

PmergeMe::PmergeMe()
{
    std::cout << "PmergeMe default constructor" << std::endl;
}

PmergeMe::PmergeMe(char **args)
{
    if (!validateArgs(args))
    {
        std::cerr << "Error" << std::endl;
        throw std::invalid_argument("Invalid arguments");
    }
    for (int i = 0; args[i]; i++)
    {
        int val = atoi(args[i]);
        _vector.push_back(val);
        _deque.push_back(val);
    }
}

void PmergeMe::printContainer(const std::vector<int> &vector, const std::string &label)
{
    std::cout << label;
    for (size_t i = 0; i < vector.size(); ++i)
        std::cout << vector[i] << " ";
    std::cout << std::endl;
}

void PmergeMe::printContainer(const std::deque<int> &deque, const std::string &label)
{
    std::cout << label;
    for (size_t i = 0; i < deque.size(); ++i)
        std::cout << deque[i] << " ";
    std::cout << std::endl;
}

// Ford-Johnson (merge-insert) sort for vector
void PmergeMe::fordJohnsonSortVector(std::vector<int> &vec)
{
    if (vec.size() <= 1)
        return;
    // Pairwise sort
    std::vector<std::pair<int, int> > pairs;
    size_t i = 0;
    for (; i + 1 < vec.size(); i += 2)
    {
        if (vec[i] > vec[i + 1])
            pairs.push_back(std::make_pair(vec[i], vec[i + 1]));
        else
            pairs.push_back(std::make_pair(vec[i + 1], vec[i]));
    }
    int last = -1;
    if (i < vec.size())
        last = vec[i];
    // Sort pairs by first element
    std::vector<int> mainChain;
    for (size_t j = 0; j < pairs.size(); ++j)
        mainChain.push_back(pairs[j].first);
    fordJohnsonSortVector(mainChain);
    // Insert second elements
    for (size_t j = 0; j < pairs.size(); ++j)
    {
        auto it = std::lower_bound(mainChain.begin(), mainChain.end(), pairs[j].second);
        mainChain.insert(it, pairs[j].second);
    }
    if (last != -1)
    {
        auto it = std::lower_bound(mainChain.begin(), mainChain.end(), last);
        mainChain.insert(it, last);
    }
    vec = mainChain;
}

// Ford-Johnson (merge-insert) sort for deque
void PmergeMe::fordJohnsonSortDeque(std::deque<int> &deq)
{
    if (deq.size() <= 1)
        return;
    // Pairwise sort
    std::deque<std::pair<int, int> > pairs;
    size_t i = 0;
    for (; i + 1 < deq.size(); i += 2)
    {
        if (deq[i] > deq[i + 1])
            pairs.push_back(std::make_pair(deq[i], deq[i + 1]));
        else
            pairs.push_back(std::make_pair(deq[i + 1], deq[i]));
    }
    int last = -1;
    if (i < deq.size())
        last = deq[i];
    // Sort pairs by first element
    std::deque<int> mainChain;
    for (size_t j = 0; j < pairs.size(); ++j)
        mainChain.push_back(pairs[j].first);
    fordJohnsonSortDeque(mainChain);
    // Insert second elements
    for (size_t j = 0; j < pairs.size(); ++j)
    {
        auto it = std::lower_bound(mainChain.begin(), mainChain.end(), pairs[j].second);
        mainChain.insert(it, pairs[j].second);
    }
    if (last != -1)
    {
        auto it = std::lower_bound(mainChain.begin(), mainChain.end(), last);
        mainChain.insert(it, last);
    }
    deq = mainChain;
}

void PmergeMe::processAndDisplay()
{
    // Print before
    printContainer(_vector, "Before: ");
    // Vector timing
    std::vector<int> vecCopy = _vector;
    auto startVec = std::chrono::high_resolution_clock::now();
    fordJohnsonSortVector(vecCopy);
    auto endVec = std::chrono::high_resolution_clock::now();
    // Deque timing
    std::deque<int> deqCopy = _deque;
    auto startDeq = std::chrono::high_resolution_clock::now();
    fordJohnsonSortDeque(deqCopy);
    auto endDeq = std::chrono::high_resolution_clock::now();
    // Print after
    printContainer(vecCopy, "After:  ");
    // Time output
    double timeVec = std::chrono::duration<double, std::micro>(endVec - startVec).count();
    double timeDeq = std::chrono::duration<double, std::micro>(endDeq - startDeq).count();
    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Time to process a range of " << vecCopy.size() << " elements with std::vector : " << timeVec << " us" << std::endl;
    std::cout << "Time to process a range of " << deqCopy.size() << " elements with std::deque  : " << timeDeq << " us" << std::endl;
}

bool PmergeMe::isSorted(std::vector<int> &vector)
{
    for (size_t i = 0; i < vector.size() - 1; i++)
        if (vector[i] > vector[i + 1])
            return false;
    return true;
}

bool PmergeMe::isSorted(std::deque<int> &deque)
{
    for (size_t i = 0; i < deque.size() - 1; i++)
        if (deque[i] > deque[i + 1])
            return false;
    return true;
}

PmergeMe::~PmergeMe()
{
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