/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cube3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:11:32 by awillems          #+#    #+#             */
/*   Updated: 2022/12/13 14:17:47 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "parser.h"
#include <stdlib.h>

int	destroy_data(int ret, t_parser *data);

void	exit_cube3d(t_game *game, int ret)
{
	destroy_data(ret, game->parser_data);
	exit(ret);
}