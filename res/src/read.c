#include "ud_file.h"

char    *ud_file_read(char *path)
{
    int     fd = open(path, O_RDONLY);
    if (!path || access(path, R_OK) || read(fd, NULL, 0) == -1)
        return (NULL);
    
    char                buf[BUF_SIZE];
    size_t              len = 0;
    size_t              total_len = 0;

    typedef struct      uds_file_read_list {
        void            (*fp_free)(void *val);
        struct          uds_file_read_list *next;
        char            data[BUF_SIZE];
    }                   ud_file_read_list;

    ud_file_read_list   *buf_list = NULL;
    ud_file_read_list   *curr = NULL;

    len = read(fd, buf, BUF_SIZE);
    total_len += len;
    buf_list = ud_list_minit(ud_file_read_list);
    ud_mem_cpy(buf_list->data, buf, len);
    curr = buf_list;
    while ((len = read(fd, buf, BUF_SIZE)) > 0)
    {
        curr = ud_list_mpush(curr);
        ud_mem_cpy(curr->data, buf, len);
        total_len += len;
    }

    char *content = NULL;
    UD_UT_PROT_MALLOC(content = ud_ut_malloc((total_len + 1) * sizeof(char)));
    char *p_content = content;
    curr = buf_list;
    while (curr)
    {
        ud_mem_cpy_rd(p_content, (char *)curr->data, curr->next ? BUF_SIZE : total_len % BUF_SIZE);
        curr = curr->next;
    }
    *p_content = '\0';
    ud_list_free(buf_list);

    close(fd);
    return content;
}