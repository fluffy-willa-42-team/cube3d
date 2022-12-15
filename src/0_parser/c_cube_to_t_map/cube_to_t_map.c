/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_to_t_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:12:15 by mahadad           #+#    #+#             */
/*   Updated: 2022/12/15 11:36:14 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d.h"

#include "cube3d_debug.h"

#include "cube3d_utils.h"

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Check if all character used in the map is authorize and if there
 *        `token` texture exist in the texture liste (aka `data.tex_list).
 * 
 * @note Check of all character if there in the autorized `.cube` char.
 *       We skip all `' '` and `'\n'` character.
 * 
 * @return int If all the character in the map is good return `0` otherwise `1`
 */
int	sani_map(t_parser *data)
{
	int	tmp;

	tmp = 0;
	while (data->cube_map[tmp])
	{
		if (data->cube_map[tmp] != ' ' && data->cube_map[tmp] != '\n')
			if (!authzed_chunk_char(data->cube_map[tmp]))
				return (ret_print(EXIT_FAILURE, ERR_BAD_CUB_CHAR));
		tmp++;
	}
	return (EXIT_SUCCESS);
}

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Parse all `.cube` format. First store all texture and init. And store
 *        all chunk and they textur ptr.
 * 
 * @note After the texture part we skip all whitespace to the
 *       separator sequence `"~~~"`.
 * 
 * @param data Parser structure.
 * @return int 
 */
int	cube_to_t_map(t_parser *data)
{
	if (load_texture_config(data, data->cube.buffer) || init_texture(data))
		return (EXIT_FAILURE);
	while (*data->cube_map
		&& (*data->cube_map == '~' || *data->cube_map == '\n'))
		data->cube_map++;
	if (sani_map(data) || store_map(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
