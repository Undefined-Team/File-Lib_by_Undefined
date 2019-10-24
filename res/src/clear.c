#include "ud_file.h"

void    ud_file_clear(char *path)
{
    ud_file_write(path, "");
}