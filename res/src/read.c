#include "ud_file.h"

ud_list_define(ud_list_file_read, ud_list_default_free, NULL);

char    *ud_file_read_ctr(char *path, size_t *p_len)
{
    int     fd = open(path, O_RDONLY);
    if (!path || access(path, R_OK) || read(fd, NULL, 0) == -1)
        return (NULL);
    
    char                buf[BUF_SIZE];
    size_t              len = 0;
    size_t              total_len = 0;

    ud_list_file_read   *buf_list = NULL;
    ud_list_file_read   *curr = NULL;

    len = read(fd, buf, BUF_SIZE);
    total_len += len;
    buf_list = ud_list_minit(ud_list_file_read);
    ud_mem_cpy(buf_list->data, buf, len);
    curr = buf_list;
    while ((len = read(fd, buf, BUF_SIZE)) > 0)
    {
        curr = ud_list_mpush(curr);
        ud_mem_cpy(curr->data, buf, len);
        total_len += len;
    }

    char *content = NULL;
    ud_ut_prot_malloc(content = ud_ut_malloc((total_len + 1) * sizeof(char)));
    char *p_content = content;
    curr = buf_list;
    while (curr)
    {
        ud_mem_cpy_rd(p_content, (char *)curr->data, curr->next ? BUF_SIZE : total_len % BUF_SIZE);
        curr = curr->next;
    }
    *p_content = '\0';
    ud_list_free(ud_list_file_read, buf_list);

    close(fd);
    if (p_len) *p_len = total_len;
    return content;
}