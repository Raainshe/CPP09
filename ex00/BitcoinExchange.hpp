/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakoni <rmakoni@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 20:40:13 by rmakoni           #+#    #+#             */
/*   Updated: 2025/07/23 22:19:56 by rmakoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

class BitcoinExchange
{
    private:
        std::map<std::string, double> _data;
        std::string _filename;
        std::string _date;
        double _value;
        double _result;
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange &operator=(const BitcoinExchange &other);
		~BitcoinExchange();

        //process file
        void processFile(const std::string &filename);

        //utils
        std::string trim(const std::string &str);
        std::string findClosestDate(const std::string &date);

        //validations
        bool validateDate(const std::string &date);
        bool validateValue(const std::string &value);
        
};


#endif