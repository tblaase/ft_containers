/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:32:13 by tblaase           #+#    #+#             */
/*   Updated: 2022/05/14 13:45:55 by tblaase          ###   ########.fr       */
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
// #include "../include/vector.hpp"
// #include "../include/stack.hpp"
#include "../include/map.hpp"
#endif


// int main()
// {
// // # SET_TEST_START #
// 	size_t test_val; // uncomment all the commented lines until '# SET_TEST_END #' to enable custom testing for the vector
// 	// std::cout << "test value: ";
// 	// std::string test_str;
// 	// std::getline(std::cin, test_str);
// 	// if (test_str.length() == 0)
// 		test_val = 50000000;
// 	// else
// 	// 	test_val = std::atoll(test_str.c_str());

// 	// std::cout << "test value set: " << test_val << std::endl;

// 	// std::cout << "resize value: ";
// 	size_t resize_val;
// 	// std::string resize_str;
// 	// std::getline(std::cin, resize_str);
// 	// if (resize_str.length() == 0)
// 		resize_val = 0;
// 	// else
// 	// 	resize_val = std::atoll(resize_str.c_str());

// 	// std::cout << "resize value set: " << resize_val << std::endl;
// // # SET_TEST_END #

// 	struct timeval start, end;
// 	long seconds;
// 	long microseconds;

// 	std::cout << std::endl << "----------------------------------------" << std::endl << std::endl;

// 	{
// 		// ##### Test of TESTED_NAMESPACE::vector #####
// 		#ifndef STD
// 			std::cout << "#####Test of my ft::vector#####" << std::endl;
// 		#else
// 			std::cout << "#####Test of the std::vector#####" << std::endl;
// 		#endif

// 		gettimeofday(&start, NULL);
// 		// std::chrono::steady_clock::time_point end;
// 		// std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
// 		TESTED_NAMESPACE::vector< int > *vct_1;
// 		try
// 		{
// 			std::cout << "\tcreate vct_1 now with size " << test_val << std::endl;
// 			vct_1 = new TESTED_NAMESPACE::vector< int >(test_val);
// 		}
// 		catch (std::exception &e)
// 		{
// 			std::cerr << "\tvct_1 exception caught!!!! " << e.what() << std::endl;
// 			goto next_vct;
// 		}
// 		std::cout << "\tvct_1 size: " << vct_1->size() << std::endl;
// 		std::cout << "\tvct_1 capacity: " << vct_1->capacity() << std::endl;
// 		try
// 		{
// 			std::cout << "\tresizing vct_1 now to " << resize_val << std::endl;
// 			vct_1->resize(resize_val);
// 		}
// 		catch (std::exception &e)
// 		{
// 			std::cerr << "\tvct_1 exception caught!!!! " << e.what() << std::endl;
// 		}
// 		std::cout << "\tvct_1 size: " << vct_1->size() << std::endl;
// 		std::cout << "\tvct_1 capacity: " << vct_1->capacity() << std::endl;

// 		std::cout << "\tdeleting vct_1 now" << std::endl;

// 		delete vct_1;
// 		vct_1 = NULL;

// 		next_vct:
// 		TESTED_NAMESPACE::vector<int> vct_2;
// 		std::cout << "\n\tfilling vct_2 now" << std::endl;
// 		for (size_t i = 0; i < test_val * 2; ++i)
// 		{
// 			try
// 			{
// 				vct_2.push_back(i);
// 			}
// 			catch (std::exception &e)
// 			{
// 				std::cerr << "\tvct_2 exception caught!!!! " << e.what() << std::endl;
// 				break ;
// 			}
// 		}
// 		std::cout << "\tvct_2 size: " << vct_2.size() << std::endl;
// 		std::cout << "\tvct_2 capacity: " << vct_2.capacity() << std::endl;

// 		std::cout << "\terasing vct_2 now" << std::endl;
// 		vct_2.erase(vct_2.begin(), vct_2.end());;
// 		std::cout << "\tvct_2 size: " << vct_2.size() << std::endl;
// 		std::cout << "\tvct_2 capacity: " << vct_2.capacity() << std::endl;

// 		gettimeofday(&end, NULL);
// 		// end = std::chrono::steady_clock::now();

