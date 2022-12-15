/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tex_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:09:15 by mahadad           #+#    #+#             */
/*   Updated: 2022/12/15 11:36:31 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d_utils.h"

#include "cube3d_debug.h"

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Check the texture argument of the allow clip.
 * 
 * @note [token] [allow_clip][transparency][skybox] [tex path/color]
 *
 *
 */
static int	set_texture_allow_clip(char param, t_texture *tmp)
{
	if (param == 'v')
		tmp->type |= ALLOW_CLIP;
	else if (param != 'x')
		return (ret_print(EXIT_FAILURE, NULL));
	return (EXIT_SUCCESS);
}

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Check the texture argument of the texture transparency.
 * 
 * @note [token] [allow_clip][transparency][skybox] [tex path/color]
 */
static int	set_texture_transparency(char param, t_texture *tmp)
{
	if (param == 'v')
		tmp->type |= TRANSPARENCY;
	else if (param != 'x')
		return (ret_print(EXIT_FAILURE, NULL));
	return (EXIT_SUCCESS);
}

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Check the texture argument of the texture skybox.
 * 
 * @note [token] [allow_clip][transparency][skybox] [tex path/color]
 */
static int	set_texture_skybox(char param, t_texture *tmp)
{
	if (param == 'v')
		tmp->type |= SKYBOX;
	else if (param != 'x')
		return (ret_print(EXIT_FAILURE, NULL));
	return (EXIT_SUCCESS);
}

/**
 * @author @Matthew-Dreemurr
 *
 * @brief Check the texture argument of the texture skybox.
 *
 * @note [token] [allow_clip][transparency][skybox] [tex path/color]
 */
static int	set_texture_pointer(char param, t_texture *tmp)
{
	if (authzed_cube_tex(param))
		tmp->token_ptr = param;
	else if (param != '.')
		return (ret_print(EXIT_FAILURE, NULL));
	return (EXIT_SUCCESS);
}

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Set the texture param and path/color.
 * 
 * @note
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
		|| set_texture_skybox(param[2], tmp)
		|| set_texture_pointer(param[3], tmp))
		return (ret_print(EXIT_FAILURE, ERR_TEX_PARAM));
	while (tex[data->index] && tex[data->index] != ' ')
		data->index++;
	return (EXIT_SUCCESS);
}

/**
 * @author @Matthew-Dreemurr
 * 
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
