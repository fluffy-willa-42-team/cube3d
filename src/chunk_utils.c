/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:56:11 by awillems          #+#    #+#             */
/*   Updated: 2022/11/18 11:59:38 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <stdio.h>


int is_equal(double a, double b);

t_chunk *get_chunk(t_game *game, t_coord_i32 coord)
{
	if (!(0 <= coord.x && coord.x < (int) game->map.width
		&& 0 <= coord.y && coord.y < (int) game->map.height))
		return (NULL);
	if (game->map.array[coord.y][coord.x] == 1)
	{
		game->chunk1.coord = coord;
		return (&game->chunk1);
	}
	if (game->map.array[coord.y][coord.x] == 2)
	{
		game->chunk2.coord = coord;
		return (&game->chunk2);
	}
	if (game->map.array[coord.y][coord.x] == 3)
	{
		game->chunk3.coord = coord;
		return (&game->chunk3);
	}
	if (game->map.array[coord.y][coord.x] == 4)
	{
		game->chunk4.coord = coord;
		return (&game->chunk4);
	}
	if (game->map.array[coord.y][coord.x] == 6)
	{
		game->cont4.coord = coord;
		return (&game->cont4);
	}
	if (game->map.array[coord.y][coord.x] == 7)
	{
		game->cont1.coord = coord;
		return (&game->cont1);
	}
	if (game->map.array[coord.y][coord.x] == 8)
	{
		game->cont2.coord = coord;
		return (&game->cont2);
	}
	if (game->map.array[coord.y][coord.x] == 9)
	{
		game->cont3.coord = coord;
		return (&game->cont3);
	}
	game->chunk0.coord = coord;
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
