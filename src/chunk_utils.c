/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:56:11 by awillems          #+#    #+#             */
/*   Updated: 2022/11/22 12:41:32 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <stdio.h>


int is_equal(double a, double b);

# define NB_CHAR 12

t_chunk *get_chunk(t_game *game, t_coord_i32 pos)
{
	return (&game->map.map[pos.y * game->map.width + pos.x]);
}

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

t_wall_inter	get_wall(t_game *game, t_coord_f64 inter)
{
	t_wall_inter wall_inter;
	
	wall_inter.text1 = NULL;
	wall_inter.text2 = NULL;
	wall_inter.chunk2 = NULL;
	wall_inter.chunk1 = get_chunk(game, set_i32(inter.x, inter.y));
	if (is_equal(inter.y - (int) inter.y, 0)) // NORTH-SOUTH
	{
		wall_inter.chunk2 = get_chunk(game, set_i32((int) inter.x, ((int) inter.y) - 1));
		if (wall_inter.chunk1)
			wall_inter.text1 = wall_inter.chunk1->north;
		if (wall_inter.chunk2)
			wall_inter.text2 = wall_inter.chunk2->south;
	}
	else if (is_equal(inter.x - (int) inter.x, 0)) // EAST-WEST
	{
		wall_inter.chunk2 = get_chunk(game, set_i32(((int) inter.x) - 1, (int) inter.y));
		if (wall_inter.chunk1)
			wall_inter.text1 = wall_inter.chunk1->west;
		if (wall_inter.chunk2)
			wall_inter.text2 = wall_inter.chunk2->east;
	}
	printf("%p %p %p %p\n", wall_inter.chunk1, wall_inter.chunk2, wall_inter.text1, wall_inter.text2);
	return (wall_inter);
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
