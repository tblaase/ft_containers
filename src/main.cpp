/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:32:13 by tblaase           #+#    #+#             */
/*   Updated: 2022/04/27 20:56:10 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <chrono>

#include <vector>
// #include <map>

#include "../include/vector.hpp"

int main()
{
	std::cout << std::endl << "----------------------------------------------------------" << std::endl << std::endl;

	// ##### Test for the std::vector #####
	std::cout << "##### Test of the std::vector #####" << std::endl;
	{
		std::chrono::steady_clock::time_point std_start = std::chrono::high_resolution_clock::now();
		std::vector< int > *a = new std::vector< int >(40000000);
		std::cout << "\ta size: " << a->size() << std::endl;
		std::cout << "\ta capacity: " << a->capacity() << std::endl;
		try
		{
			std::cout << "\tresizing a now" << std::endl;
			a->resize(40000001);
		}
		catch (std::exception &e)
		{
			std::cerr << "\texception cought!!!! " << e.what() << std::endl;
		}
		std::cout << "\ta size: " << a->size() << std::endl;
		std::cout << "\ta capacity: " << a->capacity() << std::endl;
		delete a;
		std::chrono::steady_clock::time_point std_end = std::chrono::high_resolution_clock::now();

		std::cout << std::endl << "\tstd::vector took " << std::chrono::duration_cast<std::chrono::milliseconds>(std_end - std_start).count() << " milliseconds to run." << std::endl;
	}

	std::cout << std::endl << "----------------------------------------------------------" << std::endl << std::endl;

	// ##### Test of my ft::vector #####
	std::cout << "##### Test of my ft::vector #####" << std::endl;
	{
		std::chrono::steady_clock::time_point ft_start = std::chrono::high_resolution_clock::now();
		ft::vector< int > *b = new ft::vector< int >(40000000);
		std::cout << "\tb size: " << b->size() << std::endl;
		std::cout << "\tb capacity: " << b->capacity() << std::endl;
		try
		{
			std::cout << "\tresizing b now" << std::endl;
			b->resize(40000001);
		}
		catch (std::exception &e)
		{
			std::cerr << "\texception cought!!!! " << e.what() << std::endl;
		}
		std::cout << "\tb size: " << b->size() << std::endl;
		std::cout << "\tb capacity: " << b->capacity() << std::endl;
		delete b;
		std::chrono::steady_clock::time_point ft_end = std::chrono::high_resolution_clock::now();

		std::cout << std::endl << "\tft::vector took " << std::chrono::duration_cast<std::chrono::milliseconds>(ft_end - ft_start).count() << " milliseconds to run." << std::endl;
	}

	std::cout << std::endl << "----------------------------------------------------------" << std::endl << std::endl;
	// for (size_t i = 0; i < 20; ++i)
	// {
	// 	a.push_back(i);
	// 	// b.push_back(i);
	// }

	// std::cout << "size: " << a.size() << std::endl;
	// std::cout << "capacity: " << a.capacity() << std::endl;


	// a.push_back(200);

	// std::cout << "a size: " << a.size() << std::endl;
	// std::cout << "a capacity: " << a.capacity() << std::endl;

	// for (size_t i = 0; i < a.capacity(); ++i)
	// 	std::cout << a[i] << std::endl;

	// std::cout << a.front() << std::endl;
	// std::cout << std::endl;
	// std::cout << b.front() << std::endl;



	// for (size_t i = 0; i < b.capacity(); ++i)
	// 	std::cout << b[i] << std::endl;


	// for (int i = 0; i < 7; i++)
	// 	a.push_back(i + 32);

	// for (size_t i = 0; i < a.capacity(); ++i)
	// 	std::cout << (int)a[i] << std::endl;

	// std::cout << "size: " << a.size() << std::endl;
	// std::cout << "capacity: " << a.capacity() << std::endl;

	// // for (int i = a.size(); i < 96; ++i)
	// // 	a.push_back(i);

	// // std::cout << "size: " << a.size() << std::endl;
	// // std::cout << "capacity: " << a.capacity() << std::endl;

	// std::cout << "max size for b is: " << b.max_size() << std::endl;

	// try{
	// 	b.reserve(4611686018427387);
	// 	// b.reserve(65165131131345455);
	// }
	// catch (std::exception &e)
	// {
	// 	std::cerr << "\033[31mthere was an error:\t";
	// 	std::cerr << e.what() <<std::endl;
	// 	std::cerr << "\033[0m";
	// }

	// std::cout << "size: " << b.size() << std::endl;
	// std::cout << "capacity: " << b.capacity() << std::endl;

	// std::cout << "max: " << a.max_size() << std::endl;

	// for (size_t i = 0; i < a.capacity(); ++i)
	// 	std::cout << (int)a[i] << std::endl;

	// std::cout << "size: " << a.size() << std::endl;
	// std::cout << "capacity: " << a.capacity() << std::endl;

	// system("leaks ft_containers");

	return (0);
}