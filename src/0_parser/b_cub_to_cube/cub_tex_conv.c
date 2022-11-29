/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_tex_conv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:01:25 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/29 09:24:16 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d_debug.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

#include <stdio.h>//TODO REMOVE

/**
 * @author @Matthew-Dreemurr
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
	while (x < DEFAULT_CUB_TEX_NB)
	{
		if (!data->tex[x])
			return (0);
		x++;
	}
	return (1);
}

static void	skip_whitespace(t_parser *data, char *tmp)
{
	while (tmp[data->index] != ' ')
		data->index++;
	while (tmp[data->index] == ' ')
		data->index++;
}

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Convert the texture name with arbitrary index and the texture path.
 * 
 * @note
 * `WE ./path_to_the_west_texture` -> `2 xx* ./path_to_the_west_texture`
 * `cub`   [tex token] [tex path/color]
 * `cube`  [tex token] [allow clip][transparency][token skybox] [tex path/color]
 * 
 * For the [allow_clip][transparency] we set to `x` aka false.
 * And for the [token_skybox] `.` aka none.
 * 
 * @param data Parser struct
 * @param tmp ptr to the `.cub` string
 * @param tex_index index of the texture.
 * @return  int Return 1 if the `c` is find in the `set` otherwise return 0.
 */
static int	cub_tex_to_cube(t_parser *data, char *tmp, int tex_index)
{
	if (!v_add(&data->cube, STRING, "%c xx. ", '0' + tex_index))
		return (ret_print(EXIT_FAILURE, ERR_VEC_ADD));
	skip_whitespace(data, tmp);
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
 * @author @Matthew-Dreemurr
 * 
 * @brief Convert all texture name to the `.cube` format.
 * 
 * @note Will rename all texture `.cube` token with arbitrary token.
 *
 *       "NO"  -> 0
 *       "SO"  -> 1
 *       "WE"  -> 2
 *       "EA"  -> 3
 *       "F"   -> 4
 *       "C"   -> 5
 * 
 * @param data Parser structure.
 * @return int Return 1 if the `c` is find in the `set` otherwise return 0.
 */
int	texture_conv(t_parser *data)
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
	if (!v_add(&data->cube, STRING, SEQ"\n"))
		return (ret_print(EXIT_FAILURE, ERR_VEC_ADD));
	return (EXIT_SUCCESS);
}
