/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tex_config_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 10:59:24 by awillems          #+#    #+#             */
/*   Updated: 2022/12/30 11:00:16 by awillems         ###   ########.fr       */
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
int	set_texture_allow_clip(char param, t_texture *tmp)
{
	if (param == 'v')
		tmp->type |= NO_CLIP;
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
int	set_texture_transparency(char param, t_texture *tmp)
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
int	set_texture_skybox(char param, t_texture *tmp)
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
int	set_texture_pointer(char param, t_texture *tmp)
{
	if (authzed_cube_tex(param))
		tmp->token_ptr = param;
	else if (param != '.')
		return (ret_print(EXIT_FAILURE, NULL));
	return (EXIT_SUCCESS);
}
