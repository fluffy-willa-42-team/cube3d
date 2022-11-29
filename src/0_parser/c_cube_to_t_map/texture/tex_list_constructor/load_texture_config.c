/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:09:25 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/21 17:38:56 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d.h"

#include "cube3d_utils.h" /* struct_set */

#include "cube3d_debug.h"

#include "lib_is_check.h" /* ft_isdigit */

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

/**
 * @author @Matthew-Dreemurr
 * 
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
static int	which_escape_seq(char *line)
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
 * @author @Matthew-Dreemurr
 * 
 * @brief Store all texture data in the `data.tex_list` array vector. Will read
 *        line by line and set the rigth texture slot in the array.
 *        Finally set `data.cube_map` to the cube separator sequence line.
 *
 * @warning Store raw data, there is no check if the texture input is valid !
 * 
 * @note
 * [token] [[allow_clip],[transparency],[token_skybox]] [texture_path, color]]
 * @param data 
 * @param tex 
 * @return int 
 */
int	load_texture_config(t_parser *data, char *tex)
{
	data->tex_list = v_init(sizeof(t_texture), NULL, NULL);
	if (!v_alloc(&data->tex_list, SET, DEFAULT_CUBE_TEX_NB))
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
		else if (set_current_tex_config(data, tex))
			return (EXIT_FAILURE);
		while (*tex && *tex != '\n')
			tex++;
	}
	data->cube_map = tex;
	return (EXIT_SUCCESS);
}
