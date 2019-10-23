#include "ud_file.h"

void    ud_file_clear(char *path)
{
    char eraser[] = "";
    ud_file_write(path, eraser);
}