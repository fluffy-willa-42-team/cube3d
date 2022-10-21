

#include "parser.h"

#include "cube3d_debug.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

/**
 * @brief Return texture index [0->5] and check if there is no duplicate,
 *        if an error occur return `-1`.
 * 
 * @return int Texture index otherwise `-1`
 */
static int	check_texture(char *str, t_parser *data)
{
	const char	*id[DEFAUT_TEX_NB] = {"NO", "SO", "WE", "EA", "F", "C"};
	int			index;
	int			x;

	index = 0;
	while (index < DEFAUT_TEX_NB)
	{
		x = 0;
		while (id[index][x] && str[x] == id[index][x])
			x++;
		if (!id[index][x] && str[x] == ' ')
		{
			if (data->tex[index])
				return (ret_print(-1, ERR_TEX_DUP));
			data->tex[index] = 1;
			return (index);
		}
		index ++;
	}
	return(ret_print(-1, ERR_TEX_FORMAT));
}

/**
 * @Matthew-Dreemurr
 * 
 * @brief Check in `data.tex[]` if all the texture have been find.
 * 
 * @param data Parser struct
 * @return int Return `1` if all texture is there, if not `0`.
 */
static int	is_all_tex(t_parser *data)
{
	int	x;

	x = 0;
	while (x < DEFAUT_TEX_NB)
	{
		if (!data->tex[x])
			return (0);
		x++;
	}
	return (1);
}
#include <stdio.h>//TODO REMOVE DEBUG
/**
 * @Matthew-Dreemurr
 * 
 * @brief Convert all texture name to the `.cube` format.
 * 
 * @param data Parser structure.
 * @return int Return 1 if the `c` is find in the `set` otherwise return 0.
 */
static int	texture_conv(t_parser *data)
{
	int			i;
	char		*tmp;
	int			index;

	i = -1;
	tmp = data->cub.buffer;
	while (tmp[++i])
	{
		if (tmp[i] == '\n')
			continue;
		index = check_texture(&tmp[i], data);
		if (index == -1)
			return(EXIT_FAILURE);
		if (!v_add(&data->cube, STRING, "%c ", '0' + index))
			return (ret_print(EXIT_FAILURE, ERR_VEC_ADD));
		while (tmp[i] != ' ')
			i++;
		while (tmp[i] == ' ')
			i++;
		while (tmp[i] && tmp[i] != '\n')
		{
			if (!v_add(&data->cube, STRING, "%c", tmp[i]))
				return (ret_print(EXIT_FAILURE, ERR_VEC_ADD));
			i++;
		}
		if (!v_add(&data->cube, STRING, "\n"))
			return (ret_print(EXIT_FAILURE, ERR_VEC_ADD));
		if (!tmp[i])
			return (ret_print(EXIT_FAILURE, ERR_NO_MAP_AFTER_TEX));
		if (is_all_tex(data))
			break ;
	}
	// v_print(&data->cube);
	printf("%s\n", (char *)data->cube.buffer);
	return (EXIT_SUCCESS);
}

static int	conversion(t_parser *data)
{
	int	i;

	i = 0;
	while (i < 3)
		data->buff[i++] = v_init(sizeof(char), NULL, NULL);
	data->cube = v_init(sizeof(char), NULL, NULL);
	texture_conv(data);
	return (EXIT_SUCCESS);
}

/**
 * @Matthew-Dreemurr
 * 
 * @brief Convert `.cub` to `.cube` format.
 * 
 * @param data Parser structure
 * @return int Return 1 if the `c` is find in the `set` otherwise return 0.
 */
int	file_conv(t_parser *data)
{
	if (data->type == CUB_FILE)
		if (conversion(data) || !v_delete(&data->cub)/* //TODO change check after the lib update ! */)
			return(EXIT_FAILURE);
	return (EXIT_SUCCESS);
}