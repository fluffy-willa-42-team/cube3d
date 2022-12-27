/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:58:16 by mahadad           #+#    #+#             */
/*   Updated: 2022/12/15 11:36:17 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d_debug.h"

/* get_chunk() */
#include "cube3d_utils.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

#include <stdio.h>//TODO REMOVE

///* */ static void	print_debug(t_chunk *tmp)
///* */ {
///* */ 	printf(
///* */ 	"[%d][%d] {\n"
///* */ 	"       type          :  {\n"
///* */ 	"                          WHITE_SPACE_CHUNK  [%d]\n"
///* */ 	"                          GOOD_CHUNK         [%d]\n"
///* */ 	"                          BAD_CHUNK          [%d]\n"
///* */ 	"                        },\n"
///* */ 	"       log           : [%c],\n"
///* */ 	"     }\n",
///* */ 	tmp->coord.x,
///* */ 	tmp->coord.y,
///* */ 	WHITE_SPACE_CHUNK == tmp->type,
///* */ 	GOOD_CHUNK == tmp->type,
///* */ 	BAD_CHUNK == tmp->type,
///* */ 	tmp->east ? tmp->east->token : '#'
///* */
///* */ );
///* */ }


/*static int is_clip(t_texture *tex)
{
	return (tex->type & NO_CLIP);
}*/

static t_chunk	*get(t_parser *data, t_coord_i32 pos)
{
	const int	index = (pos.y * data->map_width) + pos.x;
	return (v_getr(&data->map, index));
}


static t_chunk *get_next(t_parser *data, t_coord_i32 coord)
{
	coord.x++;
	if (coord.x >= data->map_width)
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
	W1     = 1000,
	W2     = 0100,
	W      = 1100,
	NW     = 0000,
	WEMPTY = 0010,
	WWHITESPACE = 0001
}			t_wall;

int	get_wall_x(t_parser *data, t_coord_i32 coord)
{
	t_wall ret;
	t_chunk *chunk1;
	t_chunk *chunk2;

	ret = NW;
	if (coord.x == -1)
		chunk1 = NULL;
	else
		chunk1 = get(data, set_i32(coord.x, coord.y));
	chunk2 = get_next(data, set_i32(coord.x, coord.y));

	if (chunk1 && chunk1->type == WHITE_SPACE_CHUNK) {
		ret |= WWHITESPACE;
	}

	if (chunk1 && chunk1->east) {
		if (!(chunk1->east->type & NO_CLIP)){
			ret |= W1;}
	}
	if (chunk2 && chunk2->west) {
		if (!(chunk2->west->type & NO_CLIP))
			ret |= W2;
	}
	else if (chunk2 && !chunk2->north && !chunk2->south && !chunk2->east && !chunk2->west)
		ret |= WEMPTY;
	return (ret);
}

static int check_vertical_while(t_parser *data, int line)
{
	int x;
	int	inside;
	int	count;
	t_wall wall;

	x = -1;
	inside = 0;
	count = 0;
	while (x < data->map_width)
	{
		wall = get_wall_x(data, set_i32(x, line));
		if (wall & WWHITESPACE) {
			x++;
			printf("WP\n");
			continue ;
		}
		if (!inside && wall) {
			inside = 1;
			count += 1;
			printf("in ");
		}
		else if (wall & WEMPTY) {
			inside = 0;
			count += 1;
			printf("out ");
		}
		else if (wall == W2) {
			count += 1 + inside;
			printf("wall ");
		} else if (wall) {
			printf("EOL ");
		}
		printf("[%d](%u)\n", inside, wall);
		x++;
	}
	return (EXIT_SUCCESS);
}

static int	check_vertical(t_parser *data)
{
	int	y;

	y = 0;
	while (y < data->map_height)
	{
		if (check_vertical_while(data, y))
			return (EXIT_FAILURE);
		printf("\n");//TODO REMOVE
		y++;
	}
	return (EXIT_SUCCESS);
}

int	check_map_border(t_parser *data)
{
	if (check_vertical(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS /*EXIT_FAILURE*/);//TODO return success
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
