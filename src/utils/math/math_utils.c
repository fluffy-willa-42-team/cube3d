/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:30:13 by awillems          #+#    #+#             */
/*   Updated: 2022/11/07 11:24:02 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

/**
 * @brief Loops a number so it fits between 0 and the given len
 * 
 * @param n 
 * @param len 
 * @return double 
 */
double loop_len(double n, double len)
{
	if (len == 0)
		return (n);
	while (n > len)
		n -= len;
	while (n < 0)
		n += len;
	return (n);
}

int is_equal(double a, double b)
{
	return ((a > b - 0.000001 && a < b + 0.000001) ||
		(b > a - 0.000001 && b < a + 0.000001));
}
