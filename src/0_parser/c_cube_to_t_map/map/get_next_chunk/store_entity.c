/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_entity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:54:58 by mahadad           #+#    #+#             */
/*   Updated: 2022/12/28 15:30:20 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d_debug.h"

#include "init_data.h"

/**
 * @brief Check if the player position is good
 * 
 * @note
 *       NORTH = OPT_P_NORTH (`'N'`)
 *       SOUTH = OPT_P_SOUTH (`'S'`)
 *       EAST  = OPT_P_EAST  (`'E'`)
 *       WEST  = OPT_P_WEST  (`'W'`)
 * 
 * @param opt 
 * @return t_direction 
 */
static t_direction	check_player_opt(int opt)
{
	if (opt == OPT_P_NORTH)
		return (NORTH);
	if (opt == OPT_P_SOUTH)
		return (SOUTH);
	if (opt == OPT_P_EAST)
		return (EAST);
	if (opt == OPT_P_WEST)
		return (WEST);
	return (ret_print(BAD_DIRECTION, ERR_BAD_P_OPT));
}

static int	set_player(t_parser *data, t_chunk *chunk, t_chunk_token *t)
{
	t_direction	dir;

	if (data->player.exist == 1)
		return (ret_print(EXIT_FAILURE, ERR_P_DUP));
	dir = check_player_opt(t->opt);
	if (dir == BAD_DIRECTION)
		return (EXIT_FAILURE);
	data->player = init_player(dir, set_i32(chunk->coord.x, chunk->coord.y));
	data->player.exist = 1;
	return (EXIT_SUCCESS);
}

//TODO #12 Make the entity data structure for the player
int	store_entity(t_parser *data, t_chunk *chunk, t_chunk_token *tokens)
{
	if (tokens->entity == E_PLAYER)
		if (set_player(data, chunk, tokens))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
