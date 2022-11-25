/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:56:11 by awillems          #+#    #+#             */
/*   Updated: 2022/11/25 11:25:54 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_chunk *get_chunk(t_game *game, t_coord_i32 pos)
{
	if (!(0 <= pos.x && pos.x < (int) game->map.width
		&& 0 <= pos.y && pos.y < (int) game->map.height))
		return (NULL);
	return (&game->map.map[pos.y * game->map.width + pos.x]);
}

# define NB_CHAR 12

t_chunk *get_chunk_tmp(t_game *game, t_coord_i32 coord)
{
	if (!(0 <= coord.x && coord.x < (int) game->map.width
		&& 0 <= coord.y && coord.y < (int) game->map.height))
		return (NULL);
	
	const char		character[NB_CHAR] = " svhabcdef_u";
	t_chunk	*ptr[NB_CHAR] = {
		&game->chunk0, &game->chunk1, &game->chunk2, &game->chunk3, &game->chunk4, &game->chunk5,
		&game->cont1, &game->cont2, &game->cont3, &game->cont4, 
		&game->chunk6, &game->chunk7
	};
	
	for (int i = 0; i < NB_CHAR; i++)
	{
		if (game->map.array[coord.y][coord.x] == character[i])
		{
			ptr[i]->coord = coord;
			return (ptr[i]);
		}
	}
	return (&game->chunk0);
}

void init_map(t_game *game)
{
	t_chunk *tmp;
	for (uint32_t y = 0; y < game->map.height; y++)
	{
		for (uint32_t x = 0; x < game->map.width; x++)
		{
			tmp = get_chunk_tmp(game, set_i32(x, y));
			game->map.map[y * game->map.width + x] = *tmp;
		}
	}
}
