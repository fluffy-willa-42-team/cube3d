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
	return (tex->type & ALLOW_CLIP);
}*/

static t_chunk	*get(t_parser *data, t_coord_i32 pos)
{
	const int	index = (pos.y * data->map_width) + pos.x;

	return (v_getr(&data->map, index));
}


//static t_chunk *get_next(t_parser *data, int x, int line)
//{
//	x++;
//	if (x > data->map_width)
//		return (NULL);
//	return (get(data, set_i32(x, line)));
//}


int		wip = 0;
int		inside = 0;
static int check_vertical_while(t_parser *data, int line)
{
	int x;
	int	inside;
	int	count;
	t_chunk current;

//	current = (t_chunk){ WHITE_SPACE_CHUNK,
//						 set_i32(-1, 0),
//						 NULL,
//						 NULL,
//						 NULL,
//						 NULL,
//						 NULL,
//						 NULL,
//	};
	x = 0;
	inside = 0;
	count = 0;
	while (x < data->map_width)
	{
		current = *get(data, set_i32((float)x, (float)line));
//		if (get_next(data, x, line))
//			current = *get_next(data, x, line);
		if (current.type == WHITE_SPACE_CHUNK) {
			if (inside) {
				count -= 1;
				printf("|");
				} else {
				printf("0");
			}//TODO REMOVE
			inside = 0;
		}
		if (current.type == GOOD_CHUNK) {
			if (!inside) {
				printf("1");//TODO REMOVE
				count += 1;
			} else {
				count += 2;
				printf("2");
			}//TODO REMOVE
			inside = 1;
		}
		if (current.type == BAD_CHUNK) {
			printf("!");//TODO REMOVE
		}
//		print_debug(&current);
		x++;
	}
	if (inside) {
		count -= 1;
		printf("|");
	}
	printf(" [%d]\n", count);//TODO REMOVE
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