// 		seconds = (end.tv_sec - start.tv_sec);
// 		microseconds = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
// 		#ifndef STD
// 			std::cout << std::endl << "#####ft::vector: " << (microseconds / 1000000) << "," << (microseconds % 1000000) << " seconds#####" << std::endl;
// 			// std::cout << std::endl << "\tft::vector took " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds to run." << std::endl;
// 		#else
// 			std::cout << std::endl << "#####std::vector: " << (microseconds / 1000000) << "," << (microseconds % 1000000) << " seconds#####" << std::endl;
// 			// std::cout << std::endl << "\tstd::vector took " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds to run." << std::endl;
// 		#endif
// 	// # LEAK_CHECK_START # //when checking, make sure fsanitize is disabled in the makefile CXXFLAGS
// 		#ifdef LEAK
// 			#ifndef STD
// 				system("leaks ft_containers | tail -3");
// 			#else
// 				system("leaks std_containers | tail -3");
// 			#endif
// 		#endif
// 	// # LEAK_CHECK_END #
// 	}

// 	std::cout << std::endl << "----------------------------------------" << std::endl << std::endl;

// 	{
// 		// ##### Test of TESTED_NAMESPACE::stack #####
// 		#ifndef STD
// 			std::cout << "#####Test of my ft::stack#####" << std::endl;
// 		#else
// 			std::cout << "#####Test of the std::stack#####" << std::endl;
// 		#endif
// 		gettimeofday(&start, NULL);
// 		// std::chrono::steady_clock::time_point end;
// 		// std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

// 		std::cout << "\tcreate st_1" << std::endl;
// 		TESTED_NAMESPACE::stack<int>st_1;

// 		std::cout << "\tst_1 size: " << st_1.size() << std::endl;

// 		std::cout << "\tfill with " << test_val << " elements" << std::endl;
// 		for (size_t i = 0; i < test_val; i++)
// 			st_1.push(i + 42);

// 		std::cout << "\tst_1 size: " << st_1.size() << std::endl;

// 		std::cout << "\tpopping all elements" << std::endl;
// 		for (size_t i = 0; i < test_val; i++)
// 			st_1.pop();

// 		std::cout << "\tst_1 size: " << st_1.size() << std::endl << std::endl;

// 		std::cout << "\tcreate st_2" << std::endl;
// 		TESTED_NAMESPACE::stack<int> *st_2 = new TESTED_NAMESPACE::stack<int>;

// 		std::cout << "\tst_2 size: " << st_2->size() << std::endl;

// 		std::cout << "\tfill with " << test_val * 2 << "elements" << std::endl;
// 		for (size_t i = 0; i < test_val * 2 ; i++)
// 			st_2->push(i + 42);

// 		std::cout << "\tst_2 size: " << st_2->size() << std::endl;

// 		std::cout << "\tpopping half of the elements" << std::endl;
// 		for (size_t i = 0; i < test_val; i++)
// 			st_2->pop();

// 		std::cout << "\tst_2 size: " << st_2->size() << std::endl;
// 		std::cout << "\tremaining elements should be handled by the destructor" << std::endl;
// 		delete st_2;
// 		st_2 = NULL;

// 		gettimeofday(&end, NULL);
// 		// end = std::chrono::steady_clock::now();

// 		seconds = (end.tv_sec - start.tv_sec);
// 		microseconds = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
// 		#ifndef STD
// 			std::cout << std::endl << "#####ft::stack: " << (microseconds / 1000000) << "," << (microseconds % 1000000) << " seconds#####" << std::endl;
// 			// std::cout << std::endl << "\tft::vector took " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds to run." << std::endl;
// 		#else
// 			std::cout << std::endl << "#####std::stack: " << (microseconds / 1000000) << "," << (microseconds % 1000000) << " seconds#####" << std::endl;
// 			// std::cout << std::endl << "\tstd::vector took " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds to run." << std::endl;
// 		#endif
// 	// # LEAK_CHECK_START # //when checking, make sure fsanitize is disabled in the makefile CXXFLAGS
// 		#ifdef LEAK
// 			#ifndef STD
// 				system("leaks ft_containers | tail -3");
// 			#else
// 				system("leaks std_containers | tail -3");
// 			#endif
// 		#endif
// 	// # LEAK_CHECK_END #
// 	}

// 	std::cout << std::endl << "----------------------------------------" << std::endl << std::endl;

// 	{
// 		// ##### Test of TESTED_NAMESPACE::map #####
// 		#ifndef STD
// 			std::cout << "#####Test of my ft::map#####" << std::endl;
// 		#else
// 			std::cout << "#####Test of the std::map#####" << std::endl;
// 		#endif

// 		gettimeofday(&start, NULL);
// 		// std::chrono::steady_clock::time_point end;
// 		// std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

