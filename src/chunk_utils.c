/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:56:11 by awillems          #+#    #+#             */
/*   Updated: 2022/11/18 14:50:44 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <stdio.h>


int is_equal(double a, double b);

# define NB_CHAR 12

t_chunk *get_chunk(t_game *game, t_coord_i32 coord)
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

t_texture *get_wall_texture(const t_chunk *chunk, t_coord_f64 inter)
{
	if (!chunk)
		return (NULL);
	if (is_equal(chunk->coord.x, inter.x))
		return (chunk->east);
	if (is_equal(chunk->coord.x + 1, inter.x))
		return (chunk->west);
	if (is_equal(chunk->coord.y, inter.y))
		return (chunk->south);
	if (is_equal(chunk->coord.y + 1, inter.y))
		return (chunk->north);
	return (NULL);
}
