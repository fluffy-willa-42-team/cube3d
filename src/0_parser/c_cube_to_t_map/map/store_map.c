/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:48:29 by mahadad           #+#    #+#             */
/*   Updated: 2022/12/28 15:31:23 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d.h"

#include "cube3d_debug.h"

/* struct_set() */
#include "cube3d_utils.h"

int	init_map_while(t_parser *data)
{
	int32_t		x;
	int32_t		y;
	int			err;
	t_chunk		*chunk;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		err = 0;
		while (x < data->map_width)
		{
			chunk = get_chunk_pars(data, set_i32(x, y));
			chunk->coord = set_i32(x, y);
			if (err == END_OF_LINE || err == END_OF_MAP)
				chunk->type = WHITE_SPACE_CHUNK;
			else
				err = get_next_chunk(data, chunk);
			if (err == EXIT_FAILURE)
				return (EXIT_FAILURE);
			x++;
		}
		y++;
	}
	return (EXIT_SUCCESS);
}

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief 
 * 
 * @param data 
 * @return int 
 */
int	init_map(t_parser *data)
{
	data->index = 0;
	data->map = v_init(sizeof(t_chunk), NULL, NULL);
	if (!v_alloc(&data->map, SET, (data->map_width * data->map_height)))
		return (ret_print(EXIT_FAILURE, ERR_VEC_ALLOC));
	data->map.len = data->map_width * data->map_height;
	if (init_map_while(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief 
 * 
 * @note In the first time we skip the `cube separator sequence string`, we
 *       increment the `data->cube_map` pointer.
 * 
 * @param data Parser structure.
 * @return int 
 */
int	store_map(t_parser *data)
{
	if (set_map_size(data) || init_map(data) || check_map(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
