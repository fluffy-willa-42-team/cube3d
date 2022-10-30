/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_conv_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:10:55 by mahadad           #+#    #+#             */
/*   Updated: 2022/10/30 17:36:15 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d_debug.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

/**
 * @brief Return texture index [0->5] {"NO", "SO", "WE", "EA", "F", "C"},
 *        if an error occur return `-1`.
 * 
 * @return int Texture index otherwise `-1`
 */
int	get_tex(char *str)
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
 * @brief Return texture index [0->5] and check if there is no duplicate,
 *        if an error occur return `-1`.
 * 
 * @return int Texture index otherwise `-1`
 */
int	check_texture(char *str, t_parser *data)
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
