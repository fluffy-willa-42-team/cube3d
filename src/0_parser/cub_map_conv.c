/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map_conv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:04:10 by mahadad           #+#    #+#             */
/*   Updated: 2022/10/26 12:06:24 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d_debug.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

#include <stdio.h>//TODO REMOVE


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
static int	push_chunk_part(t_parser *data, int a, int b, int c)
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
static int	conv_chunk_1(t_parser *data)
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
static int	conv_chunk_2(t_parser *data)
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
static int	conv_chunk_3(t_parser *data)
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
