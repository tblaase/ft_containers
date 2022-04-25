/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:32:13 by tblaase           #+#    #+#             */
/*   Updated: 2022/04/25 18:25:31 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>

int main()
{
	std::vector<char> a;

	// std::cout << "size: " << a.size() << std::endl;
	// std::cout << "capacity: " << a.capacity() << std::endl;
	a.reserve(4);
	std::cout << "size: " << a.size() << std::endl;
	std::cout << "capacity: " << a.capacity() << std::endl;

	for (int i = 0; i < 7; i++)
		a.push_back(i + 32);

	std::cout << "size: " << a.size() << std::endl;
	std::cout << "capacity: " << a.capacity() << std::endl;

	// for (int i = a.size(); i < 96; i++)
	// 	a.push_back(i);

	// std::cout << "size: " << a.size() << std::endl;
	// std::cout << "capacity: " << a.capacity() << std::endl;


	try{
		a.resize(15);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() <<std::endl;
	}

	std::cout << "size: " << a.size() << std::endl;
	std::cout << "capacity: " << a.capacity() << std::endl;

	std::cout << "max: " << a.max_size() << std::endl;

	for (size_t i = 0; i < a.size(); i++)
		std::cout << (int)a[i] << std::endl;

	std::cout << "size: " << a.size() << std::endl;
	std::cout << "capacity: " << a.capacity() << std::endl;

	return (0);
}