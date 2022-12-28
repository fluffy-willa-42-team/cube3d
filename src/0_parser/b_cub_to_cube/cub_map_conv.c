/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map_conv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:04:10 by mahadad           #+#    #+#             */
/*   Updated: 2022/12/28 15:29:47 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d.h"

#include "cube3d_debug.h"

#include <stdio.h>//TODO REMOVE

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Will push 3 char to create a chunk floor in the `.cube` buffer.
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
 * @author @Matthew-Dreemurr
 * 
 * @brief Find the rigth function for the floor given.
 * 
 * @param data Parser structure
 * @param line The current line
 * @param floor The chunk floor to create
 * @return int Return zero value, if there is a error return non zero value.
 */
int	exe_conv(t_parser *data, char *line, int floor)
{
	const t_conv_fct	func[3][7] = {
	{f_123_space, f_1_zero, f_1_one, f_1_p, f_1_p, f_1_p, f_1_p},
	{f_123_space, f_2_zero, f_2_one, f_2_p, f_2_p, f_2_p, f_2_p},
	{f_123_space, f_3_zero, f_3_one, f_3_p, f_3_p, f_3_p, f_3_p}};
	const char			set[8] = {' ', '0', '1', 'N', 'S', 'E', 'W', '\0'};
	int					set_index;

	set_index = 0;
	while (set[set_index] && set[set_index] != *line)
		set_index++;
	if (!set[set_index])
		return (ret_print(EXIT_FAILURE, ERR_BAD_CUB_CHAR));
	if (func[floor][set_index](data, *line))
		return (ret_print(EXIT_FAILURE, ERR_CUB_CONV_FUNC));
	return (EXIT_SUCCESS);
}

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Find the right function to execute for each tree floor of a chunk.
 *        All the function name call will follow this partern:
 *          f_{floor_level}_{char_type}
 * 
 * @param c `.cub` character
 * @return int Return zero value, if there is a error return non zero value.
 */
int	conv_line(t_parser *data, char *line)
{
	int					floor;
	char				*tmp;

	floor = 0;
	while (floor < 3)
	{
		tmp = line;
		while (*tmp && *tmp != '\n')
		{
			if (exe_conv(data, tmp, floor))
				return (EXIT_FAILURE);
			tmp++;
		}
		if (!v_add(&data->cube, STRING, "\n"))
			return (ret_print(EXIT_FAILURE, ERR_VEC_ADD));
		floor++;
	}
	return (EXIT_SUCCESS);
}

/**
 * @author @Matthew-Dreemurr
 *
 * @brief Convert `.cub` map to `.cube` chunk.
 * 
 * @example
 *        Will read each line of the `.cub` to create a 3x3 character chunk.
 *        Its mean tath we will read tree time each line to create eatch floor
 *        of a chunk. Each floor of a chunk have tree different info to store.
 * 
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
 *        If we occur a `'1'` its mean that we need to put the TOP, NORTH,
 *        WEST, EAST, BOTTOM SOUTH with the rigth texture charcter. And for the
 *        ENTITY, TEX, OPT we set it with `'.'` (or E_EMPTY).
 *
 *        If we have a `'0'` we put `'.'` (or E_EMPTY) for NORTH, WEST, EAST,
 *        SOUTH and ENTITY. For the TOP and BOTTOM we put the rigth texture
 *        character of the ceiling and floor.
 *
 *        If we have `{'N','S','E','W'}` First we make the the `'0'` case.
 *        Then we will set ENTITY with the player character `'P'` (or E_PLAYER),
 *        the OPT with the character position `{'N','S','E','W'}`
 *        (or OPT_P_NORTH, OPT_P_SOUTH, OPT_P_EAST, OPT_P_WEST) and the TEX with
 *        the `'.'` character (or E_EMPTY).
 * 
 *        If we have a `' '` we fill all chunk with `' '` character.
 *
 * @param data 
 * @return int 
 */
int	map_conv(t_parser *data)
{
	char		*tmp;

	tmp = data->cub.buffer;
	while (tmp[data->index] && tmp[data->index] == '\n')
		data->index++;
	while (tmp[data->index])
	{
		if (conv_line(data, &tmp[data->index]))
			return (EXIT_FAILURE);
		data->index++;
		while (tmp[data->index] && tmp[data->index] != '\n')
			data->index++;
		if (tmp[data->index])
			data->index++;
	}
	return (EXIT_SUCCESS);
}
