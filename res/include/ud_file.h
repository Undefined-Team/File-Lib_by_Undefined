#ifndef UD_FILE_H
# define UD_FILE_H

// Lib
#include <unistd.h> // for read and write
#include <stdio.h> // for remove
#include <fcntl.h> // for open
#include <stdlib.h> // for realpath
#include <limits.h> // for PATH_MAX
#include <ud_string.h>

// Macro
# define ud_file_read(path)                     ud_file_read_ctr(path, NULL)
# define ud_file_write(path, content)           ud_file_write_ctr(path, content, 0)
# define ud_file_write_append(path, content)    ud_file_write_ctr(path, content, O_APPEND)
# define ud_file_exists(_path)                  ({ int _fd = open(_path, O_RDONLY); ud_bool _exists = !(!_path || access(_path, R_OK) || (read(_fd, NULL, 0) == -1)); close(_fd); _exists; })
# define BUF_SIZE                               4096

// Structures
ud_list_struct(ud_list_file_read, char data[BUF_SIZE]);

// Prototypes
char    *ud_file_read_ctr(char *path, size_t *p_len);
int     ud_file_write_ctr(char *path, char *content, int flag);
void    ud_file_clear(char *path);

#endif