#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>

void    ft_putstr(char *s)
{
    int     i;

    i = 0;
    while (s[i])
    {
        write(1, &s[i], 1);
        i++;
    }
}

int     ft_strlen(char *s)
{
    int     i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}

char    *ft_parse_args(int argc, char **argv)
{
    char   *path;
    char    *tmp;
    int     len;

    path = (char *)malloc(3);
    path = "./";
    if (argc == 2)
    {
        len = ft_strlen(argv[1]);
        tmp = (char *)malloc(len + 1);
        free(path);
        path = tmp;
    }
    return (path);
}

int main(int argc, char **argv)
{
    DIR     *dir;
    struct dirent *dent;
    char    *path;

    path = ft_parse_args(argc, argv);
    dir = opendir(path);
    if (dir == NULL)
    {
        perror(path);
        return (1);
    }
    while ((dent = readdir(dir)) != NULL)
    {
        ft_putstr(dent->d_name);
        ft_putstr("\n");
    }
    closedir(dir);
    return (0);
}