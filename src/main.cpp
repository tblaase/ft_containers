/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:32:13 by tblaase           #+#    #+#             */
/*   Updated: 2022/05/10 11:54:38 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <map>
#include <list>
#include <stack>
#include <iostream>
#include <cstdlib>
// #include <chrono> // can be used instead of sys/time.h, but is not c++98 compliant

#include <sys/time.h>

#define TESTED_NAMESPACE ft
#ifdef STD
# undef TESTED_NAMESPACE
# define TESTED_NAMESPACE std
#endif


#include "../include/vector.hpp"
#include "../include/stack.hpp"
// #include "../include/map.hpp"

int main()
{
// # SET_TEST_START #
	long long test_val; // uncomment all the commented lines until '# SET_TEST_END #' to enable custom testing for the vector
	// std::cout << "test value: ";
	// std::string test_str;
	// std::getline(std::cin, test_str);
	// if (test_str.length() == 0)
		test_val = 50000000;
	// else
	// 	test_val = std::atoll(test_str.c_str());

	// std::cout << "test value set: " << test_val << std::endl;

	// std::cout << "resize value: ";
	long long resize_val;
	// std::string resize_str;
	// std::getline(std::cin, resize_str);
	// if (resize_str.length() == 0)
		resize_val = 50000001;
	// else
	// 	resize_val = std::atoll(resize_str.c_str());

	// std::cout << "resize value set: " << resize_val << std::endl;
// # SET_TEST_END #

	struct timeval start, end;
	long seconds;
	long microseconds;

	std::cout << std::endl << "-------------------------------------------" << std::endl << std::endl;

	// // ##### Test of TESTED_NAMESPACE::vector #####
	#ifndef STD
		std::cout << "#####Test of my ft::vector#####" << std::endl;
	#else
		std::cout << "#####Test of the std::vector#####" << std::endl;
	#endif

	{
		gettimeofday(&start, NULL);
		// std::chrono::steady_clock::time_point end;
		// std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
		TESTED_NAMESPACE::vector< int > *vct_1;
		try
		{
			std::cout << "\tcreate vct_1 now with size " << test_val << std::endl;
			vct_1 = new TESTED_NAMESPACE::vector< int >(test_val);
		}
		catch (std::exception &e)
		{
			std::cerr << "\tvct_1 exception caught!!!! " << e.what() << std::endl;
			goto next_vct;
		}
		std::cout << "\tvct_1 size: " << vct_1->size() << std::endl;
		std::cout << "\tvct_1 capacity: " << vct_1->capacity() << std::endl;
		try
		{
			std::cout << "\tresizing vct_1 now to " << resize_val << std::endl;
			vct_1->resize(resize_val);
		}
		catch (std::exception &e)
		{
			std::cerr << "\tvct_1 exception caught!!!! " << e.what() << std::endl;
		}
		std::cout << "\tvct_1 size: " << vct_1->size() << std::endl;
		std::cout << "\tvct_1 capacity: " << vct_1->capacity() << std::endl;

		std::cout << "\tdeleting vct_1 now" << std::endl;

		delete vct_1;

		next_vct:
		TESTED_NAMESPACE::vector<int> vct_2;
		std::cout << "\n\tfilling vct_2 now" << std::endl;
		for (int i = 0; i < 100000000; ++i)
		{
			try
			{
				vct_2.push_back(i);
			}
			catch (std::exception &e)
			{
				std::cerr << "\tvct_2 exception caught!!!! " << e.what() << std::endl;
				break ;
			}
		}
			std::cout << "\tvct_2 size: " << vct_2.size() << std::endl;
			std::cout << "\tvct_2 capacity: " << vct_2.capacity() << std::endl;

		std::cout << "\terasing vct_2 now" << std::endl;
		vct_2.erase(vct_2.begin(), vct_2.end());;
		std::cout << "\tvct_2 size: " << vct_2.size() << std::endl;
		std::cout << "\tvct_2 capacity: " << vct_2.capacity() << std::endl;

		gettimeofday(&end, NULL);
		// end = std::chrono::steady_clock::now();

		seconds = (end.tv_sec - start.tv_sec);
		microseconds = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
		#ifndef STD
			std::cout << std::endl << "#####ft::vector took " << (microseconds / 1000000) << "," << (microseconds % 1000000) << " seconds#####" << std::endl;
			// std::cout << std::endl << "\tft::vector took " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds to run." << std::endl;
		#else
			std::cout << std::endl << "#####std::vector took " << (microseconds / 1000000) << "," << (microseconds % 1000000) << " seconds#####" << std::endl;
			// std::cout << std::endl << "\tstd::vector took " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds to run." << std::endl;
		#endif
	}

	std::cout << std::endl << "-------------------------------------------" << std::endl << std::endl;

// # LEAK_CHECK_START # //when checking, make sure fsanitize is disabled in the makefile CXXFLAGS
	// #ifndef STD
	// 	system("leaks ft_containers");
	// #else
	// 	system("leaks std_containers");
	// #endif
// # LEAK_CHECK_END #
	return (0);
}


// #include "../include/tester_utils/base.hpp"

// // #define TESTED_NAMESPACE ft


// #define T_SIZE_TYPE typename TESTED_NAMESPACE::vector<T>::size_type

// template <typename T>
// void	printSize(TESTED_NAMESPACE::vector<T> const &vct, bool print_content = true)
// {
// 	const T_SIZE_TYPE size = vct.size();
// 	const T_SIZE_TYPE capacity = vct.capacity();
// 	const std::string isCapacityOk = (capacity >= size) ? "OK" : "KO";
// 	// Cannot limit capacity's max value because it's implementation dependent

// 	std::cout << "size: " << size << std::endl;
// 	std::cout << "capacity: " << isCapacityOk << std::endl;
// 	std::cout << "max_size: " << vct.max_size() << std::endl;
// 	if (print_content)
// 	{
// 		typename TESTED_NAMESPACE::vector<T>::const_iterator it = vct.begin();
// 		typename TESTED_NAMESPACE::vector<T>::const_iterator ite = vct.end();
// 		std::cout << std::endl << "Content is:" << std::endl;
// 		for (; it != ite; ++it)
// 			std::cout << "- " << *it << std::endl;
// 	}
// 	std::cout << "###########################################" << std::endl;
// }

// #define TESTED_TYPE int

// void	is_empty(TESTED_NAMESPACE::vector<TESTED_TYPE> const &vct)
// {
// 	std::cout << "is_empty: " << vct.empty() << std::endl;
// }

// int		main(void)
// {
// 	const int start_size = 7;
// 	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(start_size, 20);
// 	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it = vct.begin();

// 	for (int i = 2; i < start_size; ++i)
// 	{
// 		it[i] = (start_size - i) * 3;
// 	}
// 	printSize(vct, true);

// 	vct.resize(10, 42);
// 	printSize(vct, true);

// 	vct.resize(18, 43);
// 	printSize(vct, true);
// 	vct.resize(10);
// 	printSize(vct, true);
// 	vct.resize(23, 44);
// 	printSize(vct, true);
// 	vct.resize(5);
// 	printSize(vct, true);
// 	vct.reserve(5);
// 	vct.reserve(3);
// 	printSize(vct, true);
// 	vct.resize(87);
// 	vct.resize(5);
// 	printSize(vct, true);

// 	TESTED_NAMESPACE::vector<TESTED_TYPE> vct2;
// 	// is_empty(vct2);
// 	// vct2 = vct;
// 	is_empty(vct2);
// 	vct.reserve(vct.capacity() + 1);
// 	printSize(vct, true);
// 	printSize(vct2, true);

// 	vct2.resize(0);
// 	is_empty(vct2);
// 	printSize(vct2, true);
// 	return (0);
// }
