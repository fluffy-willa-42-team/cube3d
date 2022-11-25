/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:33:11 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/25 17:27:39 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* struct_set() */
#include "cube3d_utils.h"

#include "cube3d_debug.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

/**
 * @brief Get the width of the current chunk line.
 *        Check each three line of a chunk line. If the three line dont have the
 *        same width return a error.
 *        We check three line by three, each line need to have the same `width`
 *        (a chunk is 3x3).
 *        We consider `chunk_width`, all the `' '` only if there is at the
 *        beginning of the line and all non `' '` character.
 * 
 * @param data Parser structure.
 * @return int 
 */
static int	get_chunk_pars_line_width(t_parser *data)
{
	const int	first_chunk_width = get_line_width(data);
	int			chunk_heigth;
	int			chunk_width;

	chunk_heigth = 1;
	chunk_width = 0;
	data->index += first_chunk_width + 1;
	while (mapchar(data) && chunk_heigth < 3)
	{
		chunk_width = get_line_width(data);
		if (first_chunk_width != chunk_width)
			return (ret_print(-1, ERR_CHUNK_W));
		chunk_heigth++;
		data->index += chunk_width + 1;
	}
	if (chunk_heigth == 3)
		return (first_chunk_width);
	return (ret_print(-1, ERR_CHUNK_H));
}

/**
 * @brief Check if the size of each chunk line is correct and set
 *        `data.map_size.{x, y}`.
 *
 *        We use mapchar() and mapptr() to get the current index char or ptr
 *        from the map. Is the equivalent of `data->cube_map[data->index]`.
 *        To increment the index we set `data->index`.
 * 
 *        We check three line by three, each line need to have the same `width`
 *        (a chunk is 3x3).
 *        We consider `chunk_width`, all the `' '` only if there is at the
 *        beginning of the line and all non `' '` character.
 *        We check if `width` modulo 3 goes not give remainder.
 * 
 * @param data Parser structure.
 * @return int 
 */
int	set_map_size(t_parser *data)
{
	int	biggest_width;
	int	width;
	int	heigth;

	data->index = 0;
	biggest_width = 0;
	width = 0;
	heigth = 0;
	while (mapchar(data))
	{
		width = get_chunk_pars_line_width(data);
		if (width == -1)
			return (EXIT_FAILURE);
		if (width % 3)
			return (ret_print(EXIT_FAILURE, ERR_CHUNK_W));
		if (width > biggest_width)
			biggest_width = width;
		heigth++;
	}
	data->map_size.x = biggest_width / 3;
	data->map_size.y = heigth;
	return (EXIT_SUCCESS);
}
