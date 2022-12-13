/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:56:12 by mahadad           #+#    #+#             */
/*   Updated: 2022/12/13 15:13:37 by awillems         ###   ########.fr       */
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
void	update_win(t_game *game);

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

int	run_game(t_parser *data)
{
	t_game		game;

	game.map.map = data->map;
	game.map.width = data->map_width;
	game.map.height = data->map_height;
	game.player = data->player;
	game.param = data->param;
	game.parser_data = data;
	
	// mlx_hook(game.param.win, 17, 1L << 17, NULL, &game);
	update_win(&game);
	mlx_hook(game.param.win, 2, 1L << 0, do_key, &game);
	mlx_loop(game.param.mlx);
	return (EXIT_SUCCESS);
}

int	run(char *file)
{
	t_parser	data;

	struct_set(&data, sizeof(t_parser));
	printf("Start engine...\n");
	if (init_game(&data.param))
		return (destroy_data(EXIT_FAILURE, &data));
	printf("Parser...\n");
	if (parser(file, &data))
		return (destroy_data(EXIT_FAILURE, &data));
	if (CUBE3D_UNITEST_PARSER)
		return (destroy_data(EXIT_SUCCESS, &data));
	printf("Starting game...\n");
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
