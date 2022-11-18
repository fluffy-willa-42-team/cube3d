/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:09:25 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/18 16:52:54 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d.h"

#include "cube3d_utils.h" /* struct_set */

#include "cube3d_debug.h"

#include "lib_is_check.h" /* ft_isdigit */

#include "lib_mem.h" /* ft_memcpy */

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

#include <stdio.h>//TODO REMOVE

/**
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
int	is_texture_slot_used(t_parser *data, char token)
{
	return (get_tex_ptr(&data->tex_list, token)->token != '\0');
}

/**
 * @brief Check if the token is authorized, if there is no duplication and if
 *        there is no other token after it. Store the token and skip it.
 * 
 * @warning The token can only be one character and must be preceded by a
 *          space character `' '`.
 * 
 * @return int Return `0` if there is no error, otherwise return `1`.
 */
int	set_token(t_parser *data, char *tex, t_texture *tmp)
{
	printf("[%-12s] {%.8s}\n", __FUNCTION__, &tex[data->index]);//TODO REMOVE
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
 * @brief Skip all withe space to the next argument in a texture definition line
 * 
 * @return int   If after the white space the line continue return `0` but if
 *               is the end of the string (aka `'\0'`) return `1`.
 */
int	skip_tex_white_space(t_parser *data, char *tex)
{
	while (tex[data->index] && tex[data->index] == ' ')
		data->index++;
	if (!*tex)
		return (ret_print(EXIT_FAILURE, ERR_TEX_FORMAT));
	return (EXIT_SUCCESS);
}

/**
 * @brief Store texture path or color and set the texture type if is a image
 *        texture or color. Skip the texture path or color.
 *
 * @return int If the texture type is undefine return error `1`.
 */
int	set_texture(t_parser *data, char *tex, t_texture *tmp)
{
	printf("[%-12s] {%.8s}\n", __FUNCTION__, &tex[data->index]);//TODO REMOVE
	tmp->type |= find_tex_type(&tex[data->index]);
	if (tmp->type == UNDEFINED)
		return (ret_print(EXIT_FAILURE, ERR_TEX_TYPE));
	tmp->path = &tex[data->index];
	while (tex[data->index] && tex[data->index] != ' ')
		data->index++;
	return (EXIT_SUCCESS);
}

int	set_texture_allow_clip(char param, t_texture *tmp)
{
	if (param == 'v')
		tmp->type |= ALLOW_CLIP;
	else if (param != 'x')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	set_texture_transparency(char param, t_texture *tmp)
{
	if (param == 'v')
		tmp->type |= TRANSPARENCY;
	else if (param != 'x')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	set_texture_skybox(char param, t_texture *tmp)
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

	printf("[%-12s] {%.8s}\n", __FUNCTION__, &tex[data->index]);//TODO REMOVE
	if (set_texture_allow_clip(param[0], tmp)
		|| set_texture_transparency(param[1], tmp)
		|| set_texture_skybox(param[2], tmp))
		return (ret_print(EXIT_FAILURE, ERR_TEX_PARAM));
	while (tex[data->index] && tex[data->index] != ' ')
		data->index++;
	return (EXIT_SUCCESS);
}

/**
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
int	store_current_tex(t_parser *data, char *tex)
{
	t_texture	tmp;

	ft_memset(&tmp, '\0', sizeof(tmp));
	data->index = 0;
	if (set_token(data, tex, &tmp)
		|| skip_tex_white_space(data, tex) || set_texture_param(data, tex, &tmp)
		|| skip_tex_white_space(data, tex) || set_texture(data, tex, &tmp))
		return (EXIT_FAILURE);
	*get_tex_ptr(&data->tex_list, tmp.token) = tmp;
	return (EXIT_SUCCESS);
}



/**
 * @brief Check if a line start with a sequence cube comment or
 *        separator sequence.
 *        Return `SEQ_NO`       if there is no sequence
 *        Return `SEQ_ERR`      if there is a bad sequence
 *        Return `SEQ_COMM`     if is a comment sequence (or `SEQ[0]`)
 *        Return `SEQ_ENDOFTEX` if is a separator sequence (or `SEQ`)
 *
 * @warning The sequence must be used only at the beginning of a new line.
 *          If there is another character before the sequence in the line it is
 *          an undefined behavior.
 * 
 * @param line 
 * @return int Return `SEQ_NO`, `SEQ_ERR`, `SEQ_COMM` or `SEQ_ENDOFTEX`
 */
int	which_escape_seq(char *line)
{
	int			len;

	len = 0;
	if (*line != SEQ[0])
		return (SEQ_NO);
	while (line[len] && line[len] == SEQ[0])
		len++;
	if (len == 1)
		return (SEQ_COMM);
	if (len == SEQ_LEN)
		return (SEQ_ENDOFTEX);
	return (SEQ_ERR);
}


/**
 * @brief Store all texture data in the `data.tex_list` array vector. Finally
 *        set `data.cube_map` to the cube separator sequence line.
 *
 * @warning Store raw data, there is no check if the texture input is valid !
 * 
 * @note
 * [token] [[allow_clip],[transparency],[token_skybox]] [texture_path, color]]
 * @param data 
 * @param tex 
 * @return int 
 */
int	store_texture(t_parser *data, char *tex)
{
	data->tex_list = v_init(sizeof(t_texture), NULL, NULL);
	if (!v_alloc(&data->tex_list, SET, DEFAUT_CUBE_TEX_NB))
		return (ret_print(EXIT_FAILURE, ERR_VEC_ALLOC));
	while (*tex)
	{
		while (*tex && (*tex == ' ' || *tex == '\n'))
			tex++;
		if (!*tex)
			break ;
		if (*tex == SEQ[0])
		{
			if (which_escape_seq(tex) == SEQ_COMM)
				;
			else if (which_escape_seq(tex) == SEQ_ENDOFTEX)
				break ;
			else if (which_escape_seq(tex) == SEQ_ERR)
				return (ret_print(EXIT_FAILURE, ERR_SEQ_BAD));
		}
		else if (store_current_tex(data, tex))
			return (EXIT_FAILURE);
		while (*tex && *tex != '\n')
			tex++;
	}
	data->cube_map = tex;
	return (EXIT_SUCCESS);
}
