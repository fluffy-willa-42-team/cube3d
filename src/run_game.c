/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:32:07 by awillems          #+#    #+#             */
/*   Updated: 2022/12/15 11:33:40 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "cube3d.h"
#include "ray_caster.h"

void	update_win(t_game *game);
int		do_key(int keycode, t_game *game);
int		exit_cube3d(t_game *game);

int	run_game(t_parser *data)
{
	t_game		game;

	game.map.map = data->map;
	game.map.width = data->map_width;
	game.map.height = data->map_height;
	game.player = data->player;
	game.param = data->param;
	game.parser_data = data;
	game.return_value = 0;
	
	update_win(&game);
	mlx_hook(game.param.win, 17, 1L << 17, exit_cube3d, &game);
	mlx_hook(game.param.win, 2, 1L << 0, do_key, &game);
	mlx_loop(game.param.mlx);
	return (EXIT_SUCCESS);
}