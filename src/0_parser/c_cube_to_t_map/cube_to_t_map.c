/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_to_t_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:12:15 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/02 19:11:28 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d.h"

#include "cube3d_utils.h"

#include "cube3d_debug.h"

#include "lib_is_check.h" /* ft_isdigit */

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

#include <stdio.h>//TODO REMOVE

/**
 * TODO
 * 
 * Parse tex and store
 *     - [ ] Store in tex_array
 *     - [ ] Check for dup
 *     - [ ] Open tex file
 * Parse map and find HxW
 * 
 * Alloc array map
 * 
 * Init array map
 *     - [ ] Make a function that find chunk with x,y and init a struct in data.
 *           read_chunk(t_data *data.(tmp_)chunk_struct, int x, int y)
 *           t_chunk_struct {TOP,BOTTOM,N,S,E,W,C,F,ENTITY,TAG,...}
 * 
 */

/**
 * @brief Check if the character is a authorized characters for a `.cube` format.
 * 
 * @example
 *          33  '!'   34  '"'   35  '#'   36  '$'   37  '%'
 *          38  '&'   39  '''   40  '('   41  ')'   42  '*'
 *          43  '+'   44  ','   45  '-'   46  '.'   47  '/'
 *          48  '0'   49  '1'   50  '2'   51  '3'   52  '4'
 *          53  '5'   54  '6'   55  '7'   56  '8'   57  '9'
 *          58  ':'   59  ';'   60  '<'   61  '='   62  '>'
 *          63  '?'   64  '@'   65  'A'   66  'B'   67  'C'
 *          68  'D'   69  'E'   70  'F'   71  'G'   72  'H'
 *          73  'I'   74  'J'   75  'K'   76  'L'   77  'M'
 *          78  'N'   79  'O'   80  'P'   81  'Q'   82  'R'
 *          83  'S'   84  'T'   85  'U'   86  'V'   87  'W'
 *          88  'X'   89  'Y'   90  'Z'   91  '['   92  '\'
 *          93  ']'   94  '^'   95  '_'   96  '`'   97  'a'
 *          98  'b'   99  'c'   100 'd'   101 'e'   102 'f'
 *          103 'g'   104 'h'   105 'i'   106 'j'   107 'k'
 *          108 'l'   109 'm'   110 'n'   111 'o'   112 'p'
 *          113 'q'   114 'r'   115 's'   116 't'   117 'u'
 *          118 'v'   119 'w'   120 'x'   121 'y'   122 'z'
 *          123 '{'   124 '|'   125 '}'
 * 
 * @param c character to check
 * @return int Return `1` if the character is in the authorized char, otherwise
 *             return `0`.
 */
int	authzed_cube_char(int c)
{
	return ((c >= '!') && (c <= '}'));
}

/**
 * @brief Check texture type. For a texture path that start with `./` return
 *        `IMAGE`, for a color type, is three set of three numbers separated by
 *        commas `rrr,ggg,bbb` we return `COLOR` otherwise if we dont not found
 *        the type, return `UNDEFINED type.
 * 
 * @example
 *          Color format
 *             [0 ] r
 *             [1 ] r
 *             [2 ] r
 *             [3 ] ,
 *             [4 ] g
 *             [5 ] g
 *             [6 ] g
 *             [7 ] ,
 *             [8 ] b
 *             [9 ] b
 *             [10] b
 * 
 * @param tex 
 * @return int 
 */
int	find_tex_type(char *tex)
{
	int	x;

	if ((*tex && *tex == '.') && (*(tex + 1) && *(tex + 1) == '/'))
		return (IMAGE);
	x = 0;
	while (tex[x])
	{
		if (x == 3 || x == 7)
		{
			if (tex[x] != ',')
				return (UNDEFINED);
		}
		else if (!ft_isdigit(tex[x]))
			return (UNDEFINED);
		if (x == 10)
			return (COLOR);
		x++;
	}
	return (UNDEFINED);
}

/**
 * @brief Will set a tmp `t_texture` struct and push it in the
 *        `t_data `data.tex_list array vector.
 * 
 * @param data 
 * @param tex 
 * @return int 
 */
int	store_tex(t_parser *data, char *tex)
{
	t_texture	tmp;

	if (!authzed_cube_char(*tex))
		return (ret_print(EXIT_FAILURE, ERR_TEX_FORMAT));
	data->tex_list = v_init(sizeof(t_texture), NULL, NULL);
	if (!v_alloc(&data->tex_list, SET, 16))
		return (ret_print(EXIT_FAILURE, ERR_VEC_ALLOC));
	tmp.token = *tex;
	tex++;
	while (*tex && (*tex == ' ' || *tex == '\n'))
		tex++;
	if (!*tex)
		return (ret_print(EXIT_FAILURE, ERR_TEX_FORMAT));
	tmp.type = find_tex_type(tex);
	printf("token [%c]\ntype [%d]\n", tmp.token, tmp.type);
	return (EXIT_SUCCESS);
}



/**
 * @brief Check if a line start with a sequence cube comment or
 *        separator sequence.
 *        Return `SEQ_NO`       if there is no sequence
 *        Return `SEQ_ERR`      if there is a bad sequence
 *        Return `SEQ_COMM`     if is a comment sequence (or `SEQ[0]`)
 *        Return `SEQ_ENDOFTEX` if is a separator sequence (or `SEQ`)
 *
 * @warning The sequence must be used only at the beginning of a new line.
 *          If there is another character before the sequence in the line it is
 *          an undefined behavior.
 * 
 * @param line 
 * @return int Return `SEQ_NO`, `SEQ_ERR`, `SEQ_COMM` or `SEQ_ENDOFTEX`
 */
int	which_escape_seq(char *line)
{
	int			len;

	len = 0;
	if (*line != SEQ[0])
		return (SEQ_NO);
	while(line[len] && line[len] == SEQ[0])
		len++;
	if (len == 1)
		return (SEQ_COMM);
	if (len == SEQ_LEN)
		return (SEQ_ENDOFTEX);
	return (SEQ_ERR);
}


/**
 * @brief Store all texture data in the `data.tex_list` array vector.
 *
 * @warning Store raw data, there is no check if the texture input is valid !
 * 
 * @param data 
 * @param tex 
 * @return int 
 */
int	store_texture(t_parser *data, char *tex)
{
	while (*tex)
	{
		while (*tex && (*tex == ' ' || *tex == '\n'))
			tex++;
		if (*tex == SEQ[0])
		{
			if (which_escape_seq(tex) == SEQ_COMM)
				;
			else if (which_escape_seq(tex) == SEQ_ENDOFTEX)
				break ;
			else if (which_escape_seq(tex) == SEQ_ERR)
				return(ret_print(EXIT_FAILURE, ERR_SEQ_BAD));
		}
		else if (store_tex(data, tex))
			return(EXIT_FAILURE);

		// break;//TODO #6 REMOVE Find a break condition when we find all texture
		//WIP
		/**
		 * - [ ] cub conv add `~~~` to separate the end of the game texture from the map.
		 * 
		 * 
		 */
	}
	//TODO//WIP skip the current line to the next

	return (EXIT_SUCCESS);
}

/**
 * @brief 
 * 
 * @param data 
 * @return int 
 */
int	cube_to_t_map(t_parser *data)
{
	if (store_texture(data, data->cube.buffer))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}