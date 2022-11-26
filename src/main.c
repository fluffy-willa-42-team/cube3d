/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 10:49:27 by awillems          #+#    #+#             */
/*   Updated: 2022/11/26 14:58:29 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "MLX42/MLX42.h"

#include "cube3d.h"
#include "init_data.h"

t_texture	*init_image(t_texture *ptr, char *path);
t_texture	*init_color(t_texture *ptr, uint32_t color);
t_texture	*init_texture(t_texture *ptr, int type, char *path, uint32_t color);

void		init_map(t_game *game);

void		hook_loop(void *param);

int	main(void)
{
	t_game	game = {
		init_params(),
		init_player(NORTH, set_i32(2, 3)),
	{{
		"sssss",
		"s  ss",
		"ss  s",
		"s   s",
		"sssss"
	}, NULL, 5, 5},
	{0, NULL, 0},
	{0, NULL, 0},
	{0, NULL, 0},
	{0, NULL, 0},
	{0, NULL, 0},
	{0, NULL, 0},
	{{0, 0}, NULL,			NULL,			NULL,			NULL,			&game.ceiling,	&game.floor},	// chunk0	' '
	{{0, 0}, &game.north,	&game.south,	&game.east,		&game.west,		NULL,			NULL}			// chunk1	's'
	};

	if (	!init_texture(&game.north,		0,	"./texture/mc/grass_side.xpm42",	0x2b66c4ff)
		||	!init_texture(&game.south,		0,	"./texture/mc/stone.xpm42", 		0xc4bf2bff)
		||	!init_texture(&game.east,		0,	"./texture/mc/grass_top.xpm42", 	0xc42e2bff)
		||	!init_texture(&game.west,		0,	"./texture/bars.xpm42", 			0x2bc442ff)
		||	!init_texture(&game.ceiling,	0,	"./texture/mc/grass_top.xpm42", 	0x3d2bc4ff)
		||	!init_texture(&game.floor,		0 ,	"./texture/bars.xpm42", 			0x282836ff)
	)
		return (EXIT_FAILURE);
	game.map.map = malloc(sizeof(t_chunk) * game.map.width * game.map.height);
	if (!game.map.map)
		return (EXIT_FAILURE);
	init_map(&game);
	game.param.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "MLX42", true);
	if (!game.param.mlx)
		return (EXIT_FAILURE);
	game.param.img = mlx_new_image(game.param.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game.param.img)
		return (EXIT_FAILURE);
	mlx_image_to_window(game.param.mlx, game.param.img, 0, 0);
	mlx_loop_hook(game.param.mlx, &hook_loop, &game);
	mlx_loop(game.param.mlx);
	if (game.north.image)		mlx_delete_texture(game.north.image);
	if (game.south.image)		mlx_delete_texture(game.south.image);
	if (game.east.image)		mlx_delete_texture(game.east.image);
	if (game.west.image)		mlx_delete_texture(game.west.image);
	if (game.ceiling.image)		mlx_delete_texture(game.ceiling.image);
	if (game.floor.image)		mlx_delete_texture(game.floor.image);
	free(game.map.map);
	mlx_delete_image(game.param.mlx, game.param.img);
	mlx_terminate(game.param.mlx);
	return (EXIT_SUCCESS);
}
