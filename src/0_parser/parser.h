/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:53:43 by mahadad           #+#    #+#             */
/*   Updated: 2022/10/26 15:03:16 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "vector_lib.h"

# define CUB_FILE 1
# define CUBE_FILE 2

# define DEFAUT_TEX_NB 6

typedef int	(*t_conv_fct)();

/**
 * @param type     (int)    Type of the file `.cub` or `.cube`
 * @param file_fd  (int)    Fd of the file
 * @param *path    (char)   Path file from the main
 * @param cub     (t_vec)   Buffer to write the `.cub`  file
 * @param cube    (t_vec)   Buffer to write the `.cube` file
 */
typedef struct s_parser
{
	int				type;
	int				file_fd;
	char			*path;
	t_vec			cub;
	t_vec			cube;
	int				index;
	char			tex[DEFAUT_TEX_NB];
}				t_parser;

int	parser(char *av);
int	open_file(t_parser *data);
int	read_file(t_parser *data);
int	file_sani(t_parser *data);
int	file_conv(t_parser *data);

int	texture_conv(t_parser *data);
int	map_conv(t_parser *data);

int	get_tex(char *str);
int	check_texture(char *str, t_parser *data);

#endif /* PARSER_H */
