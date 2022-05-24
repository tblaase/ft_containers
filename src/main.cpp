/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:32:13 by tblaase           #+#    #+#             */
/*   Updated: 2022/05/24 17:41:40 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <sys/time.h>
// #include <chrono> // can be used instead of sys/time.h, but is not c++98 compliant


#define TESTED_NAMESPACE ft
#ifdef STD
# undef TESTED_NAMESPACE
# define TESTED_NAMESPACE std
#include <vector>
#include <map>
#include <stack>
#else
#include "../include/vector.hpp"
#include "../include/stack.hpp"
#include "../include/map.hpp"
#endif


int main()
{
// # SET_TEST_START #
	size_t test_val; // uncomment all the commented lines until '# SET_TEST_END #' to enable custom testing for the vector
	// std::cout << "test value: ";
	// std::string test_str;
	// std::getline(std::cin, test_str);
	// if (test_str.length() == 0)
		test_val = 50000000;
	// else
	// 	test_val = std::atoll(test_str.c_str());

	// std::cout << "test value set: " << test_val << std::endl;

	// std::cout << "resize value: ";
	size_t resize_val;
	// std::string resize_str;
	// std::getline(std::cin, resize_str);
	// if (resize_str.length() == 0)
		resize_val = 0;
	// else
	// 	resize_val = std::atoll(resize_str.c_str());

	// std::cout << "resize value set: " << resize_val << std::endl;
// # SET_TEST_END #

	struct timeval start, end;
	long seconds;
	long microseconds;

	std::cout << std::endl << "----------------------------------------" << std::endl << std::endl;

	{
		// ##### Test of TESTED_NAMESPACE::vector #####
		#ifndef STD
			std::cout << "#####Test of my ft::vector#####" << std::endl;
		#else
			std::cout << "#####Test of the std::vector#####" << std::endl;
		#endif

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
		std::cout << "\tmax_size: " << vct_1->max_size() << std::endl;
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
		vct_1 = NULL;

		next_vct:
		TESTED_NAMESPACE::vector<int> vct_2;
		TESTED_NAMESPACE::vector< int >::iterator it;
		std::cout << "\n\tfilling vct_2 now" << std::endl;
		for (size_t i = 0; i < test_val * 2; ++i)
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
		it = vct_2.begin();
		std::cout << "\tprinting the first 5 elements of vct_1" << std::endl;
		for (size_t i = 0; i < 5; ++i)
			std::cout << "\telem " << i << ": " << *it++ << std::endl;

		std::cout << "\terasing vct_2 now" << std::endl;
		vct_2.erase(vct_2.begin(), vct_2.end());;
		std::cout << "\tvct_2 size: " << vct_2.size() << std::endl;
		std::cout << "\tvct_2 capacity: " << vct_2.capacity() << std::endl;

		gettimeofday(&end, NULL);
		// end = std::chrono::steady_clock::now();

		seconds = (end.tv_sec - start.tv_sec);
		microseconds = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
		#ifndef STD
			std::cout << std::endl << "#####ft::vector: " << (microseconds / 1000000) << "," << (microseconds % 1000000) << " seconds#####" << std::endl;
			// std::cout << std::endl << "\tft::vector took " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds to run." << std::endl;
		#else
			std::cout << std::endl << "#####std::vector: " << (microseconds / 1000000) << "," << (microseconds % 1000000) << " seconds#####" << std::endl;
			// std::cout << std::endl << "\tstd::vector took " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds to run." << std::endl;
		#endif
	// # LEAK_CHECK_START # //when checking, make sure fsanitize is disabled in the makefile CXXFLAGS
		#ifdef LEAK
			#ifndef STD
				system("leaks ft_containers | tail -3");
			#else
				system("leaks std_containers | tail -3");
			#endif
		#endif
	// # LEAK_CHECK_END #
	}

	std::cout << std::endl << "----------------------------------------" << std::endl << std::endl;

	{
		// ##### Test of TESTED_NAMESPACE::stack #####
		#ifndef STD
			std::cout << "#####Test of my ft::stack#####" << std::endl;
		#else
			std::cout << "#####Test of the std::stack#####" << std::endl;
		#endif
		gettimeofday(&start, NULL);
		// std::chrono::steady_clock::time_point end;
		// std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

		std::cout << "\tcreate st_1" << std::endl;
		TESTED_NAMESPACE::stack<int>st_1;

		std::cout << "\tst_1 size: " << st_1.size() << std::endl;

		std::cout << "\tfill with " << test_val << " elements" << std::endl;
		for (size_t i = 0; i < test_val; i++)
			st_1.push(i + 42);

		std::cout << "\tst_1 size: " << st_1.size() << std::endl;

		std::cout << "\tpopping all elements" << std::endl;
		for (size_t i = 0; i < test_val; i++)
			st_1.pop();

		std::cout << "\tst_1 size: " << st_1.size() << std::endl << std::endl;

		std::cout << "\tcreate st_2" << std::endl;
		TESTED_NAMESPACE::stack<int> *st_2 = new TESTED_NAMESPACE::stack<int>;

		std::cout << "\tst_2 size: " << st_2->size() << std::endl;

		std::cout << "\tfill with " << test_val * 2 << "elements" << std::endl;
		for (size_t i = 0; i < test_val * 2 ; i++)
			st_2->push(i + 42);

		std::cout << "\tst_2 size: " << st_2->size() << std::endl;

		std::cout << "\tpopping half of the elements" << std::endl;
		for (size_t i = 0; i < test_val; i++)
			st_2->pop();

		std::cout << "\tst_2 size: " << st_2->size() << std::endl;
		std::cout << "\tremaining elements should be handled by the destructor" << std::endl;
		delete st_2;
		st_2 = NULL;

		gettimeofday(&end, NULL);
		// end = std::chrono::steady_clock::now();

		seconds = (end.tv_sec - start.tv_sec);
		microseconds = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
		#ifndef STD
			std::cout << std::endl << "#####ft::stack: " << (microseconds / 1000000) << "," << (microseconds % 1000000) << " seconds#####" << std::endl;
			// std::cout << std::endl << "\tft::vector took " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds to run." << std::endl;
		#else
			std::cout << std::endl << "#####std::stack: " << (microseconds / 1000000) << "," << (microseconds % 1000000) << " seconds#####" << std::endl;
			// std::cout << std::endl << "\tstd::vector took " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds to run." << std::endl;
		#endif
	// # LEAK_CHECK_START # //when checking, make sure fsanitize is disabled in the makefile CXXFLAGS
		#ifdef LEAK
			#ifndef STD
				system("leaks ft_containers | tail -3");
			#else
				system("leaks std_containers | tail -3");
			#endif
		#endif
	// # LEAK_CHECK_END #
	}

	std::cout << std::endl << "----------------------------------------" << std::endl << std::endl;

	{
		// ##### Test of TESTED_NAMESPACE::map #####
		#ifndef STD
			std::cout << "#####Test of my ft::map#####" << std::endl;
		#else
			std::cout << "#####Test of the std::map#####" << std::endl;
		#endif

		gettimeofday(&start, NULL);
		// std::chrono::steady_clock::time_point end;
		// std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

		TESTED_NAMESPACE::map<int, int> *map_1 = new TESTED_NAMESPACE::map<int, int>;
		std::cout << "\tinserting " << test_val / 100 << " elements" << std::endl;
		for (size_t i = 0; i < test_val / 100; ++i)
		{
			map_1->insert(TESTED_NAMESPACE::make_pair(i, i + 1));
		}
		std::cout << "\tmax_size: " << map_1->max_size() << std::endl;
		std::cout << "\tmap size: " << map_1->size() << std::endl;

		std::cout << "\titerating over map using the iterator" << std::endl;
		TESTED_NAMESPACE::map<int, int>::const_iterator it = map_1->begin();
		for (size_t i = 0; i < 15; ++i)
		{
			std::cout << "key: " << it->first << "\tvalue: " << it->second << std::endl;
			++it;
		}
		std::cout << "\toutput for adding a duplicate element: " << map_1->insert(TESTED_NAMESPACE::make_pair(0, 55)).second << std::endl;
		std::cout << "\tthe insertion of duplicate elements should not change the value of the key:" << std::endl;
		it = map_1->begin();
		std::cout << "\tkey: " << it->first << "\tvalue: " << it->second << std::endl;
		std::cout << "\tmap size: " << map_1->size() << std::endl;
		std::cout << "\tclearing map" << std::endl;
		map_1->clear();
		std::cout << "\tmap size: " << map_1->size();
		delete map_1;
		map_1 = NULL;
		gettimeofday(&end, NULL);
		// end = std::chrono::steady_clock::now();

		seconds = (end.tv_sec - start.tv_sec);
		microseconds = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
		#ifndef STD
			std::cout << std::endl << "#####ft::map: " << (microseconds / 1000000) << "," << (microseconds % 1000000) << " seconds#####" << std::endl;
			// std::cout << std::endl << "\tft::vector took " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds to run." << std::endl;
		#else
			std::cout << std::endl << "#####std::map: " << (microseconds / 1000000) << "," << (microseconds % 1000000) << " seconds#####" << std::endl;
			// std::cout << std::endl << "\tstd::vector took " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds to run." << std::endl;
		#endif
	// # LEAK_CHECK_START # //when checking, make sure fsanitize is disabled in the makefile CXXFLAGS
		#ifdef LEAK
			#ifndef STD
				system("leaks ft_containers | tail -3");
			#else
				system("leaks std_containers | tail -3");
			#endif
		#endif
	// # LEAK_CHECK_END #
	}

	std::cout << std::endl << "----------------------------------------" << std::endl << std::endl;

	return (0);
}
