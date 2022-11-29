/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zero_conv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:03:27 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/29 09:24:16 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d.h"

#include "cube3d_debug.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Set the first chunk floor for the `'0'` case.
 *        TOP is set with the ceiling texture index (or `get_tex("C")`)
 *        and {NORTH, ENTITY} with `'.'` (or E_EMPTY).
 *
 * @details floor 1 : TOP | NORTH | ENTITY
 *
 * @param data Parser struct
 * @param c `.cub` character
 * @return int Return zero value, if there is a error return non zero value.
 */
int	f_1_zero(t_parser *data, char c)
{
	(void)c;
	if (push_chunk_part(data, get_tex("C"), E_EMPTY, E_EMPTY))
		return (ret_print(EXIT_FAILURE, ERR_VEC_ADD));
	return (EXIT_SUCCESS);
}

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Set the second chunk floor for the `'0'` case.
 *        {WEST, EAST, TEX} is set to '.' (or E_EMPTY).
 *
 * @details floor 2 : WEST | EAST | TEX
 *
 * @param data Parser struct
 * @param c `.cub` character
 * @return int Return zero value, if there is a error return non zero value.
 */
int	f_2_zero(t_parser *data, char c)
{
	(void)c;
	if (push_chunk_part(data, E_EMPTY, E_EMPTY, E_EMPTY))
		return (ret_print(EXIT_FAILURE, ERR_VEC_ADD));
	return (EXIT_SUCCESS);
}

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Set the last chunk floor for the `'0'` case.
 *        BOTTOM is set with the floor texture index (or `get_tex("F")`)
 *        and {SOUTH, OPT} with `'.'` (or E_EMPTY).
 *
 * @details floor 3 : BOTTOM | SOUTH | OPT
 *
 * @param data Parser struct
 * @param c `.cub` character
 * @return int Return zero value, if there is a error return non zero value.
 */
int	f_3_zero(t_parser *data, char c)
{
	(void)c;
	if (push_chunk_part(data, get_tex("F"), E_EMPTY, E_EMPTY))
		return (ret_print(EXIT_FAILURE, ERR_VEC_ADD));
	return (EXIT_SUCCESS);
}
