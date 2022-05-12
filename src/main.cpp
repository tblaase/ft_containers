/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:32:13 by tblaase           #+#    #+#             */
/*   Updated: 2022/05/12 14:40:46 by tblaase          ###   ########.fr       */
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
#include <list>
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

		// TESTED_NAMESPACE::map<int, int> *_map = new TESTED_NAMESPACE::map<int, int>;
		// // float progress = 0;
		// for (size_t i = 0; i < test_val; ++i)
		// {
		// 	_map->insert(TESTED_NAMESPACE::make_pair<int, int>(i, i));
		// }
		// // std::cout << std::endl << "showing the created tree now inorder" << std::endl;
		// // avl.inorder(avl._root);
		// // std::cout << "\nsize: " << avl->size() << std::endl;
		// // avl.destroy_tree_from(avl._root);
		// delete _map;
		// _map = NULL;
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


// #include "../include/tester_utils/base.hpp"
// #include "../include/tester_utils/common.hpp"

// #include <list>

// #define T1 char
// #define T2 int
// typedef _pair<const T1, T2> T3;

// template <class T>
// void	is_empty(T const &mp)
// {
// 	std::cout << "is_empty: " << mp.empty() << std::endl;
// }

// int		main(void)
// {
// 	std::list<T3> lst;
// 	unsigned int lst_size = 7;
// 	for (unsigned int i = 0; i < lst_size; ++i)
// 		lst.push_back(T3('a' + i, lst_size - i));

// 	TESTED_NAMESPACE::map<T1, T2> mp(lst.begin(), lst.end()), mp2;
// 	TESTED_NAMESPACE::map<T1, T2>::iterator it;

// 	lst.clear();
// 	is_empty(mp);
// 	printSize(mp);

// 	is_empty(mp2);
// 	mp2 = mp;
// 	is_empty(mp2);

// 	it = mp.begin();
// 	for (unsigned long int i = 3; i < mp.size(); ++i)
// 		it++->second = i * 7;

// 	printSize(mp);
// 	printSize(mp2);

// 	mp2.clear();
// 	is_empty(mp2);
// 	printSize(mp2);
// 	return (0);
// }
