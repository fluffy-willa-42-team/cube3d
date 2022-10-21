#ifndef CUBE3D_DEBUG_H
#define CUBE3D_DEBUG_H

int	ret_print(int ret, const char *msg);

# define ERR_FILE_EXT    "Error\nBad file extension !\n"
# define ERR_OPEN_FILE   "Error\nFailed to open file !\n"
# define ERR_RFILE_TYPE  "Error\nBad file data->type ?!\n"
# define ERR_RDL_FAIL    "Error\nv_readline fail !\n"
# define ERR_VEC_ADD     "Error\nv_add fail !\n"
# define ERR_SANI_FILE   "Error\nUnauthorized withe space, only ' ' and '\\n'!\n"
# define ERR_READ_TO_VEC "Error\nread_to_vec fail !\n"
# define ERR_TEX_FORMAT  "Error\nBad texture format !\n"
# define ERR_TEX_DUP     "Error\nDuplicate texture !\n"
# define ERR_NO_MAP_AFTER_TEX   "Error\nNo map after texture !/n"

#define UNAUTHORIZED_SPACE "\t\v\f\r"
#define WHITE_SPACE "\t\v\f\r \n"

#endif /* CUBE3D_DEBUG_H */
