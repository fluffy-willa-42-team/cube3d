/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d_debug.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:54:56 by mahadad           #+#    #+#             */
/*   Updated: 2022/10/27 18:00:51 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_DEBUG_H
# define CUBE3D_DEBUG_H

int	ret_print(int ret, const char *msg);

# define ERR_FILE_EXT    "Error\nBad file extension !\n"
# define ERR_OPEN_FILE   "Error\nFailed to open file !\n"
# define ERR_RFILE_TYPE  "Error\nBad file data->type ?!\n"
# define ERR_RDL_FAIL    "Error\nv_readline fail !\n"
# define ERR_VEC_ADD     "Error\nv_add fail !\n"
# define ERR_SANI_FILE   "Error\nUnauthorized withe space, only ' ' and '\\n'!\n"
# define ERR_EMPTY_FILE  "Error\nEmpty map file !\n"
# define ERR_TEX_FORMAT  "Error\nBad texture format !\n"
# define ERR_TEX_DUP     "Error\nDuplicate texture !\n"
# define ERR_NO_MAP_AFTER_TEX   "Error\nNo map after texture !\n"
# define ERR_BAD_CUB_CHAR "Error\nnUnauthorized character in the map !\n"

# define UNAUTHORIZED_SPACE "\t\v\f\r"
# define WHITE_SPACE "\t\v\f\r \n"

#endif /* CUBE3D_DEBUG_H */
