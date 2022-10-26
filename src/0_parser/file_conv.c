/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_conv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:52:08 by mahadad           #+#    #+#             */
/*   Updated: 2022/10/26 11:52:47 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d_debug.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

#include <stdio.h>//TODO REMOVE

/**
 * @brief Return texture index [0->5] and check if there is no duplicate,
 *        if an error occur return `-1`.
 * 
 * @return int Texture index otherwise `-1`
 */
static int	check_texture(char *str, t_parser *data)
{
	const char	*id[DEFAUT_TEX_NB] = {"NO", "SO", "WE", "EA", "F", "C"};
	int			index;
	int			x;

	index = 0;
	while (index < DEFAUT_TEX_NB)
	{
		x = 0;
		while (id[index][x] && str[x] == id[index][x])
			x++;
		if (!id[index][x] && str[x] == ' ')
		{
			if (data->tex[index])
				return (ret_print(-1, ERR_TEX_DUP));
			data->tex[index] = 1;
			return (index);
		}
		index ++;
	}
	return (ret_print(-1, ERR_TEX_FORMAT));
}

/**
 * @brief Return texture index [0->5] and check if there is no duplicate,
 *        if an error occur return `-1`.
 * 
 * @return int Texture index otherwise `-1`
 */
static int	get_tex(char *str)
{
	const char	*id[DEFAUT_TEX_NB] = {"NO", "SO", "WE", "EA", "F", "C"};
	int			index;
	int			x;

	index = 0;
	while (index < DEFAUT_TEX_NB)
	{
		x = 0;
		while (id[index][x] && str[x] == id[index][x])
			x++;
		if (!id[index][x] && !str[x])
			return (index + '0');
		index ++;
	}
	return (ret_print(-1, ERR_TEX_FORMAT));
}

/**
 * @Matthew-Dreemurr
 * 
 * @brief Check in `data.tex[]` if all the texture have been find.
 * 
 * @param data Parser struct
 * @return int Return `1` if all texture is there, if not `0`.
 */
static int	is_all_tex(t_parser *data)
{
	int	x;

	x = 0;
	while (x < DEFAUT_TEX_NB)
	{
		if (!data->tex[x])
			return (0);
		x++;
	}
	return (1);
}
#include <stdio.h>//TODO REMOVE DEBUG


/**
 * @brief Convert the texture name with arbitrary index and the texture path.
 * 
 * @example `WE ./path_to_the_west_texture` -> `2 ./path_to_the_west_texture`
 * 
 * @param data Parser struct
 * @param tmp ptr to the `.cub` string
 * @param tex_index index of the texture.
 * @return  int Return 1 if the `c` is find in the `set` otherwise return 0.
 */
static int	cub_tex_to_cube(t_parser *data, char *tmp, int tex_index)
{
	if (!v_add(&data->cube, STRING, "%c ", '0' + tex_index))
		return (ret_print(EXIT_FAILURE, ERR_VEC_ADD));
	while (tmp[data->index] != ' ')
		data->index++;
	while (tmp[data->index] == ' ')
		data->index++;
	while (tmp[data->index] && tmp[data->index] != '\n')
	{
		if (!v_add(&data->cube, STRING, "%c", tmp[data->index]))
			return (ret_print(EXIT_FAILURE, ERR_VEC_ADD));
		data->index++;
	}
	if (!v_add(&data->cube, STRING, "\n"))
		return (ret_print(EXIT_FAILURE, ERR_VEC_ADD));
	if (!tmp[data->index])
		return (ret_print(EXIT_FAILURE, ERR_NO_MAP_AFTER_TEX));
	return (EXIT_SUCCESS);
}

/**
 * @Matthew-Dreemurr
 * 
 * @brief Convert all texture name to the `.cube` format.
 * 
 * @param data Parser structure.
 * @return int Return 1 if the `c` is find in the `set` otherwise return 0.
 */
