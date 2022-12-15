/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cube3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:11:32 by awillems          #+#    #+#             */
/*   Updated: 2022/12/15 11:34:37 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "parser.h"
#include <stdio.h>

int	destroy_data(int ret, t_parser *data);

int	exit_cube3d(t_game *game)
{
	destroy_data(game->return_value, game->parser_data);
	printf("Exit\n");
	exit(game->return_value);
	return (1);
}