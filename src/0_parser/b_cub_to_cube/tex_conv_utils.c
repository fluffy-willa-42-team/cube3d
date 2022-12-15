/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_conv_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:10:55 by mahadad           #+#    #+#             */
/*   Updated: 2022/12/15 11:35:58 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d_debug.h"

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Return texture index [0->5] {"NO", "SO", "WE", "EA", "F", "C"},
 *        if an error occur return `-1`.
 * 
 * @return int Texture index otherwise `-1`
 */
int	get_tex(char *str)
{
	const char	*id[DEFAULT_CUB_TEX_NB] = {"NO", "SO", "WE", "EA", "F", "C"};
	int			index;
	int			x;

	index = 0;
	while (index < DEFAULT_CUB_TEX_NB)
	{
		x = 0;
		while (id[index][x] && str[x] == id[index][x])
			x++;
		if (!id[index][x] && !str[x])
			return (index + '0');
		index ++;
	}
	return (-1);
}

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Return texture index [0->5] and check if there is no duplicate,
 *        if an error occur return `-1`.
 * 
 * @return int Texture index otherwise `-1`
 */
int	check_texture(char *str, t_parser *data)
{
	const char	*id[DEFAULT_CUB_TEX_NB] = {"NO", "SO", "WE", "EA", "F", "C"};
	int			index;
	int			x;

	index = 0;
	while (index < DEFAULT_CUB_TEX_NB)
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
