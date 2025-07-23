/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakoni <rmakoni@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 21:17:08 by rmakoni           #+#    #+#             */
/*   Updated: 2025/07/23 22:12:25 by rmakoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
    std::cout << "Loading database..." << std::endl;
    std::ifstream file("database.csv");
    std::string line;
    
    // Skip header line
    std::getline(file, line);
    
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string date, rate;
        std::getline(ss, date, ',');
        std::getline(ss, rate, ',');
        std::pair<std::string, double> element(date, std::stod(rate));
        _data.insert(element);
    }
    file.close();
    std::cout << "\nDatabase loaded successfully" << std::endl;
}

BitcoinExchange::~BitcoinExchange()
{
    std::cout << "BitcoinExchange destructor called" << std::endl;
}

void BitcoinExchange::processFile(const std::string &filename)
{
    try {
        std::ifstream file(filename);
        std::string line;
        
        // Skip header line
        std::getline(file, line);
        
        while (std::getline(file, line))
        {
            std::stringstream ss(line);
            
            std::string date, value;
            std::getline(ss, date, '|');
            std::getline(ss, value);
            //trim the whitespaces
            date = trim(date);
            value = trim(value);
            if (validateDate(date) && validateValue(value))
            {
                std::string closestDate = findClosestDate(date);
                if (closestDate.empty())
                {
                    std::cerr << "Error: no data available for date => " << date << std::endl;
                }
                else
                {
                    _date = date;  // Keep original date for display
                    _value = std::stod(value);
                    _result = _data[closestDate] * _value;  // Use closest date's rate
                    std::cout << _date << " => " << _value << " = " << _result << std::endl;
                }
            }
            else
            {
                if (!validateDate(date))
                    std::cerr << "Error: bad input => " << date << std::endl;
                if (!validateValue(value))
                    std::cerr << "Error: bad input => " << value << std::endl;
            }
        }
        file.close();
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

std::string BitcoinExchange::findClosestDate(const std::string &date)
{
    // First check if exact date exists
    std::map<std::string, double>::iterator exact = _data.find(date);
    if (exact != _data.end())
        return date;  // Exact match found
    
    // Find the first date >= target date
    std::map<std::string, double>::iterator it = _data.lower_bound(date);
    
    // If target date is before all dates in database
    if (it == _data.begin())
        return "";  // No valid earlier date exists
    
    // Move to the previous date (closest earlier date)
    --it;
    return it->first;
}

bool BitcoinExchange::validateDate(const std::string &date)
{
    std::stringstream ss(date);
    std::string year, month, day;
    std::getline(ss, year, '-');
    std::getline(ss, month, '-');
    std::getline(ss, day);
    if (year.length() != 4 || month.length() != 2 || day.length() != 2)
        return false;
    return true;
}

bool BitcoinExchange::validateValue(const std::string &value)
{
    std::stringstream ss(value);
    std::string string;
    std::getline(ss, string);
    if (string.length() == 0)
        return false;
    if (std::stod(string) < 0)
        return false;
    if (std::stod(string) > 1000)
        return false;
    return true;
}

std::string BitcoinExchange::trim(const std::string &str)
{
       // Find first non-whitespace character
       size_t start = str.find_first_not_of(" \t\r\n");
       if (start == std::string::npos)
           return "";  // String is all whitespace
       
       // Find last non-whitespace character
       size_t end = str.find_last_not_of(" \t\r\n");
       
       // Return substring from start to end
       return str.substr(start, end - start + 1);
}