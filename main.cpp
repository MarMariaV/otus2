﻿// homework2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "lib.h"
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>


const int n_ip = 4;
using ipLineType = std::array<int, n_ip>;
using VipLineType = std::vector<ipLineType>;

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
	std::vector<std::string> r;

	std::string::size_type start = 0;
	std::string::size_type stop = str.find_first_of(d);
	while (stop != std::string::npos)
	{
		r.push_back(str.substr(start, stop - start));

		start = stop + 1;
		stop = str.find_first_of(d, start);
	}

	r.push_back(str.substr(start));

	return r;
}

void printFunc(VipLineType ip_pool)
{
	for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
	{
		for (auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
		{
			if (ip_part != ip->cbegin())
			{
				std::cout << ".";

			}
			std::cout << *ip_part;
		}
		std::cout << std::endl;
	}
}

int main(/*int argc, char const *argv[]*/)
{
	
	try
	{
		ipLineType ip_array;
		VipLineType ip_pool;

		for (std::string line; std::getline(std::cin, line);)
		{
			auto temp_str = split(split(line, '\t').at(0), '.');

			for (int i = 0; i < n_ip; ++i)
			{
				ip_array[i] = std::stoi(temp_str.at(i));
			}			
			ip_pool.push_back(ip_array);
		}

		const auto& is_first = [](VipLineType ip_pool, int index, int value)
		{
			decltype (ip_pool) result;
			for (ipLineType ip : ip_pool)
			{
				if (ip.at(index) == value)
					result.push_back(std::move(ip));
			}
			return result;
		};

		const auto& is_first_second = [](VipLineType ip_pool, int index1, int value1, int index2, int value2)
		{
			decltype (ip_pool) result;
			for (ipLineType ip : ip_pool)
			{
				if (ip.at(index1) == value1 && ip.at(index2) == value2)
					result.push_back(std::move(ip));
			}
			return result;
		};

		const auto& is_one_of = [](VipLineType ip_pool, int value)
		{
			decltype (ip_pool) result;
			for (ipLineType ip : ip_pool)
			{
				if (std::find(std::begin(ip), std::end(ip), value) != std::end(ip))
				{
					result.push_back(std::move(ip));
				}
			}
			return result;
		};
		
		std::sort(ip_pool.begin(), ip_pool.end(), std::greater<ipLineType>{});
		auto result1 = is_first(ip_pool, 0, 1);
		auto result2 = is_first_second(ip_pool, 0, 46, 1, 70);
		auto result3 = is_one_of(ip_pool, 46);

		printFunc(ip_pool);
		printFunc(result1);
		printFunc(result2);
		printFunc(result3);


		// 222.173.235.246
		// 222.130.177.64
		// 222.82.198.61
		// ...
		// 1.70.44.170
		// 1.29.168.152
		// 1.1.234.8



		// TODO filter by first byte and output
		// ip = filter(1)

		// 1.231.69.33
		// 1.87.203.225
		// 1.70.44.170
		// 1.29.168.152
		// 1.1.234.8

		// TODO filter by first and second bytes and output
		// ip = filter(46, 70)

		// 46.70.225.39
		// 46.70.147.26
		// 46.70.113.73
		// 46.70.29.76

		// TODO filter by any byte and output
		// ip = filter_any(46)

		// 186.204.34.46
		// 186.46.222.194
		// 185.46.87.231
		// 185.46.86.132
		// 185.46.86.131
		// 185.46.86.131
		// 185.46.86.22
		// 185.46.85.204
		// 185.46.85.78
		// 68.46.218.208
		// 46.251.197.23
		// 46.223.254.56
		// 46.223.254.56
		// 46.182.19.219
		// 46.161.63.66
		// 46.161.61.51
		// 46.161.60.92
		// 46.161.60.35
		// 46.161.58.202
		// 46.161.56.241
		// 46.161.56.203
		// 46.161.56.174
		// 46.161.56.106
		// 46.161.56.106
		// 46.101.163.119
		// 46.101.127.145
		// 46.70.225.39
		// 46.70.147.26
		// 46.70.113.73
		// 46.70.29.76
		// 46.55.46.98
		// 46.49.43.85
		// 39.46.86.85
		// 5.189.203.46
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}


	return 0;
}
