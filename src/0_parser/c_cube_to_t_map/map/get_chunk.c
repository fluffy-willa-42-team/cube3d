/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_chunk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:28:25 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/29 09:32:19 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

/**
 * @author @Matthew-Dreemurr
 * 
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
 * @author @Matthew-Dreemurr
 * 
 * @brief Get the `t_chunk` from the array with the coordinate `{x, y}`.
 * 
 * @return t_chunk* Return pointer from the array.
 */
t_chunk	*get_chunk(t_game *game, t_coord_i32 pos)
{
	const int	index = (pos.y * game->map.width) + pos.x;

	return (v_get(&game->map.map, index));
}
