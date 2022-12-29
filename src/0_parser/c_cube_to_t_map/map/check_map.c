/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:58:16 by mahadad           #+#    #+#             */
/*   Updated: 2022/12/29 16:20:53 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d_debug.h"

/* get_chunk() */
#include "cube3d_utils.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

/*static int is_clip(t_texture *tex)
{
	return (tex->type & NO_CLIP);
}*/

static t_chunk	*get(t_parser *data, t_coord_i32 pos)
{
	const int	index = (pos.y * data->map_width) + pos.x;

	return (v_getr(&data->map, index));
}

static t_chunk	*get_next_x(t_parser *data, t_coord_i32 coord)
{
	coord.x++;
	if (coord.x >= data->map_width)
		return (NULL);
	return (get(data, coord));
}

static t_chunk	*get_next_y(t_parser *data, t_coord_i32 coord)
{
	coord.y++;
	if (coord.y >= data->map_height)
		return (NULL);
	return (get(data, coord));
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

typedef enum e_wall
{
	NW		= 0b0000,
	W2EMPTY	= 0b0001,
	W2		= 0b0100,
	W1		= 0b1000,
}			t_wall;

int	get_wall_x(t_parser *data, t_coord_i32 coord)
{
	t_wall	ret;
	t_chunk	*chunk1;
	t_chunk	*chunk2;

	ret = NW;
	if (coord.x == -1)
		chunk1 = NULL;
	else
		chunk1 = get(data, set_i32(coord.x, coord.y));
	chunk2 = get_next_x(data, set_i32(coord.x, coord.y));
	if (!chunk2 || chunk2->type == WHITE_SPACE_CHUNK)
		ret |= W2EMPTY;
	if (chunk1 && chunk1->east)
		if (!(chunk1->east->type & NO_CLIP))
			ret |= W1;
	if (chunk2 && chunk2->west)
		if (!(chunk2->west->type & NO_CLIP))
			ret |= W2;
	return (ret);
}

int	get_wall_y(t_parser *data, t_coord_i32 coord)
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

static int	check_y_while(t_parser *data, int x)
{
	int		y;
	int		inside;
	int		count;
	t_wall	wall;

	y = -1;
	inside = 0;
	count = 0;
	while (y < data->map_height)
	{
		wall = get_wall_y(data, set_i32(x, y));
		if (!inside && wall & W2EMPTY)
			;
		else if (!inside && wall & W2)
		{
			count += 1;
			inside = 1;
		}
		else if (inside && wall & W1 && !(wall & W2) && wall & W2EMPTY)
		{
			count += 1;
			inside = 0;
		}
		else if (inside && (wall & W1 || wall & W2))
			count += 2;
		else if (!inside && !(wall & W2EMPTY))
			return (ret_print(EXIT_FAILURE, "FFFFFFF\n"));
		y++;
	}
	return (count % 2);
}

static int	check_x_while(t_parser *data, int y)
{
	int		x;
	int		inside;
	int		count;
	t_wall	wall;

	x = -1;
	inside = 0;
	count = 0;
	while (x < data->map_width)
	{
		wall = get_wall_x(data, set_i32(x, y));
		if (!inside && wall & W2EMPTY)
			;
		else if (!inside && wall & W2)
		{
			count += 1;
			inside = 1;
		}
		else if (inside && wall & W1 && !(wall & W2) && wall & W2EMPTY)
		{
			count += 1;
			inside = 0;
		}
		else if (inside && (wall & W1 || wall & W2))
			count += 2;
		else if (!inside && !(wall & W2EMPTY))
			return (ret_print(EXIT_FAILURE, "FFFFFFF\n"));
		x++;
	}
	return (count % 2);
}

static int	check_x(t_parser *data)
{
	int	y;

	y = 0;
	while (y < data->map_height)
	{
		if (check_x_while(data, y))
			return (EXIT_FAILURE);
		y++;
	}
	return (EXIT_SUCCESS);
}

static int	check_y(t_parser *data)
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

int	check_map_border(t_parser *data)
{
	if (check_x(data) || check_y(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @brief Return 0 (aka EXIT_SUCCESS) if the player exist otherwise,
 *        return 1 (aka EXIT_FAILURE)
 */
static int	check_player(t_parser *data)
{
	return (!data->player.exist);
}

int	check_map(t_parser *data)
{
	if (check_player(data))
		return (ret_print(EXIT_FAILURE, ERR_BAD_P_NO));
	if (check_map_border(data))
		return (ret_print(EXIT_FAILURE, "//TODO BREAKPOINT TO REMOVE"));
	return (EXIT_SUCCESS);
}
