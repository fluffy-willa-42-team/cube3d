/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:56:12 by mahadad           #+#    #+#             */
/*   Updated: 2022/12/06 14:29:30 by mahadad          ###   ########.fr       */
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

int	run_game(t_parser *data)
{
	t_game		game;

	game.map.map = data->map;
	game.map.width = data->map_width;
	game.map.height = data->map_height;
	game.player = data->player;
	game.param = init_params();
	game.param.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "MLX42", true);
	if (!game.param.mlx)
		return (EXIT_FAILURE);//TODO use ret_print
	game.param.img = mlx_new_image(game.param.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game.param.img)
		return (EXIT_FAILURE);//TODO use ret_print
	mlx_image_to_window(game.param.mlx, game.param.img, 0, 0);
	mlx_loop_hook(game.param.mlx, &hook_loop, &game);
	mlx_loop(game.param.mlx);
	mlx_delete_image(game.param.mlx, game.param.img);
	mlx_terminate(game.param.mlx);
	return (EXIT_SUCCESS);
}

int	run(char *file)
{
	t_parser	data;

	struct_set(&data, sizeof(t_parser));
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
