/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map_conv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:04:10 by mahadad           #+#    #+#             */
/*   Updated: 2022/10/26 16:12:46 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d_debug.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

#include <stdio.h>//TODO REMOVE

// /**
//  * @brief Will push 3 char to create a chunk level in the `.cube` buffer.
//  * 
//  * @param a First char
//  * @param b Second char
//  * @param c Last char
//  * @return int 
//  */
// static int	push_chunk_part(t_parser *data, int a, int b, int c)
// {
// 	char	buff[4];

// 	buff[0] = a;
// 	buff[1] = b;
// 	buff[2] = c;
// 	buff[3] = '\0';
// 	if (!v_add(&data->cube, STRING, buff))
// 		return (ret_print(EXIT_FAILURE, ERR_VEC_ADD));
// 	return (EXIT_SUCCESS);
// }

// /**
//  * @brief Convert to the first chunk line.
//  *     TOP, NORTH, ENTITY
//  *
//  * @return int 
//  */
// static int	conv_chunk_1(t_parser *data)
// {
// 	int		i;
// 	char	*tmp;

// 	i = 0;
// 	tmp = &((char *)data->cub.buffer)[data->index];
// 	while (tmp[i] && tmp[i] != '\n')
// 	{
// 		if (tmp[i] == ' ')
// 			push_chunk_part(data, ' ', ' ', ' ');
// 		else if (tmp[i] == '0')
// 			push_chunk_part(data, '.', '.', '.');
// 		else if (tmp[i] == '1')
// 			push_chunk_part(data, get_tex("C"), get_tex("NO"), '!');
// 		else
// 			push_chunk_part(data, '!', '!', '!');
// 		i++;
// 	}
// 	if (!v_add(&data->cube, STRING, "\n"))
// 		return (ret_print(EXIT_FAILURE, ERR_VEC_ADD));
// 	return (EXIT_SUCCESS);
// }

// /**
//  * @brief Convert to the first chunk line.
//  *     WEST, TAG, EAST
//  *
//  * @return int 
//  */
// static int	conv_chunk_2(t_parser *data)
// {
// 	int		i;
// 	char	*tmp;

// 	i = 0;
// 	tmp = &((char *)data->cub.buffer)[data->index];
// 	while (tmp[i] && tmp[i] != '\n')
// 	{
// 		if (tmp[i] == ' ')
// 			push_chunk_part(data, ' ', ' ', ' ');
// 		else if (tmp[i] == '0')
// 			push_chunk_part(data, '.', '.', '.');
// 		else if (tmp[i] == '1')
// 			push_chunk_part(data, get_tex("WE"), '!', get_tex("EA"));
// 		else
// 			push_chunk_part(data, '!', '!', '!');
// 		i++;
// 	}
// 	if (!v_add(&data->cube, STRING, "\n"))
// 		return (ret_print(EXIT_FAILURE, ERR_VEC_ADD));
// 	return (EXIT_SUCCESS);
// }

// /**
//  * @brief Convert to the first chunk line.
//  *     BOTTOM, SOUTH, TAG
//  *
//  * 
//  * @return int 
//  */
// static int	conv_chunk_3(t_parser *data)
// {
// 	int		i;
// 	char	*tmp;

// 	i = 0;
// 	tmp = &((char *)data->cub.buffer)[data->index];
// 	while (tmp[i] && tmp[i] != '\n')
// 	{
// 		if (tmp[i] == ' ')
// 			push_chunk_part(data, ' ', ' ', ' ');
// 		else if (tmp[i] == '0')
// 			push_chunk_part(data, '.', '.', '.');
// 		else if (tmp[i] == '1')
// 			push_chunk_part(data, get_tex("F"), get_tex("SO"), '!');
// 		else
// 			push_chunk_part(data, '!', '!', '!');
// 		i++;
// 	}
// 	if (!v_add(&data->cube, STRING, "\n"))
// 		return (ret_print(EXIT_FAILURE, ERR_VEC_ADD));
// 	return (EXIT_SUCCESS);
// }

int	dummy()
{
	return 0;
}

/**
 * @author Matthew-Dreemurr
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
 *        ENTITY, TYPE, OPT will store player info, it will be set only if
 *        we have the `{'N','S','E','W'}` characters. ENTITY will be set with
 *        `'P'` (or E_PLAYER) and OPT with the character position
 *        `{'N','S','E','W'}` (or OPT_P_NORTH, OPT_P_SOUTH, OPT_P_EAST,
 *        OPT_P_WEST). In other case all info will be set with the `'.'` 
 *        character (or E_EMPTY).
 *
 *        floor 1 : TOP    | NORTH | ENTITY
 *                  -------0-------0-------
 *        floor 2 : WEST   | EAST  | TEX
 *                  -------0-------0-------
 *        floor 3 : BOTTOM | SOUTH | OPT
 *
 *        If we occur a `'1'` its mean that we need to put the TOP, NORTH,
 *        WEST, EAST, BOTTOM SOUTH with the rigth texture charcter. And for the
 *        ENTITY, TYPE, OPT we set it with `'.'` (or E_EMPTY).
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
	const char			*index = {' ', '0', '1', 'N', 'S', 'E', 'W'};
	const t_conv_fct	func[3][7] = {
		{dummy, dummy, dummy, dummy, dummy, dummy, dummy},
		{dummy, dummy, dummy, dummy, dummy, dummy, dummy},
		{dummy, dummy, dummy, dummy, dummy, dummy, dummy}};

	(void)func;
	tmp = data->cub.buffer;
	while (tmp[data->index] && tmp[data->index] == '\n')
		data->index++;
	while (tmp[data->index])
	{
		while (tmp[data->index] && tmp[data->index] != '\n')
			data->index++;
		if (tmp[data->index])
			data->index++;
	}
	printf("\n[%s]\n", (char *)data->cube.buffer);//TODO REMOVE DEBUG
	return (EXIT_SUCCESS);
}
