/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_current_tex_config.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:03:25 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/29 13:50:46 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d_debug.h"

/* get_tex_ptr() */
#include "cube3d_utils.h"

#include "lib_mem.h" /* ft_memcpy */

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Skip all withe space to the next argument in a texture definition line
 * 
 * @return int   If after the white space the line continue return `0` but if
 *               is the end of the string (aka `'\0'`) return `1`.
 */
static int	skip_tex_white_space(t_parser *data, char *tex)
{
	while (tex[data->index] && tex[data->index] == ' ')
		data->index++;
	if (!*tex)
		return (ret_print(EXIT_FAILURE, ERR_TEX_FORMAT));
	return (EXIT_SUCCESS);
}

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Check if the texture slot of the given toke was already init. We use
 *        this check to find duplication.
 *
 * @note We check if the token of the texture slot is != from `'\0'`, if is not
 *       the case, the slot is already used.
 * 
 * @warning The `data->tex_list` need to be memset to `0`, or all the token set
 *          to `'\0'` to avoid garbadge memory.
 * 
 * @return int If the slot is used return `1` otherwise `0`.
 */
static int	is_texture_slot_used(t_parser *data, char token)
{
	return (get_tex_ptr(&data->tex_list, token)->token != '\0');
}

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Check if the token is authorized, if there is no duplication and if
 *        there is no other token after it. Store the token and skip it.
 * 
 * @warning The token can only be one character and must be preceded by a
 *          space character `' '`.
 * 
 * @return int Return `0` if there is no error, otherwise return `1`.
 */
static int	set_token(t_parser *data, char *tex, t_texture *tmp)
{
	if (!authzed_cube_tex(tex[data->index]))
		return (ret_print(EXIT_FAILURE, ERR_TEX_RESERVED));
	if (is_texture_slot_used(data, tex[data->index]))
		return (ret_print(EXIT_FAILURE, ERR_TEX_DUP));
	tmp->token = tex[data->index];
	data->index++;
	if (tex[data->index] != ' ')
		return (ret_print(EXIT_FAILURE, ERR_TEX_TOKEN_FORMAT));
	return (EXIT_SUCCESS);
}

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Will set a tmp `t_texture` struct and push it in the
 *        `t_data `data.tex_list array vector. Check if the texture has not
 *        already been initiated. `data.path` will point the first character
 *        address in `data.cube`.
 * 
 * @warning Texture `token` is only one char, if there is more than one return
 *          error. `token`, `type` or `path` texture need to be separated only
 *          by space and only one texture definition by line !
 * 
 * @param data 
 * @param tex 
 * @return int 
 */
int	set_current_tex_config(t_parser *data, char *tex)
{
	t_texture	tmp;

	ft_memset(&tmp, '\0', sizeof(t_texture));
	data->index = 0;
	if (set_token(data, tex, &tmp)
		|| skip_tex_white_space(data, tex) || set_texture_param(data, tex, &tmp)
		|| skip_tex_white_space(data, tex) || set_texture_path(data, tex, &tmp))
		return (EXIT_FAILURE);
	*get_tex_ptr(&data->tex_list, tmp.token) = tmp;
	return (EXIT_SUCCESS);
}
