/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:09:25 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/18 12:58:58 by mahadad          ###   ########.fr       */
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
 * @brief Will set a tmp `t_texture` struct and push it in the
 *        `t_data `data.tex_list array vector. Check if the texture has not
 *        already been initiated. `data.path` will point the first character
 *        address in `data.cube`.
 * 
 * @warning Texture `token` is only one char, if there is more than one return
 *          error. `token` and `path` texture need to be separated only by space
 *          and only one texture definition by line !
 * 
 * @param data 
 * @param tex 
 * @return int 
 */
int	store_tex(t_parser *data, char *tex)
{
	t_texture	tmp;

	struct_set(&tmp, sizeof(t_texture));
	if (!authzed_cube_tex(*tex))
		return (ret_print(EXIT_FAILURE, ERR_TEX_RESERVED));
	tmp.token = *tex;
	if (get_tex_ptr(&data->tex_list, tmp.token)->token != '\0')
		return (ret_print(EXIT_FAILURE, ERR_TEX_DUP));
	tex++;
	if (*tex != ' ')
		return (ret_print(EXIT_FAILURE, ERR_TEX_FORMAT));
	while (*tex && *tex == ' ')
		tex++;
	if (!*tex)
		return (ret_print(EXIT_FAILURE, ERR_TEX_FORMAT));
	//TODO check flag {v,x}{v,x} for transparency and clip texture
	tmp.type = find_tex_type(tex);
	tmp.path = &*tex;
	if (!ft_memcpy(get_tex_ptr(&data->tex_list, tmp.token),
			&tmp, sizeof(t_texture)))
		return (ret_print(EXIT_FAILURE, ERR_MEMCPY));
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
		else if (store_tex(data, tex))
			return (EXIT_FAILURE);
		while (*tex && *tex != '\n')
			tex++;
	}
	data->cube_map = tex;
	return (EXIT_SUCCESS);
}
