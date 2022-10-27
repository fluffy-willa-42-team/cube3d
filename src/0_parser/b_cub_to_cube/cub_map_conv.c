/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map_conv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:04:10 by mahadad           #+#    #+#             */
/*   Updated: 2022/10/27 19:11:31 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d_debug.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

#include <stdio.h>//TODO REMOVE

/**
 * @brief Will push 3 char to create a chunk floor in the `.cube` buffer.
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
 * @brief 
 * 
 * @param c 
 * @return int 
 */
int	conv_space(t_parser *data, char c)
{
	if (push_chunk_part(data, c, c, c))
		return (ret_print(EXIT_FAILURE, ERR_VEC_ADD));
	return (EXIT_SUCCESS);
}

//TODO Rework C3_DEBUG and add it to cube3d_debug.h
# define C3_DEBUG(ret, msg) d_r(ret, msg, __FILE__, __LINE__, __FUNCTION__);

int	d_r(int err,const char *msg, const char *file, const int line, const char *func)
{
	if (/*TODO C3_DEBUG*/ 1)
		printf("[DEBUG]: %s:%d In function `%s`\n    [%s]\n    return (%d)\n", file, line, func, msg, err);
	return (err);
}

int	dummy(t_parser *data, char c)
{
	C3_DEBUG(23, "test 123");
	printf("dummy[%c]\n", c);
	(void)data;
	return (0);
}

/**
 * @Matthew-Dreemurr
 * 
 * @brief Find the right function to execute for each tree floor of a chunk.
 * 
 * @param c `.cub` character
 * @return int Return zero value, if there is a error return non zero value.
 */
int	exe_conv(t_parser *data, char c)
{
	const char			set[8] = {' ', '0', '1', 'N', 'S', 'E', 'W', '\0'};
	const t_conv_fct	func[3][7] = {
	{conv_space, dummy, dummy, dummy, dummy, dummy, dummy},
	{conv_space, dummy, dummy, dummy, dummy, dummy, dummy},
	{conv_space, dummy, dummy, dummy, dummy, dummy, dummy}};
	int					index;
	int					floor;

	index = 0;
	floor = 0;
	while (set[index] != c)
		index++;
	if (!set[index])
		return (ret_print(EXIT_FAILURE, ERR_BAD_CUB_CHAR));
	while (floor < 3)
	{
		if (func[floor][index](data, c))
			return (EXIT_FAILURE);
		floor++;
	}
	return (EXIT_SUCCESS);
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
		if (exe_conv(data, tmp[data->index]))
			return (EXIT_FAILURE);
		while (tmp[data->index] && tmp[data->index] != '\n')
			data->index++;
		if (tmp[data->index])
			data->index++;
	}
	printf("\n[%s]\n", (char *)data->cube.buffer);//TODO REMOVE DEBUG
	return (EXIT_SUCCESS);
}
