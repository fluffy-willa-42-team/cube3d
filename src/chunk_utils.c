/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:56:11 by awillems          #+#    #+#             */
/*   Updated: 2022/11/07 11:04:13 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int is_equal(double a, double b);

t_chunk get_chunk(t_game *game, uint32_t x, uint32_t y)
{
	t_texture *ptr;

	ptr = &game->temp;
	
	if (!(x < game->map.width && y < game->map.height))
		return ((t_chunk) {0, {x, y}, NULL, NULL, NULL, NULL, NULL, NULL});
	if (game->map.array[y][x] == 1)
		return ((t_chunk) {1, {x, y}, ptr, ptr, ptr, ptr, ptr, ptr});
	return ((t_chunk) {0, {x, y}, NULL, NULL, NULL, NULL, NULL, NULL});
}

t_texture *get_wall_texture(t_chunk *chunk, t_coord_f64 inter)
{
	if (is_equal(chunk->coord.x, inter.x))
		return (chunk->north);
	if (is_equal(chunk->coord.x, inter.x + 1))
		return (chunk->south);
	if (is_equal(chunk->coord.y, inter.y))
		return (chunk->west);
	if (is_equal(chunk->coord.y, inter.y + 1))
		return (chunk->east);
	return (NULL);
}
