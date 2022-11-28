/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:12:59 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/28 14:15:26 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d.h"

#include "cube3d_utils.h"

/**
 * @brief Get the texture index int the list.
 * 
 * @warning The function calculate only the token index, it dont check if the
 *          element exist !
 *          If the token is out of range from the `authzed_chunk_char()`
 *          will return `-1`.
 * 
 * @return int Return the index of the texture slot. Or `-1` if the token is
 *             unauthorized.
 */
int	get_tex_index(char token)
{
	if (!authzed_chunk_char(token))
		return (-1);
	return (token - '!');
}

/**
 * @brief Get the texture ptr int the list.
 * 
 * @warning The function calculate only the pointer index, it dont check if the
 *          element exist !
 *          If the token is out of range from the `authzed_chunk_char()`
 *          will return `NULL`.
 * 
 * @return int Return a pointer of the texture slot. Or `NULL` if the token is
 *             unauthorized.
 */
t_texture	*get_tex_ptr(t_vec *tex, char token)
{
	const int	index = get_tex_index(token);

	if (index == -1)
		return (NULL);
	if (token == E_EMPTY)
		return (NULL);
	return (&((t_texture *)tex->buffer)[get_tex_index(token)]);
}
