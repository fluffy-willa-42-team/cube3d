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

int	check_map(t_parser *data)
{
	if (!data->player.exist)
		return (ret_print(EXIT_FAILURE, ERR_BAD_CHUNK_FLOOR));
	return (EXIT_SUCCESS);
}