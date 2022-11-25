/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_chunk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:44:17 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/22 14:51:16 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* authzed_chunk_char() */
#include "cube3d_utils.h"


/**
 * @brief Check if all the token of the current is only white space `' '`.
 * 
 * @warning A chunk with white space `' '` can not have data !
 */
static int	is_all_white_space_tokens(t_chunk_token *tokens)
{
	return (tokens->ceiling == ' '
		&& tokens->east == ' '
		&& tokens->entity == ' '
		&& tokens->floor == ' '
		&& tokens->floor == ' '
		&& tokens->north == ' '
		&& tokens->opt == ' '
		&& tokens->south == ' '
		&& tokens->tex == ' '
		&& tokens->west == ' ');
}

/**
 * @brief Check if all the token of the current chunk is valid.
 * 
 * @warning A chunk with data can not have white space token `' '` !
 */
static int	is_all_valid_tokens(t_chunk_token *tokens)
{
	return (authzed_chunk_char(tokens->ceiling)
		&& authzed_chunk_char(tokens->east)
		&& authzed_chunk_char(tokens->floor)
		&& authzed_chunk_char(tokens->floor)
		&& authzed_chunk_char(tokens->north)
		&& authzed_chunk_char(tokens->south)
		&& authzed_chunk_char(tokens->entity)
		&& authzed_chunk_char(tokens->tex)
		&& authzed_chunk_char(tokens->opt)
		&& authzed_chunk_char(tokens->west));
}

/**
 * @brief Check if is a white space chunk or if there is data.
 * 
 * @warning A chunk with white space `' '` can not have data !
 *          A chunk with data can not have white space token `' '` !
 */
int	check_chunk_type(t_chunk_token *tokens)
{
	if (is_all_white_space_tokens(tokens))
	{
		tokens->type = WHITE_SPACE_CHUNK;
		return (WHITE_SPACE_CHUNK);
	}
	if (is_all_valid_tokens(tokens))
	{
		tokens->type = GOOD_CHUNK;
		return (GOOD_CHUNK);
	}
	tokens->type = BAD_CHUNK;
	return (BAD_CHUNK);
}
