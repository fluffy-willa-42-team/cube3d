/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_conv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:04:49 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/16 14:30:34 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d.h"

#include "cube3d_debug.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

/**
 * @Matthew-Dreemurr
 * 
 * @brief Set the first chunk floor for the `{'N','S','E','W'}` case aka the
 *        player.
 *        TOP is set with the ceiling texture index (or `get_tex("C")`).
 *        NORTH is set to '.' (or E_EMPTY).
 *        And ENTITY is set to `'P'` (or E_PLAYER)
 *
 * @details floor 1 : TOP | NORTH | ENTITY
 *
 *
 * @param data Parser struct
 * @param c `.cub` character
 * @return int Return zero value, if there is a error return non zero value.
 */
int	f_1_p(t_parser *data, char c)
{
	(void)c;
	if (push_chunk_part(data, get_tex("C"), E_EMPTY, E_PLAYER))
		return (ret_print(EXIT_FAILURE, ERR_VEC_ADD));
	return (EXIT_SUCCESS);
}

/**
 * @Matthew-Dreemurr
 * 
 * @brief Set the second chunk floor for the `{'N','S','E','W'}` case aka the
 *        player.
 *        {WEST, EAST, TEX} is set to '.' (or E_EMPTY).
 *
 * @details floor 2 : WEST | EAST | TEX
 *
 * @param data Parser struct
 * @param c `.cub` character
 * @return int Return zero value, if there is a error return non zero value.
 */
int	f_2_p(t_parser *data, char c)
{
	return (f_2_zero(data, c));
}

/**
 * @Matthew-Dreemurr
 * 
 * @brief Set the last chunk floor for the `{'N','S','E','W'}` case aka the
 *        player.
 *        BOTTOM is set with the floor texture index (or `get_tex("F")`).
 *        SOUTH is set to '.' (or E_EMPTY).
 *        And OPT is set to `{'N','S','E','W'}`
 *       (or OPT_P_NORTH, OPT_P_SOUTH, OPT_P_EAST, OPT_P_WEST).
 *
 * @details floor 3 : BOTTOM | SOUTH | OPT
 *
 * @param data Parser struct
 * @param c `.cub` character
 * @return int Return zero value, if there is a error return non zero value.
 */
int	f_3_p(t_parser *data, char c)
{
	(void)c;
	if (push_chunk_part(data, get_tex("F"), E_EMPTY, c))
		return (ret_print(EXIT_FAILURE, ERR_VEC_ADD));
	return (EXIT_SUCCESS);
}