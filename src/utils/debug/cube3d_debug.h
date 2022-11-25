/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d_debug.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:54:56 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/25 12:41:46 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_DEBUG_H
# define CUBE3D_DEBUG_H

# ifndef CUBE3D_UNITEST_PARSER
#  define CUBE3D_UNITEST_PARSER 0
# endif

int	ret_print(int ret, const char *msg);

# define ERR_FILE_EXT    "Error\nBad file extension !\n"
# define ERR_OPEN_FILE   "Error\nFailed to open file !\n"
# define ERR_CLOSE_FILE  "Error\nFailed to close file !\n"
# define ERR_RFILE_TYPE  "Error\nBad file data->type ?!\n"
# define ERR_RDL_FAIL    "Error\nv_readline fail !\n"
# define ERR_VEC_ADD     "Error\nv_add fail !\n"
# define ERR_VEC_ALLOC   "Error\nv_alloc fail !\n"
# define ERR_SANI_FILE   "Error\nUnauthorized withe space, only ' ' and '\\n'!\n"
# define ERR_EMPTY_FILE  "Error\nEmpty map file !\n"
# define ERR_TEX_PARAM   "Error\nBad texture param !\n"
# define ERR_TEX_FORMAT  "Error\nBad texture format !\n"
# define ERR_TEX_TYPE    "Error\nBad texture type !\n"
# define ERR_TEX_TOKEN_FORMAT  "Error\nBad texture token format !\n"
# define ERR_SKY_TOKEN_FORMAT  "Error\nBad skybox token format !\n"
# define ERR_TEX_RESERVED  "Error\nBad or reserved texture token used !\n"
# define ERR_TEX_DUP     "Error\nDuplicate texture !\n"
# define ERR_NO_MAP_AFTER_TEX "Error\nNo map after texture !\n"
# define ERR_BAD_CUB_CHAR "Error\nUnauthorized character in the map !\n"
# define ERR_CUB_CONV_FUNC "Error\nf_{floor_level}_{char_type} fail !\n"
# define ERR_SEQ_BAD     "Error\nBad cube sequence\n"
# define ERR_CHUNK_W     "Error\nBad chunk line width\n"
# define ERR_CHUNK_H     "Error\nBad chunk line heigth\n"
# define ERR_MEMCPY      "Error\nmemcpy faild !\n"
# define ERR_NO_TEX      "Error\nTexture in chunk was not define !\n"
# define ERR_BAD_CHUNK_FLOOR  "Error\nBad chunk floor !\n"
# define ERR_BAD_XPM  "Error\nXPM file is invalid or corrupted !\n"
# define ERR_NULL_TEX   "Error\nt_texture *NULL !\n"
# define ERR_COLOR_R     "Error\n Bad color channel R\n"
# define ERR_COLOR_G     "Error\n Bad color channel G\n"
# define ERR_COLOR_B     "Error\n Bad color channel B\n"
# define ERR_COLOR_A     "Error\n Bad color channel A\n"

# define UNAUTHORIZED_SPACE "\t\v\f\r"
# define WHITE_SPACE "\t\v\f\r \n"

# ifdef DEBUG_PRINT

#  include <stdio.h>

static inline int	ret_print_debug(int ret, const char *msg, const char *file, const char *func, int line)
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
