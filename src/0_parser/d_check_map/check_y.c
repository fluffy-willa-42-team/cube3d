/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_y.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mahadad           #+#    #+#             */
/*   Updated: 2022/12/30 11:08:38 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "check_map_utils.h"

#include "cube3d_debug.h"

static t_chunk	*get_next_y(t_parser *data, t_coord_i32 coord)
{
	coord.y++;
	if (coord.y >= data->map_height)
		return (NULL);
	return (get(data, coord));
}

static int	get_wall_y(t_parser *data, t_coord_i32 coord)
{
	t_wall	ret;
	t_chunk	*chunk1;
	t_chunk	*chunk2;

	ret = NW;
	if (coord.y == -1)
		chunk1 = NULL;
	else
		chunk1 = get(data, set_i32(coord.x, coord.y));
	chunk2 = get_next_y(data, set_i32(coord.x, coord.y));
	if (!chunk2 || chunk2->type == WHITE_SPACE_CHUNK)
		ret |= W2EMPTY;
	if (chunk1 && chunk1->south)
		if (!(chunk1->south->type & NO_CLIP))
			ret |= W1;
	if (chunk2 && chunk2->north)
		if (!(chunk2->north->type & NO_CLIP))
			ret |= W2;
	return (ret);
}

static int	check_y_while_while(
	t_parser *data,
	t_coord_i32 pos,
	int *count,
	int *inside
)
{
	t_wall	wall;

	wall = get_wall_y(data, pos);
	if (!*inside && wall & W2EMPTY)
		;
	else if (!*inside && wall & W2)
	{
		*count += 1;
		*inside = 1;
	}
	else if (*inside && wall & W1 && !(wall & W2) && wall & W2EMPTY)
	{
		*count += 1;
		*inside = 0;
	}
	else if (*inside && (wall & W1 || wall & W2))
		*count += 2;
	else if (!*inside && !(wall & W2EMPTY))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	check_y_while(t_parser *data, int x)
{
	int		y;
	int		inside;
	int		count;

	y = -1;
	inside = 0;
	count = 0;
	while (y < data->map_height)
	{
		if (check_y_while_while(data, set_i32(x, y), &count, &inside))
			return (EXIT_FAILURE);
		y++;
	}
	return (count % 2);
}

int	check_y(t_parser *data)
{
	int	x;

	x = 0;
	while (x < data->map_width)
	{
		if (check_y_while(data, x))
			return (EXIT_FAILURE);
		x++;
	}
	return (EXIT_SUCCESS);
}
