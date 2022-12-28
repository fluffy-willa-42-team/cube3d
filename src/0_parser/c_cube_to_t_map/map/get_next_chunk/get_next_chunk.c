/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_chunk.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:36:52 by mahadad           #+#    #+#             */
/*   Updated: 2022/12/28 15:31:39 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* struct_set() */
#include "cube3d_utils.h"

#include "cube3d_debug.h"

/**
 * @author @Matthew-Dreemurr
 * 
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
void	get_chunk_pars_token(t_parser *data, t_chunk_token *tokens)
{
	const char	*f1 = mapptr(data);
	const char	*f2 = mapptr(data) + data->index + data->tmp_width + 1;
	const char	*f3 = mapptr(data) + 2 * (data->index + data->tmp_width + 1);

	struct_set(tokens, sizeof(t_chunk_token));
	tokens->ceiling = f1[0];
	tokens->north = f1[1];
	tokens->entity = f1[2];
	tokens->west = f2[0];
	tokens->east = f2[1];
	tokens->tex = f2[2];
	tokens->floor = f3[0];
	tokens->south = f3[1];
	tokens->opt = f3[2];
}

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Set the chunk structure, find the chunk type (bad, good, whitespace)
 *        and store the texture pointer for each face (north, south, east, west,
 *        ceiling, floor).
 * 
 * @param data 
 * @param chunk 
 * @return int 
 */
int	set_chunk(t_parser *data, t_chunk *chunk)
{
	t_chunk_token	tokens;

	get_chunk_pars_token(data, &tokens);
	if (check_chunk_type(&tokens) == BAD_CHUNK)
		return (ret_print(EXIT_FAILURE, ERR_BAD_CHUNK_TYPE));
	chunk->type = tokens.type;
	chunk->ceiling = get_tex_ptr(&data->tex_list, tokens.ceiling);
	chunk->north = get_tex_ptr(&data->tex_list, tokens.north);
	chunk->west = get_tex_ptr(&data->tex_list, tokens.west);
	chunk->east = get_tex_ptr(&data->tex_list, tokens.east);
	chunk->floor = get_tex_ptr(&data->tex_list, tokens.floor);
	chunk->south = get_tex_ptr(&data->tex_list, tokens.south);
	if (store_entity(data, chunk, &tokens))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Calculate the next chunk index, will set the index to `0` and
 *        increment the `data->cube_map` address to offset the pointer.
 * 
 * @param data 
 * @return int 
 */
static int	set_next_chunk_index(t_parser *data)
{
	data->index++;
	data->cube_map += data->index;
	data->index = 0;
	data->cube_map += (get_line_width(data) + 1) * 2;
	if (!mapchar(data))
		return (END_OF_MAP);
	return (END_OF_LINE);
}

/**
 * @author @Matthew-Dreemurr
 * 
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
 * @return int Return `0` (aka EXIT_SUCCESS) if there is no error,
 *             `1` (aka EXIT_FAILURE) if a error is occurred,
 *             `-1` if is the end of file.
 */
int	get_next_chunk(t_parser *data, t_chunk *chunk)
{
	data->tmp_width = get_line_width(data);
	if (set_chunk(data, chunk))
		return (EXIT_FAILURE);
	data->index += 3;
	if (mapchar(data) == '\n')
		return (set_next_chunk_index(data));
	return (EXIT_SUCCESS);
}
