/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_chunk.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:36:52 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/22 14:52:36 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* struct_set() */
#include "cube3d_utils.h"

#include "cube3d_debug.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

int	store_entity_data(t_parser *data, t_chunk *chunk, t_chunk_token *tmp)
{
	(void)data;
	(void)chunk;
	(void)tmp;
	//TODO #12 Make the entity data structure for the player
	return (EXIT_SUCCESS);
}

/**
 * @brief Store all the chunk token in the `t_chunk_token` structure.
 * 
 * @note
 *        floor 1 : TOP    | NORTH | ENTITY
 *                  -------0-------0-------
 *        floor 2 : WEST   | EAST  | TEX
 *                  -------0-------0-------
 *        floor 3 : BOTTOM | SOUTH | OPT
 * 
 */
void	get_chunk_token(t_parser *data, t_chunk_token *tmp)
{
	const char	*f1 = mapptr(data);
	const char	*f2 = mapptr(data) + data->index + data->tmp_width + 1;
	const char	*f3 = mapptr(data) + 2 * (data->index + data->tmp_width + 1);

	struct_set(tmp, sizeof(tmp));
	tmp->ceiling = f1[0];
	tmp->north = f1[1];
	tmp->entity = f1[2];
	tmp->west = f2[0];
	tmp->east = f2[1];
	tmp->tex = f2[2];
	tmp->floor = f3[0];
	tmp->south = f3[1];
	tmp->opt = f3[2];
}

int	set_chunk(t_parser *data, t_chunk *chunk)
{
	t_chunk_token	tokens;

	get_chunk_token(data, &tokens);
	if (check_chunk_type(&tokens) == BAD_CHUNK)
		return(ret_print(EXIT_FAILURE, "//TODO bad chunk type\n"));
	chunk->ceiling = get_tex_ptr(&data->tex_list, tokens.ceiling);
	chunk->north = get_tex_ptr(&data->tex_list, tokens.north);
	chunk->west = get_tex_ptr(&data->tex_list, tokens.west);
	chunk->east = get_tex_ptr(&data->tex_list, tokens.east);
	chunk->floor = get_tex_ptr(&data->tex_list, tokens.floor);
	chunk->south = get_tex_ptr(&data->tex_list, tokens.south);
	// chunk.entity = get_tex_ptr(&data->tex_list, tokens.entity);
	// chunk->tex = get_tex_ptr(&data->tex_list, tokens.tex);
	// chunk->opt = get_tex_ptr(&data->tex_list, tokens.opt);
	if (store_entity_data(data, chunk, &tokens))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	set_next_chunk_index(t_parser *data)
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
 * 
 *       If after this skip the current `mapchar(data)` is null, we reach the
 *       end of the map.
 * 
 *       After set the chunk data we check if the chunk have data or if is a
 *       white space chunk (3x3 `' '` chunk).
 * 
 * @param data 
 * @param chunk 
 * @return int 
 */
int	get_next_chunk(t_parser *data, t_chunk *chunk)
{
	if (mapchar(data) == '\n')
		if (set_next_chunk_index(data) == -1)
			return (-1);
	data->tmp_width = get_line_width(data);
	if (set_chunk(data, chunk))
		return (EXIT_FAILURE);
	data->index += 3;
	return (EXIT_SUCCESS);
}
