/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:56:12 by mahadad           #+#    #+#             */
/*   Updated: 2022/12/15 11:56:01 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "cube3d.h"
#include "ray_caster.h"

#include "mlx_utils.h"
#include "cube3d_debug.h"

#include <stdio.h>//TODO REMOVE

#include "cube3d_utils.h"

int	init_game(t_param *param);
int	run_game(t_parser *data);

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
