/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 12:02:50 by tblaase           #+#    #+#             */
/*   Updated: 2022/04/24 12:19:46 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>

namespace ft
{
	template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
		struct iterator
		{
			typedef T			value_type;
			typedef Distance	diff_type;
			typedef Pointer		pointer;
			typedef Reference	reference;
			typedef Category	it_category;
		};

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag: public input_iterator_tag {};
	struct bidirectional_iterator_tag: public forward_iterator_tag {};
	struct random_access_iterator_tag: public bidirectional_iterator_tag {};

	template<class Iterator>
		struct iterator_traits
		{
			typedef typename Iterator::value_type	value_type;
			typedef typename Iterator::diff_type	diff_type;
			typedef typename Iterator::pointer		pointer;
			typedef typename Iterator::reference	reference;
			typedef typename Iterator::it_category	it_category;
		};

	template<class T>
		struct iterator_traits<T*>
		{
			typedef T							value_type;
			typedef value_type*					pointer;
			typedef value_type&					referance;
			typedef ptrdiff_t					diff_type;
			typedef random_access_iterator_tag	it_category;
		};
}
