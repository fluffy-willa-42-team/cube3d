/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:56:12 by mahadad           #+#    #+#             */
/*   Updated: 2022/12/12 16:52:05 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "cube3d.h"
#include "ray_caster.h"

#include "mlx_utils.h"
#include "cube3d_debug.h"

#include <stdio.h>//TODO REMOVE

#include "parser.h"

#include "cube3d_utils.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

#include "init_data.h"


// void	hook_loop(void *param);
int		do_key(int keycode, t_game *game);

int	init_game(t_param *param)
{
	*param = init_params();
	param->mlx = mlx_init();
	if (!param->mlx)
		return (EXIT_FAILURE);//TODO use ret_print
	param->win = mlx_new_window(param->mlx, WIN_WIDTH, WIN_HEIGHT, "cube3d");
	if (!param->win)
	{
		free(param->mlx);
		return (EXIT_FAILURE);
	}
	param->img = mlx_new_image(param->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!param->img)
	{
		mlx_destroy_window(param->mlx, param->win);
		free(param->mlx);
		return (EXIT_FAILURE);//TODO use ret_print
	}
	return (EXIT_SUCCESS);
}

int	run_game(t_parser *data)
{
	t_game		game;

	game.map.map = data->map;
	game.map.width = data->map_width;
	game.map.height = data->map_height;
	game.player = data->player;
	game.param = data->param;
	mlx_put_image_to_window(game.param.mlx, game.param.win, game.param.img, 0, 0);
	// mlx_loop_hook(game.param.mlx, &hook_loop, &game);
	// mlx_hook(game->param.win, 17, 1L << 17, NULL, &data);
	mlx_hook(&game.param.win, 2, 1L << 0, do_key, &data);
	draw_rectangle(&game, set_f64(0, 0), set_i32(WIN_WIDTH, WIN_HEIGHT), 0x000000ff);
	ray_caster(&game);
	draw_minimap(&game);
	mlx_loop(game.param.mlx);
	mlx_destroy_image(game.param.mlx, game.param.img);
	mlx_destroy_window(game.param.mlx, game.param.win);
	free(game.param.mlx);
	return (EXIT_SUCCESS);
}

int	run(char *file)
{
	t_parser	data;

	if (!init_game(&data.param))
		return (destroy_data(EXIT_FAILURE, &data));
	if (parser(file, &data))
		return (destroy_data(EXIT_FAILURE, &data));
	if (CUBE3D_UNITEST_PARSER)
		return (destroy_data(EXIT_SUCCESS, &data));
	if (run_game(&data))
		return (destroy_data(EXIT_FAILURE, &data));
	return (destroy_data(EXIT_SUCCESS, &data));
}

int	main(int argc, char *argv[])
{
	(void) argc;
	(void) argv;
	if (argc != 2)
	{
		printf("[%d]\n", argc);
		return (ret_print(1, "TODO\n"));
	}
	printf("Arg [%s]\n", argv[1]);
	if (run(argv[1]))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
