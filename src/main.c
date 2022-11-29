/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:56:12 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/29 13:43:43 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d_debug.h"

#include <stdio.h>//TODO REMOVE

#include "parser.h"

#include "cube3d_utils.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

#include "init_data.h"

void	hook_loop(void *param);

int	run(char *file)
{
	t_game		game;
	t_parser	data;

	if (parser(file, &data))
		return (destroy_data(EXIT_FAILURE, &data));
	if (CUBE3D_UNITEST_PARSER)
		return (destroy_data(EXIT_SUCCESS, &data));
	game.map.map = data.map;
	game.map.width = data.map_width;
	game.map.height = data.map_height;
	game.player = init_player(EAST, set_i32(11, 10));
	game.param = init_params();
	game.param.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "MLX42", true);
	if (!game.param.mlx)
		return (EXIT_FAILURE);
	game.param.img = mlx_new_image(game.param.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game.param.img)
		return (EXIT_FAILURE);
	mlx_image_to_window(game.param.mlx, game.param.img, 0, 0);
	mlx_loop_hook(game.param.mlx, &hook_loop, &game);
	mlx_loop(game.param.mlx);
	mlx_delete_image(game.param.mlx, game.param.img);
	mlx_terminate(game.param.mlx);
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
