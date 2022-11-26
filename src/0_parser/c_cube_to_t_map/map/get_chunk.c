/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_chunk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:28:25 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/26 12:31:03 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

/**
 * @brief Get the `t_chunk` from the array with the coordinate `{x, y}`.
 * 
 * @return t_chunk* Return pointer from the array.
 */
t_chunk	*get_chunk_pars(t_parser *data, t_coord_i32 pos)
{
	const int	index = (pos.y * data->map_width) + pos.x;

	return (v_get(&data->map, index));
}

/**
 * @brief Get the `t_chunk` from the array with the coordinate `{x, y}`.
 * 
 * @return t_chunk* Return pointer from the array.
 */
t_chunk	*get_chunk(t_game *game, t_coord_i32 pos)
{
	const int	index = (pos.y * game->map.width) + pos.x;

	t_chunk	*chunk = v_get(&game->map.map, index);
	printf("(%d %d) => (%d %d) [%d, %lu] [%u %u]\n", pos.x, pos.y, chunk->coord.x, chunk->coord.y, index, game->map.map.len, game->map.width, game->map.height);
	return (chunk);
}
