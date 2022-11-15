/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:48:29 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/15 12:35:12 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d.h"

#include "cube3d_debug.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

#include <stdio.h>//TODO REMOVE

/**
 * //TODO
 * Make function util to read cube format
 * Faire les math pour pouvoir lire les trois etage d'un chunk
 */

/**
 * @brief Set the floor 1 object
 * 
 * @details floor 1 : TOP | NORTH | ENTITY
 * 
 * 
 * @param data 
 * @param index 
 * @param c 
 * @return int 
 */
static int	set_floor_1(t_parser *data, t_chunk *chunk)
{
	(void)chunk;
	printf("[%.3s]\n", mapptr(data));
	return (EXIT_SUCCESS);
}

/**
 * @brief Set the floor 2 object
 * 
 * @details floor 2 : WEST | EAST | TEX
 * 
 * 
 * @param data 
 * @param index 
 * @param c 
 * @return int 
 */
static int	set_floor_2(t_parser *data, t_chunk *chunk)
{
	(void)chunk;
	printf("[%.3s]\n", (mapptr(data) + data->index + get_line_width(data) + 1));

	return (EXIT_SUCCESS);
}

/**
 * @brief Set the floor 3 object
 * 
 * @details floor 3 : BOTTOM | SOUTH | OPT
 * 
 * 
 * @param data 
 * @param index 
 * @param c 
 * @return int 
 */
static int	set_floor_3(t_parser *data, t_chunk *chunk)
{
	(void)chunk;
	printf("[%.3s]\n", (mapptr(data) + data->index + 2 * (get_line_width(data) + 1)));

	return (EXIT_SUCCESS);
}

int	set_next_chunk_index(t_parser *data)
{
	data->index++;
	data->cube_map += data->index;
	data->index = 0;
	data->cube_map += (get_line_width(data) + 1) * 2;
	if (!mapchar(data))
		return (-1);
	return (EXIT_SUCCESS);
}

/**
 * @brief Set the `chunk` structure, we read each tree floor and check each 3
 *        value then store in the structure. The we skip the current chunk for
 *        the next call.
 * 
 * @details
 *        TOP, BOTTOM is the ceiling and floor color. In the `.cub` is the
 *        default background color, but in the `.cube` format we use them as
 *        color for the top and bottom face of our chunk.
 *
 *        NORTH, WEST, EAST, SOUTH will be the texture of each chunk face.
 *
 *        ENTITY, TEX, OPT will store player info or other entity.
 *
 *        floor 1 : TOP    | NORTH | ENTITY
 *                  -------0-------0-------
 *        floor 2 : WEST   | EAST  | TEX
 *                  -------0-------0-------
 *        floor 3 : BOTTOM | SOUTH | OPT
 * 
 * @note If the current `mapchar(data)` (or `data.cube_map[data.index]`) is '\n'
 *       we are a the end of the floor 1 line. In this case we skip the floor 2
 *       and 3 by incrementing the `data.cube` pointer with `data.index` and two
 *       time the width of the floor 2. (we have already verified that the 3
 *       floor have the same width).
 *       If after this skip the current `mapchar(data)` is null, we reach the
 *       end of the map.
 * 
 * @param data 
 * @param chunk 
 * @return int 
 */
int	get_next_chunk(t_parser *data, t_chunk *chunk)
{
	(void)chunk;
	if (mapchar(data) == '\n')
		if (set_next_chunk_index(data) == -1)
			return (-1);
	if (set_floor_1(data, chunk)
		|| set_floor_2(data, chunk)
		|| set_floor_3(data, chunk))
		return (EXIT_FAILURE)/* //TODO check if we return the message error here or in the function */;
	data->index += 3;
	return (EXIT_SUCCESS);
}

int	init_map(t_parser *data)
{
	t_chunk	tmp;
	int		err;

	data->index = 0;
	printf("[%d]\n", data->index);//TODO REMOVE
	data->map = v_init(sizeof(t_chunk), NULL, NULL);
	if (!v_alloc(&data->map, SET, (data->map_size.x * data->map_size.y)))
		return (ret_print(EXIT_FAILURE, ERR_VEC_ALLOC));
	err = EXIT_SUCCESS ;
	while (err == EXIT_SUCCESS)
	{
		err = get_next_chunk(data, &tmp);
		if (err == EXIT_SUCCESS)
		{
			if (!v_add(&data->map, DEFAULT, &tmp))
				return (ret_print(EXIT_FAILURE, ERR_VEC_ADD));
		}
		else if (err == EXIT_FAILURE)
			return (ret_print(EXIT_FAILURE, "//TODO"));
	}
	return (EXIT_SUCCESS);
}

/**
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
	(void)data;
	while (*data->cube_map && (*data->cube_map == '~' || *data->cube_map == '\n'))
		data->cube_map++;
	if (set_map_size(data) || init_map(data))
		return (EXIT_FAILURE);
	// printf("{{\n%s\n}}\n",data->cube_map);printf("map size [%dx%d]\n", data->map_size.x,data->map_size.y);
	return (EXIT_SUCCESS);
}
