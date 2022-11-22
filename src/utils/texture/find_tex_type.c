/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_tex_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:13:54 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/21 17:41:03 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube3d.h"

#include "lib_is_check.h" /* ft_isdigit */

/**
 * @brief Check texture type. For a texture path that start with `./` return
 *        `IMAGE`, for a color type, is three set of three numbers separated by
 *        commas `rrr,ggg,bbb,aaa` we return `COLOR` otherwise if we dont not
 *        found the type, return `UNDEFINED type.
 * 
 * @warning Dont check if the path or color is correct.
 * 
 * @example
 *          Color format
 *             [0 ] r
 *             [1 ] r
 *             [2 ] r
 *             [3 ] ,
 *             [4 ] g
 *             [5 ] g
 *             [6 ] g
 *             [7 ] ,
 *             [8 ] b
 *             [9 ] b
 *             [10] b
 *             [11] ,
 *             [12] a
 *             [13] a
 *             [14] a
 * 
 * @param tex 
 * @return int 
 */
int	find_tex_type(char *tex)
{
	int	x;
	int	num_len;
	int	comma_nb;

	if ((*tex && *tex == '.') && (*(tex + 1) && *(tex + 1) == '/'))
		return (IMAGE);
	x = 0;
	comma_nb = 0;
	num_len = 0;
	while (ft_isdigit(tex[x]))
	{
		num_len++;
		if (tex[x + 1] == ',')
		{
			comma_nb++;
			x++;
			num_len = 0;
		}
		if (num_len > 3)
			return (UNDEFINED);
		x++;
	}
	if (comma_nb == 3 && num_len)
		return (COLOR);
	return (UNDEFINED);
}