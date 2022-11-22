/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_chunk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:40:19 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/22 14:40:37 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief Get the `t_chunk` from the array with the coordinate `{x, y}`.
 * 
 * @return t_chunk* Return pointer from the array.
 */
t_chunk	*get_chunk(t_parser *data, int x, int y)
{
	const int	index = (y * data->map_size.x) + x;

	return (v_get(&data->map, index));
}
