/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:56:12 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/02 11:26:38 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d_debug.h"

#include <stdio.h>//TODO REMOVE

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

int	run(char *file)
{
	if (parser(file))
		return (EXIT_FAILURE);
	if (CUBE3D_UNITEST_PARSER)
		return (EXIT_SUCCESS);
	return(EXIT_SUCCESS);
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
