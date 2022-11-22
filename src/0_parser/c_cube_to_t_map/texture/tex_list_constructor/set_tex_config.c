/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tex_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:09:15 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/22 14:57:39 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d_utils.h"

#include "cube3d_debug.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

#include <stdio.h>//TODO REMOVE

static int	set_texture_allow_clip(char param, t_texture *tmp)
{
	if (param == 'v')
		tmp->type |= ALLOW_CLIP;
	else if (param != 'x')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	set_texture_transparency(char param, t_texture *tmp)
{
	if (param == 'v')
		tmp->type |= TRANSPARENCY;
	else if (param != 'x')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	set_texture_skybox(char param, t_texture *tmp)
{
	if (authzed_cube_tex(param))
		tmp->type |= SKYBOX;
	else if (param != '.')
		return (EXIT_FAILURE);
	tmp->sky_box_token = param;
	return (EXIT_SUCCESS);
}

/**
 * @brief 
 * 
 * [[allow_clip] [transparency],     [token_tex_skybox]]
 * [x,v]         [x,v]               [autohirize_token, `'.'`]
 *
 * @return int 
 */
int	set_texture_param(t_parser *data, char *tex, t_texture *tmp)
{
	const char	*param = &tex[data->index];

	if (set_texture_allow_clip(param[0], tmp)
		|| set_texture_transparency(param[1], tmp)
		|| set_texture_skybox(param[2], tmp))
		return (ret_print(EXIT_FAILURE, ERR_TEX_PARAM));
	while (tex[data->index] && tex[data->index] != ' ')
		data->index++;
	return (EXIT_SUCCESS);
}

/**
 * @brief Store texture path or color and set the texture type if is a image
 *        texture or color. Skip the texture path or color.
 *
 * @return int If the texture type is undefine return error `1`.
 */
int	set_texture_path(t_parser *data, char *tex, t_texture *tmp)
{
	tmp->type |= find_tex_type(&tex[data->index]);
	if (tmp->type == UNDEFINED)
		return (ret_print(EXIT_FAILURE, ERR_TEX_TYPE));
	tmp->path = &tex[data->index];
	while (tex[data->index] && tex[data->index] != ' ')
		data->index++;
	return (EXIT_SUCCESS);
}
