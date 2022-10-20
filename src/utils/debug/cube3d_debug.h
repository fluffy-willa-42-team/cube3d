#ifndef CUBE3D_DEBUG_H
#define CUBE3D_DEBUG_H

int	ret_print(int ret, const char *msg);

# define ERR_FILE_EXT    "Error: Bad file extension !\n"
# define ERR_OPEN_FILE   "Error: Failed to open file !\n"
# define ERR_RFILE_TYPE  "Error: Bad file data->type ?!\n"
# define ERR_VEC_FAIL    "Error: v_readline fail !\n"
# define ERR_SANI_FILE   "Error: Unauthorized withe space, only ' ' and '\\n'!\n"
# define ERR_READ_TO_VEC "Error: read_to_vec fail !\n"

#define UNAUTHORIZED_SPACE "\t\v\f\r"
#define WHITE_SPACE "\t\v\f\r \n"

#endif /* CUBE3D_DEBUG_H */
