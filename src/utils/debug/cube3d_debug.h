/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d_debug.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:54:56 by mahadad           #+#    #+#             */
/*   Updated: 2022/12/28 14:15:57 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_DEBUG_H
# define CUBE3D_DEBUG_H

#  include <stdio.h>

# ifndef CUBE3D_UNITEST_PARSER
#  define CUBE3D_UNITEST_PARSER 0
# endif

int	ret_print(int ret, const char *msg);

# define ERR_BAD_ARGS			"Bad Arguments\n\nExpected: ./exec filename"
# define ERR_FILE_EXT			"Bad file extension !"
# define ERR_OPEN_FILE			"Failed to open file !"
# define ERR_CLOSE_FILE			"Failed to close file !"
# define ERR_RFILE_TYPE			"Bad file data->type ?!"
# define ERR_RDL_FAIL			"v_readline fail !"
# define ERR_VEC_ADD			"v_add fail !"
# define ERR_VEC_ALLOC			"v_alloc fail !"
# define ERR_FREE_MEME			"Free all alloc fail !"
# define ERR_SANI_FILE		"Unauthorized withe space, only ' ' and '\\n'!"
# define ERR_EMPTY_FILE			"Empty map file !"
# define ERR_TEX_FILE			"Unable to open xmp file !"
# define ERR_TEX_PARAM			"Bad texture param !"
# define ERR_TEX_FORMAT			"Bad texture format !"
# define ERR_TEX_TYPE			"Bad texture type !"
# define ERR_TEX_TOKEN_FORMAT	"Bad texture token format !"
# define ERR_SKY_TOKEN_FORMAT	"Bad skybox token format or dont exist !"
# define ERR_TEX_RESERVED		"Bad or reserved texture token used !"
# define ERR_TEX_DUP			"Duplicate texture !"
# define ERR_P_DUP				"Duplicate player !"
# define ERR_NO_MAP_AFTER_TEX	"No map after texture !"
# define ERR_BAD_CUB_CHAR		"Unauthorized character in the map !"
# define ERR_CUB_CONV_FUNC		"f_{floor_level}_{char_type} fail !"
# define ERR_SEQ_BAD			"Bad cube sequence"
# define ERR_CHUNK_W			"Bad chunk line width"
# define ERR_CHUNK_H			"Bad chunk line height"
# define ERR_MEMCPY				"memcpy faild !"
# define ERR_NO_TEX				"Texture in chunk was not define !"
# define ERR_BAD_CHUNK_FLOOR	"Bad chunk floor !"
# define ERR_BAD_CHUNK_TYPE		"Bad chunk type !"
# define ERR_BAD_P_OPT	 		"Bad player direction !"
# define ERR_BAD_P_NO			"No player set !"
# define ERR_BAD_XPM			"XPM file is invalid or corrupted !"
# define ERR_NULL_TEX			"t_texture *NULL !"
# define ERR_COLOR_R			"Bad color channel R"
# define ERR_COLOR_G			"Bad color channel G"
# define ERR_COLOR_B			"Bad color channel B"
# define ERR_COLOR_A			"Bad color channel A"

# define UNAUTHORIZED_SPACE "\t\v\f\r"
# define WHITE_SPACE "\t\v\f\r \n"

# ifdef DEBUG_PRINT

static inline int	ret_print_debug(
	int ret,
	const char *msg,
	const char *file,
	const char *func,
	int line
)
{
	printf ("%s[INFO] ret_print[%d] %s() %s:%d\n", msg, ret, func, file, line);
	return (ret);
}

#  ifdef ret_print
#   undef ret_print
#  endif

#  define ret_print(x, y) ret_print_debug(x, y,__FILE__, __FUNCTION__, __LINE__)
# endif /* DEBUG_PRINT */

#endif /* CUBE3D_DEBUG_H */
