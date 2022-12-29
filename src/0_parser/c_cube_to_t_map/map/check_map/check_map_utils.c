/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mahadad           #+#    #+#             */
/*   Updated: 2022/12/29 16:35:54 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "check_map_utils.h"

#include "cube3d_debug.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

t_chunk	*get(t_parser *data, t_coord_i32 pos)
{
	const int	index = (pos.y * data->map_width) + pos.x;

	return (v_getr(&data->map, index));
}

/**
 * @brief Check if the given texture can be pass-through by a player.
 * @return `1` if clip, `0` if noclip
 */
int	is_clip(t_texture *tmp)
{
	if (tmp == NULL)
		return (0);
	return (tmp->type != NO_CLIP);
}
