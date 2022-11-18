/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:48:29 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/17 12:04:02 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d.h"

#include "cube3d_utils.h"

#include "cube3d_debug.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

#include <stdio.h>//TODO REMOVE


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
	const	char *f1 = mapptr(data);
	const	char *f2 = mapptr(data) + data->index + data->tmp_width + 1;
	const	char *f3 = mapptr(data) + 2 * (data->index + data->tmp_width + 1);

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

int	store_entity_data(t_parser *data, t_chunk *chunk, t_chunk_token *tmp)
{
	(void)data;
	(void)chunk;
	(void)tmp;
	return (EXIT_SUCCESS);
}


/**
 * @brief Check if all the token of the current is only white space `' '`.
 * 
 * @warning A chunk with white space `' '` can not have data !
 */
int	is_all_white_space_tokens(t_chunk_token *tokens)
{
	return (tokens->ceiling == ' '
		&& tokens->east == ' '
		&& tokens->entity == ' '
		&& tokens->floor == ' '
		&& tokens->floor == ' '
		&& tokens->north == ' '
		&& tokens->opt == ' '
		&& tokens->south == ' '
		&& tokens->tex == ' '
		&& tokens->west == ' ');
}

/**
 * @brief Check if all the token of the current chunk is valid.
 * 
 * @warning A chunk with data can not have white space token `' '` !
 */
int	is_all_valid_tokens(t_chunk_token *tokens)
{
	return (authzed_chunk_char(tokens->ceiling)
		&& authzed_chunk_char(tokens->east)
		&& authzed_chunk_char(tokens->floor)
		&& authzed_chunk_char(tokens->floor)
		&& authzed_chunk_char(tokens->north)
		&& authzed_chunk_char(tokens->south)
		&& authzed_chunk_char(tokens->entity)
		&& authzed_chunk_char(tokens->tex)
		&& authzed_chunk_char(tokens->opt)
		&& authzed_chunk_char(tokens->west));
}

int	check_chunk_type(t_chunk_token *tokens)
{
	if (is_all_white_space_tokens(tokens))
	{
		tokens->type = WHITE_SPACE_CHUNK;
		return (WHITE_SPACE_CHUNK);
	}
	if (is_all_valid_tokens(tokens))
	{
		tokens->type = GOOD_CHUNK;
		return (GOOD_CHUNK);
	}
	tokens->type = BAD_CHUNK;
	return (BAD_CHUNK);
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
	// if (set_floor_1(data, chunk)
	// 	|| set_floor_2(data, chunk)
	// 	|| set_floor_3(data, chunk))
	// 	return (EXIT_FAILURE);
	if (set_chunk(data, chunk))
		return (EXIT_FAILURE);
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
 * @brief Get the `t_chunk` from the array with the coordinate `{x, y}`.
 * 
 * @return t_chunk* Return pointer from the array.
 */
t_chunk *get_chunk(t_parser *data, int x, int y)
{
	const int index = (y * data->map_size.x) + x;

	return (v_get(&data->map, index));
}

/**
 * @brief Set the chunk coord, `t_chunk.coor.{x,y}`
 * 
 * @param data 
 */
void	set_chunk_coord(t_parser *data)
{
	const int	max = data->map_size.x * data->map_size.y;
	int			index;
	t_coord_i32	coor;
	t_chunk	*tmp;

	index = 0;
	struct_set(&coor, sizeof(coor));
	while (index < max)
	{
		if (coor.x >= data->map_size.x)
		{
			coor.x = 0;
			coor.y++;
		}
		tmp = get_chunk(data, coor.x, coor.y);
		tmp->coord.x = coor.x;
		tmp->coord.y = coor.y;
		coor.x++;
		index++;
	}
}

void	t_map_debug(t_parser *data)
{
	const int	max = data->map_size.x * data->map_size.y;
	int			index;
	t_coord_i32	coor;
	t_chunk	*tmp;

	index = 0;
	struct_set(&coor, sizeof(coor));
	while (index < max)
	{
		if (coor.x >= data->map_size.x)
		{
			coor.x = 0;
			coor.y++;
		}
		printf("(%d)x(%d)\n", coor.x, coor.y);
		tmp = get_chunk(data, coor.x, coor.y);
		if (tmp->type == WHITE_SPACE_CHUNK)
		{
			printf("[ , , ,]\n[ , , ,]\n[ , , ,]\n[ , , ,]\n");
		}
		else
		{
			printf("[%c,%c,.]\n[%c,%c,.]\n[%c,%c,.]\n[ %d, %d]\n\n",
			tmp->ceiling ? (tmp->ceiling->token ? tmp->ceiling->token : '.') : '.' ,
			tmp->north ? (tmp->north->token ? tmp->north->token : '.') : '.' ,

			tmp->west ? (tmp->west->token ? tmp->west->token : '.') : '.' ,
			tmp->east ? (tmp->east->token ? tmp->east->token : '.') : '.' ,
			
			tmp->floor ? (tmp->floor->token ? tmp->floor->token : '.') : '.' ,
			tmp->south ? (tmp->south->token ? tmp->south->token : '.') : '.',

			tmp->coord.x,
			tmp->coord.y
			);
		}
		coor.x++;
		index++;
	}
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
	if (set_map_size(data) || init_map(data))
		return (EXIT_FAILURE);
	set_chunk_coord(data);
	t_map_debug(data);//TODO REMOVE
	
	// printf("{{\n%s\n}}\n",data->cube_map);printf("map size [%dx%d]\n", data->map_size.x,data->map_size.y);
	return (EXIT_SUCCESS);
}