// 		TESTED_NAMESPACE::map<int, int> *map_1 = new TESTED_NAMESPACE::map<int, int>;
// 		std::cout << "inserting " << test_val / 10 << " elements" << std::endl;
// 		for (size_t i = 0; i < test_val / 10; ++i)
// 		{
// 			map_1->insert(TESTED_NAMESPACE::make_pair(i, i));
// 		}
// 		std::cout << "map size: " << map_1->size() << std::endl;
// 		std::cout << "clearing map" << std::endl;
// 		map_1->clear();
// 		std::cout << "map size: " << map_1->size();
// 		delete map_1;
// 		map_1 = NULL;
// 		gettimeofday(&end, NULL);
// 		// end = std::chrono::steady_clock::now();

// 		seconds = (end.tv_sec - start.tv_sec);
// 		microseconds = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
// 		#ifndef STD
// 			std::cout << std::endl << "#####ft::map: " << (microseconds / 1000000) << "," << (microseconds % 1000000) << " seconds#####" << std::endl;
// 			// std::cout << std::endl << "\tft::vector took " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds to run." << std::endl;
// 		#else
// 			std::cout << std::endl << "#####std::map: " << (microseconds / 1000000) << "," << (microseconds % 1000000) << " seconds#####" << std::endl;
// 			// std::cout << std::endl << "\tstd::vector took " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds to run." << std::endl;
// 		#endif
// 	// # LEAK_CHECK_START # //when checking, make sure fsanitize is disabled in the makefile CXXFLAGS
// 		#ifdef LEAK
// 			#ifndef STD
// 				system("leaks ft_containers | tail -3");
// 			#else
// 				system("leaks std_containers | tail -3");
// 			#endif
// 		#endif
// 	// # LEAK_CHECK_END #
// 	}

// 	std::cout << std::endl << "----------------------------------------" << std::endl << std::endl;

// 	return (0);
// }


// #include "../include/tester_utils/base.hpp"
#include "../containers_test/srcs/map/common.hpp"
#include <list>

#define T1 int
#define T2 foo<int>
typedef TESTED_NAMESPACE::map<T1, T2>::value_type T3;
typedef TESTED_NAMESPACE::map<T1, T2>::iterator ft_iterator;
typedef TESTED_NAMESPACE::map<T1, T2>::const_iterator ft_const_iterator;

static int iter = 0;

template <typename MAP>
void	ft_bound(MAP &mp, const T1 &param)
{
	ft_iterator ite = mp.end(), it[2];
	_pair<ft_iterator, ft_iterator> ft_range;

	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	std::cout << "with key [" << param << "]:" << std::endl;
	it[0] = mp.lower_bound(param); it[1] = mp.upper_bound(param);
	ft_range = mp.equal_range(param);
	std::cout << "lower_bound: " << (it[0] == ite ? "end()" : printPair(it[0], false)) << std::endl;
	std::cout << "upper_bound: " << (it[1] == ite ? "end()" : printPair(it[1], false)) << std::endl;
	std::cout << "equal_range: " << (ft_range.first == it[0] && ft_range.second == it[1]) << std::endl;
}

template <typename MAP>
void	ft_const_bound(const MAP &mp, const T1 &param)
{
	ft_const_iterator ite = mp.end(), it[2];
	_pair<ft_const_iterator, ft_const_iterator> ft_range;

	std::cout << "\t-- [" << iter++ << "] (const) --" << std::endl;
	std::cout << "with key [" << param << "]:" << std::endl;
	it[0] = mp.lower_bound(param);
	it[1] = mp.upper_bound(param);
	ft_range = mp.equal_range(param);
	std::cout << "lower_bound: " << (it[0] == ite ? "end()" : printPair(it[0], false)) << std::endl;
	std::cout << "upper_bound: " << (it[1] == ite ? "end()" : printPair(it[1], false)) << std::endl;
	std::cout << "equal_range: " << (ft_range.first == it[0] && ft_range.second == it[1]) << std::endl;
}

int		main(void)
{
	std::list<T3> lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(i + 1, (i + 1) * 3));
	TESTED_NAMESPACE::map<T1, T2> mp(lst.begin(), lst.end());
	printSize(mp);

	ft_const_bound(mp, -10);
	ft_const_bound(mp, 1);
	ft_const_bound(mp, 5);
	ft_const_bound(mp, 10);
	ft_const_bound(mp, 50);

	printSize(mp);

	mp.lower_bound(3)->second = 404;
	mp.upper_bound(7)->second = 842;
	ft_bound(mp, 5);
	ft_bound(mp, 7);

	printSize(mp);
	return (0);
}
