/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:58:16 by mahadad           #+#    #+#             */
/*   Updated: 2022/12/30 10:35:54 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "check_map_utils.h"

#include "cube3d_debug.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

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
		return (ret_print(EXIT_FAILURE, ERR_MAP_NOT_CLOSED));
	return (EXIT_SUCCESS);
}
