/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:56:12 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/28 15:58:47 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d_debug.h"

#include <stdio.h>//TODO REMOVE

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

#include "init_data.h"

void	hook_loop(void *param);

int	run(char *file)
{
	t_game	game;

	if (parser(file, &game.map))
		return (EXIT_FAILURE);
	if (CUBE3D_UNITEST_PARSER)
		return (EXIT_SUCCESS);
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
	return (EXIT_SUCCESS);
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
