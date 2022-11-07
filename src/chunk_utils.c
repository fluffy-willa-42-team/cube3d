/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:56:11 by awillems          #+#    #+#             */
/*   Updated: 2022/11/07 11:55:19 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <stdio.h>


int is_equal(double a, double b);

t_chunk get_chunk(t_game *game, t_coord_i32 coord)
{
	t_texture *ptr;

	ptr = &game->temp;
	
	if (!(0 <= coord.x && coord.x < (int) game->map.width
		&& 0 <= coord.y && coord.y < (int) game->map.height))
		return ((t_chunk) {-1, coord, NULL, NULL, NULL, NULL, NULL, NULL});
	if (game->map.array[coord.y][coord.x] == 1)
		return ((t_chunk) {1, coord, ptr, ptr, ptr, ptr, ptr, ptr});
	if (game->map.array[coord.y][coord.x] == 2)
		return ((t_chunk) {1, coord, NULL, NULL, ptr, ptr, ptr, ptr});
	return ((t_chunk) {0, coord, NULL, NULL, NULL, NULL, NULL, NULL});
}

t_texture *get_wall_texture(t_chunk *chunk, t_coord_f64 inter)
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
