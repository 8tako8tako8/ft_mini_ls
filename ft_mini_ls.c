#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>

void    ft_put_d_name(char *s)
{
    size_t     i;

    i = 0;
    while (s[i])
    {
        write(1, &s[i], 1);
        i++;
    }
    write(1, "\n", 1);
}

size_t  ft_strlen(char *s)
{
    size_t     i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}

char    *ft_strdup(char *s)
{
    size_t      i;
    size_t      len;
    char        *ret_str;

    len = ft_strlen(s);
    ret_str = (char *)malloc(len + 1);
    i = 0;
    while (s[i])
    {
        ret_str[i] = s[i];
        i++;
    }
    ret_str[i] = '\0';
    return (ret_str);
}

void    ft_mini_ls(int argc, char **argv)
{
    DIR             *dir;
    struct dirent   *dent;
    char            *path;

    path = (char *)malloc(3);
    path[0] = '.';
    path[1] = '/';
    path[2] = '\0';
    if (argc == 2)
    {
        free(path);
        path = ft_strdup(argv[1]);
    }
    //path = ft_parse_args(argc, argv);
    dir = opendir(path);
    if (dir == NULL)
    {
        perror(path);
        return ;
    }
    while ((dent = readdir(dir)) != NULL)
        ft_put_d_name(dent->d_name);
    closedir(dir);
    free(path);
}

int     main(int argc, char **argv)
{
    ft_mini_ls(argc, argv);
    //while (1);
    return (0);
}