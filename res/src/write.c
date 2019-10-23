#include "ud_file.h"

int     ud_file_write_ctr(char *path, char *content, int flag)
{
    if (!path)
        return (-1);
    
    if (!flag && !access(path, F_OK))
        remove(path);
    int     fd = open(path, O_RDWR | O_CREAT | flag, 0644);
    if (fd == -1)
    {
        char resolved_path[PATH_MAX];
        if (!realpath(path, resolved_path))
            ud_ut_error("Couldn't resolve absolute path from %s.", path);
        ud_ut_error("Couldn't create file %s, check that the provided path exists.", resolved_path);
    }
    if (!content) return (close(fd));
    int     w_ret = write(fd, content, ud_str_len(content));
    close(fd);
    if (w_ret == -1)
    {
        char resolved_path[PATH_MAX];
        if (!realpath(path, resolved_path))
            ud_ut_error("Couldn't resolve absolute path from %s.", path);
        ud_ut_error("Couldn't write to file %s.", resolved_path);
    }
    return (w_ret);
}