static int	texture_conv(t_parser *data)
{
	char		*tmp;
	int			index;

	data->index = -1;
	tmp = data->cub.buffer;
	while (tmp[++data->index])
	{
		if (is_all_tex(data))
			break ;
		if (tmp[data->index] == '\n')
			continue ;
		index = check_texture(&tmp[data->index], data);
		if (index == -1)
			return (EXIT_FAILURE);
		if (cub_tex_to_cube(data, tmp, index))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 *     TOP    | NORTH | ENTITY
 *     -------0-------0-------
 *     WEST   | TAG   | EAST
 *     -------0-------0-------
 *     BOTTOM | SOUTH | TAG
 */


/**
 * @brief Will push 3 char to create a chunk level in the `.cube` buffer.
 * 
 * @param a First char
 * @param b Second char
 * @param c Last char
 * @return int 
 */
int	push_chunk_part(t_parser *data, int a, int b, int c)
{
	char	buff[4];

	buff[0] = a;
	buff[1] = b;
	buff[2] = c;
	buff[3] = '\0';
	if (!v_add(&data->cube, STRING, buff))
		return (ret_print(EXIT_FAILURE, ERR_VEC_ADD));
	return (EXIT_SUCCESS);
}

/**
 * @brief Convert to the first chunk line.
 *     TOP, NORTH, ENTITY
 *
 * @return int 
 */
int	conv_chunk_1(t_parser *data)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = &((char *)data->cub.buffer)[data->index];
	while (tmp[i] && tmp[i] != '\n')
	{
		if (tmp[i] == ' ')
			push_chunk_part(data, ' ', ' ', ' ');
		else if (tmp[i] == '0')
			push_chunk_part(data, '.', '.', '.');
		else if (tmp[i] == '1')
			push_chunk_part(data, get_tex("C"), get_tex("NO"), '!');
		else
		{
			push_chunk_part(data, '!', '!', '!');
		}
		i++;
	}
	if (!v_add(&data->cube, STRING, "\n"))
		return (ret_print(EXIT_FAILURE, ERR_VEC_ADD));
	return (EXIT_SUCCESS);
}

/**
 * @brief Convert to the first chunk line.
 *     WEST, TAG, EAST
 *
 * @return int 
 */
int	conv_chunk_2(t_parser *data)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = &((char *)data->cub.buffer)[data->index];
	while (tmp[i] && tmp[i] != '\n')
	{
		if (tmp[i] == ' ')
			push_chunk_part(data, ' ', ' ', ' ');
		else if (tmp[i] == '0')
			push_chunk_part(data, '.', '.', '.');
		else if (tmp[i] == '1')
			push_chunk_part(data, get_tex("WE"), '!', get_tex("EA"));
		else
			push_chunk_part(data, '!', '!', '!');
		i++;
	}
	if (!v_add(&data->cube, STRING, "\n"))
		return (ret_print(EXIT_FAILURE, ERR_VEC_ADD));
	return (EXIT_SUCCESS);
}

/**
 * @brief Convert to the first chunk line.
 *     BOTTOM, SOUTH, TAG
 *
 * 
 * @return int 
 */
int	conv_chunk_3(t_parser *data)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = &((char *)data->cub.buffer)[data->index];
	while (tmp[i] && tmp[i] != '\n')
	{
		if (tmp[i] == ' ')
			push_chunk_part(data, ' ', ' ', ' ');
		else if (tmp[i] == '0')
			push_chunk_part(data, '.', '.', '.');
		else if (tmp[i] == '1')
			push_chunk_part(data, get_tex("F"), get_tex("SO"), '!');
		else
			push_chunk_part(data, '!', '!', '!');
		i++;
	}
	if (!v_add(&data->cube, STRING, "\n"))
		return (ret_print(EXIT_FAILURE, ERR_VEC_ADD));
	return (EXIT_SUCCESS);
}

/**
 * @brief Convert `.cub` map to `.cube` chunk.
 *        Call `conv_chunk_{1,2,3}` each line.
 * 
 * @param data 
 * @return int 
 */
int	map_conv(t_parser *data)
{
	char	*tmp;

	tmp = data->cub.buffer;
	while (tmp[data->index] && tmp[data->index] == '\n')
		data->index++;
	while (tmp[data->index])
	{
		conv_chunk_1(data);
		conv_chunk_2(data);
		conv_chunk_3(data);
		while (tmp[data->index] && tmp[data->index] != '\n')
			data->index++;
		if (tmp[data->index])
			data->index++;
	}
	printf("\n[%s]\n", (char *)data->cube.buffer);//TODO REMOVE DEBUG
	return (EXIT_SUCCESS);
}

/**
 * @brief Try to find all mandatory texture and convert to `.cube` format. Then
 *        convert map to `.cube` format.
 * 
 * @param data Parser structure
 * @return int Return 1 if the `c` is find in the `set` otherwise return 0. 
 */
static int	conversion(t_parser *data)
{
	data->cube = v_init(sizeof(char), NULL, NULL);
	if (texture_conv(data) || map_conv(data)/*//WIP*/)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @Matthew-Dreemurr
 * 
 * @brief Convert `.cub` to `.cube` format.
 * 
 * @param data Parser structure
 * @return int Return 1 if the `c` is find in the `set` otherwise return 0.
 */
int	file_conv(t_parser *data)
{
	if (data->type == CUB_FILE)
		if (conversion(data) || !v_delete(&data->cub)/* //TODO change check after the lib update ! */)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
