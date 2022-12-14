/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:58:16 by mahadad           #+#    #+#             */
/*   Updated: 2022/12/12 16:06:36 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d_debug.h"

/* get_chunk() */
#include "cube3d_utils.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

#include <stdio.h>//TODO REMOVE

/* */ static void	print_debug(t_chunk *tmp)
/* */ {
/* */ 	printf(
/* */ 	"[%d][%d] {\n"
/* */ 	"       type          :  {\n"
/* */ 	"                          WHITE_SPACE_CHUNK  [%d]\n"
/* */ 	"                          GOOD_CHUNK         [%d]\n"
/* */ 	"                          BAD_CHUNK          [%d]\n"
/* */ 	"                        },\n"
/* */ 	"       log           : [%c],\n"
/* */ 	"     }\n",
/* */ 	tmp->coord.x,
/* */ 	tmp->coord.y,
/* */ 	WHITE_SPACE_CHUNK == tmp->type,
/* */ 	GOOD_CHUNK == tmp->type,
/* */ 	BAD_CHUNK == tmp->type,
/* */ 	tmp->east ? tmp->east->token : '#'
/* */
/* */ );
/* */ }


/*static int is_clip(t_texture *tex)
{
	return (tex->type & ALLOW_CLIP);
}*/

int		wip = 0;
int		outside = 1;

static t_chunk	*get(t_parser *data, t_coord_i32 pos)
{
	const int	index = (pos.y * data->map_width) + pos.x;

	return (v_get(&data->map, index));
}

static int check_vertical_while(t_parser *data, int line)
{
	int x;

	x = 0;
	while (x < data->map_width)
	{
		if (get(data, set_i32(x, line))) print_debug(get(data, set_i32(x, line))); else printf("Nop\n");
		if (outside) {
			printf("OUT\n");//TODO REMOVE
		}
		if (!outside) {
			printf("IN\n");//TODO REMOVE
		}
		if ((x + 1) < data->map_width) {
			if (get(data, set_i32((x + 1), line))->type == WHITE_SPACE_CHUNK)
				outside = 1;
			else
				outside = 0;
		}
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
		y++;
	}
	return (EXIT_SUCCESS);
}

int	check_map_border(t_parser *data)
{
	if (check_vertical(data))
		return (EXIT_FAILURE);
	return (/*EXIT_SUCCESS*/ EXIT_FAILURE);//TODO return success
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
