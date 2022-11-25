/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_to_t_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:12:15 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/25 13:04:19 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d.h"

#include "cube3d_debug.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

#include "cube3d_utils.h"

/**
 * TODO
 * 
 * Parse tex and store
 *     - [x] Store in tex_array
 *     - [ ] Check for dup
 *     - [ ] Open tex file
 * Parse map and find HxW
 * 
 * Alloc array map
 * 
 * Init array map
 *     - [ ] Make a function that find chunk with x,y and init a struct in data.
 *           read_chunk(t_data *data.(tmp_)chunk_struct, int x, int y)
 *           t_chunk_struct {TOP,BOTTOM,N,S,E,W,C,F,ENTITY,TAG,...}
 * 
 */

/**
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
 * @brief 
 * 
 * @param data Parser structure.
 * @return int 
 */
int	cube_to_t_map(t_parser *data)
{
	if (load_texture_config(data, data->cube.buffer) || init_texture(data))
		return (EXIT_FAILURE);
	while (*data->cube_map && (*data->cube_map == '~' || *data->cube_map == '\n'))
		data->cube_map++;
	if (sani_map(data) || store_map(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
