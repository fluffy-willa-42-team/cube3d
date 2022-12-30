/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tex_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:09:15 by mahadad           #+#    #+#             */
/*   Updated: 2022/12/30 11:00:19 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d_utils.h"

#include "cube3d_debug.h"

int	set_texture_allow_clip(char param, t_texture *tmp);
int	set_texture_transparency(char param, t_texture *tmp);
int	set_texture_skybox(char param, t_texture *tmp);
int	set_texture_pointer(char param, t_texture *tmp);

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
