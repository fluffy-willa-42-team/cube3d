/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_conv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:34:26 by mahadad           #+#    #+#             */
/*   Updated: 2022/12/15 11:36:07 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d.h"

#include "cube3d_debug.h"

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Set a chunk floor for the `' '` case.
 *        Set all floor character to `' '`.
 * 
 * @param data Parser struct
 * @param c `.cub` character
 * @return int Return zero value, if there is a error return non zero value.
 */
int	f_123_space(t_parser *data, char c)
{
	if (push_chunk_part(data, c, c, c))
		return (ret_print(EXIT_FAILURE, ERR_VEC_ADD));
	return (EXIT_SUCCESS);
}
