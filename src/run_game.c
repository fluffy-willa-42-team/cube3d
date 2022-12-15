/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:32:07 by awillems          #+#    #+#             */
/*   Updated: 2022/12/15 11:40:48 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "cube3d.h"
#include "ray_caster.h"

#include "init_data.h"

#include <stdio.h>

void	update_win(t_game *game);
int		do_key(int keycode, t_game *game);
int		exit_cube3d(t_game *game);

int	destroy_data(int ret, t_parser *data);

int	init_game(t_param *param)
{
	*param = init_params();
	param->mlx = mlx_init();
	if (!param->mlx)
		return (EXIT_FAILURE);//TODO use ret_print
	param->win = mlx_new_window(param->mlx, WIN_WIDTH, WIN_HEIGHT, "cube3d");
	if (!param->win)
		return (EXIT_FAILURE);
	param->img = mlx_new_image(param->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!param->img)
		return (EXIT_FAILURE);//TODO use ret_print
	return (EXIT_SUCCESS);
}

int	exit_game(t_game *game)
{
	destroy_data(game->return_value, game->parser_data);
	printf("Exit\n");
	exit(game->return_value);
	return (1);
}

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
	mlx_hook(game.param.win, 17, 1L << 17, exit_game, &game);
	mlx_hook(game.param.win, 2, 1L << 0, do_key, &game);
	mlx_loop(game.param.mlx);
	return (EXIT_SUCCESS);
}
