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

int	check_map_border(t_parser *data)
{
	t_coord_i32	coord;
	t_chunk		*tmp;

	coord = (t_coord_i32){0, 0};
	while ((uint32_t)coord.y < data->map_height)
	{
		coord.x = 0;
		while ((uint32_t)coord.x < data->map_width)
		{
			tmp = get_chunk_pars(data, coord);
			if (tmp)
				print_debug(tmp);
			else
				printf("Nop\n");
			coord.x++;
		}
		coord.y++;
	}
	return (EXIT_FAILURE);
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
		return (ret_print(EXIT_FAILURE, ERR_BAD_CHUNK_FLOOR));
    if (check_map_border(data))
          return (ret_print(EXIT_FAILURE, "//TODO ERRMSG"));
	return (EXIT_SUCCESS);
}
