/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:53:43 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/28 12:25:00 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "vector_lib.h"

# include "cube3d.h"

# define CUB_FILE 1
# define CUBE_FILE 2

# define END_OF_MAP -1

/**
 * @brief Default number of texture
 *        `NO` `SO` `WE` `EA` `F` `C`
 */
# define DEFAULT_CUB_TEX_NB 6

/**
 * @brief Default number of texture
 * 
 */
# define DEFAULT_CUBE_TEX_NB 92

/**
 * @brief Cube separator sequence string
 * @warning The sequence must be used only at the beginning of a new line.
 *          If there is another character before the sequence in the line it is
 *          an undefined behavior.
 */
# define SEQ           "~~~"

/**
 * @brief Cube separator sequence string len
 * @warning The sequence must be used only at the beginning of a new line.
 *          If there is another character before the sequence in the line it is
 *          an undefined behavior.
 */
# define SEQ_LEN       3

/**
 * @brief No cube sequence find
 * @warning The sequence must be used only at the beginning of a new line.
 *          If there is another character before the sequence in the line it is
 *          an undefined behavior.
 */
# define SEQ_NO        0

/**
 * @brief Cube bad separator sequence
 * @warning The sequence must be used only at the beginning of a new line.
 *          If there is another character before the sequence in the line it is
 *          an undefined behavior.
 */
# define SEQ_ERR      -1

/**
 * @brief Cube comment sequence index
 * @warning The sequence must be used only at the beginning of a new line.
 *          If there is another character before the sequence in the line it is
 *          an undefined behavior.
 */
# define SEQ_COMM      1

/**
 * @brief Cube separator sequence index
 * @warning The sequence must be used only at the beginning of a new line.
 *          If there is another character before the sequence in the line it is
 *          an undefined behavior.
 */
# define SEQ_ENDOFTEX  2

/**
 * @param type     (int)     Type of the file `.cub` or `.cube`
 * @param file_fd  (int)     Fd of the file
 * @param path     (char *)  Path file from the main
 * @param cub      (t_vec)   Buffer to write the `.cub`  file
 * @param cube     (t_vec)   Buffer to write the `.cube` file
 * @param cube_map (char *)  Pointer to the beginning of the `.cube` map
 * @param index    (int)     Temporary index
 * @param tmp_width (int)     Temporary width
 * @param tex      (char []) Character array to check duplication `.cub` texture
 * @param tex_list (t_vec)   Structure array with all texture info
 * @param map_size (t_coord_i32) Store the map size, width .x, height .y
 * @param map      (t_vec)   Stucture array with all map info
 */
typedef struct s_parser
{
	int				type;
	int				file_fd;
	char			*path;
	t_vec			cub;
	t_vec			cube;
	char			*cube_map;
	int				index;
	int				tmp_width;
	char			tex[DEFAULT_CUB_TEX_NB];
	t_vec			tex_list;
	uint32_t		map_width;
	uint32_t		map_height;
	t_vec			map;
}				t_parser;

typedef struct s_chunk_token
{
	char			north;
	char			east;
	char			west;
	char			south;
	char			ceiling;
	char			floor;
	char			entity;
	char			tex;
	char			opt;
	t_chunk_type	type;
}				t_chunk_token;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	a;
}				t_color;

typedef int	(*t_conv_fct)(t_parser *data, char c);

int		parser(char *av, t_map *map);

int		open_file(t_parser *data);
int		read_file(t_parser *data);
int		file_sani(t_parser *data);
int		file_conv(t_parser *data);

int		texture_conv(t_parser *data);
int		map_conv(t_parser *data);

int		get_tex(char *str);
int		check_texture(char *str, t_parser *data);

int		push_chunk_part(t_parser *data, int a, int b, int c);

int		f_123_space(t_parser *data, char c);

int		f_1_zero(t_parser *data, char c);
int		f_2_zero(t_parser *data, char c);
int		f_3_zero(t_parser *data, char c);

int		f_1_one(t_parser *data, char c);
int		f_2_one(t_parser *data, char c);
int		f_3_one(t_parser *data, char c);

int		f_1_p(t_parser *data, char c);
int		f_2_p(t_parser *data, char c);
int		f_3_p(t_parser *data, char c);

int		cube_to_t_map(t_parser *data);

int		set_texture_path(t_parser *data, char *tex, t_texture *tmp);
int		set_texture_param(t_parser *data, char *tex, t_texture *tmp);

int		set_color_texture(t_texture *tex);
int		set_current_tex_config(t_parser *data, char *tex);

int		load_texture_config(t_parser *data, char *tex);
int		init_texture(t_parser *data);

int		store_map(t_parser *data);

int		check_chunk_type(t_chunk_token *tokens);
int		get_next_chunk(t_parser *data, t_chunk *chunk);
int		set_map_size(t_parser *data);
int		get_line_width(t_parser *data);

char	mapchar(t_parser *data);
char	*mapptr(t_parser *data);

#endif /* PARSER_H */
