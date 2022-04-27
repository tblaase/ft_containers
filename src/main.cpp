/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:32:13 by tblaase           #+#    #+#             */
/*   Updated: 2022/04/27 23:21:51 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
// #include <chrono>

#include <sys/time.h>

#include <vector>
// #include <map>

#include "../include/vector.hpp"

int main()
{

	std::cout << "test value: ";
	long long test_val;
	std::string test_str;
	std::getline(std::cin, test_str);
	if (test_str.length() == 0)
		test_val = 50000000;
	else
		test_val = std::atoll(test_str.c_str());

	std::cout << "test value set: " << test_val << std::endl;

	std::cout << "resize value: ";
	long long resize_val;
	std::string resize_str;
	std::getline(std::cin, resize_str);
	if (resize_str.length() == 0)
		resize_val = 50000001;
	else
		resize_val = std::atoll(resize_str.c_str());

	std::cout << "resize value set: " << resize_val << std::endl;

	struct timeval start, end;
	long seconds;
	long microseconds;

	std::cout << std::endl << "----------------------------------------------------------" << std::endl << std::endl;

	// ##### Test for the std::vector #####
	std::cout << "##### Test of the std::vector #####" << std::endl;
	{
		gettimeofday(&start, NULL);
		// std::chrono::steady_clock::time_point std_start = std::chrono::steady_clock::now();
		std::vector< int > *a;
		try
		{
			a = new std::vector< int >(test_val);
		}
		catch (std::exception &e)
		{
			std::cerr << "\texception caught!!!! " << e.what() << std::endl;
			gettimeofday(&end, NULL);
			// std::chrono::steady_clock::time_point std_end = std::chrono::steady_clock::now();

			seconds = (end.tv_sec - start.tv_sec);
			microseconds = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
			std::cout << std::endl << "\tstd::vector took " << (microseconds / 1000000) << "," << (microseconds % 1000000) << " seconds" << std::endl;
			// std::cout << std::endl << "\tstd::vector took " << std::chrono::duration_cast<std::chrono::microseconds>(std_end - std_start).count() << " microseconds to run." << std::endl;
			goto ft_vector;
		}
		std::cout << "\ta size: " << a->size() << std::endl;
		std::cout << "\ta capacity: " << a->capacity() << std::endl;
		try
		{
			std::cout << "\tresizing a now" << std::endl;
			a->resize(resize_val);
		}
		catch (std::exception &e)
		{
			std::cerr << "\texception caught!!!! " << e.what() << std::endl;
		}
		std::cout << "\ta size: " << a->size() << std::endl;
		std::cout << "\ta capacity: " << a->capacity() << std::endl;

		delete a;
		gettimeofday(&end, NULL);
		// std::chrono::steady_clock::time_point std_end = std::chrono::steady_clock::now();

		seconds = (end.tv_sec - start.tv_sec);
		microseconds = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
		std::cout << std::endl << "\tstd::vector took " << (microseconds / 1000000) << "," << (microseconds % 1000000) << " seconds" << std::endl;
		// std::cout << std::endl << "\tstd::vector took " << std::chrono::duration_cast<std::chrono::milliseconds>(std_end - std_start).count() << " milliseconds to run." << std::endl;
	}

	ft_vector:
	std::cout << std::endl << "----------------------------------------------------------" << std::endl << std::endl;

	// ##### Test of my ft::vector #####
	std::cout << "##### Test of my ft::vector #####" << std::endl;
	{
		gettimeofday(&start, NULL);
		// std::chrono::steady_clock::time_point ft_start = std::chrono::steady_clock::now();
		ft::vector< int > *b;
		try
		{
			b = new ft::vector< int >(test_val);
		}
		catch (std::exception &e)
		{
			std::cerr << "\texception caught!!!! " << e.what() << std::endl;
			gettimeofday(&end, NULL);
			// std::chrono::steady_clock::time_point ft_end = std::chrono::steady_clock::now();

			seconds = (end.tv_sec - start.tv_sec);
			microseconds = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
			std::cout << std::endl << "\tft::vector took " << (microseconds / 1000000) << "," << (microseconds % 1000000) << " seconds" << std::endl;
			// std::cout << std::endl << "\tft::vector took " << std::chrono::duration_cast<std::chrono::microseconds>(ft_end - ft_start).count() << " microseconds to run." << std::endl;
			goto end;
		}
		std::cout << "\tb size: " << b->size() << std::endl;
		std::cout << "\tb capacity: " << b->capacity() << std::endl;
		try
		{
			std::cout << "\tresizing b now" << std::endl;
			b->resize(resize_val);
		}
		catch (std::exception &e)
		{
			std::cerr << "\texception caught!!!! " << e.what() << std::endl;
		}
		std::cout << "\tb size: " << b->size() << std::endl;
		std::cout << "\tb capacity: " << b->capacity() << std::endl;

		delete b;
		gettimeofday(&end, NULL);
		// std::chrono::steady_clock::time_point ft_end = std::chrono::steady_clock::now();

		seconds = (end.tv_sec - start.tv_sec);
		microseconds = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
		std::cout << std::endl << "\tft::vector took " << (microseconds / 1000000) << "," << (microseconds % 1000000) << " seconds" << std::endl;
		// std::cout << std::endl << "\tft::vector took " << std::chrono::duration_cast<std::chrono::milliseconds>(ft_end - ft_start).count() << " milliseconds to run." << std::endl;
	}

	std::cout << std::endl << "----------------------------------------------------------" << std::endl << std::endl;

	end:
	// system("leaks ft_containers");
	return (0);
}