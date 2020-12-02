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

void    ft_ls_option_aorlargea(char *path, char *option)
{
    DIR             *dir;
    struct dirent   *dent;
    char            *name;

    dir = opendir(path);
    if (dir == NULL)
    {
        perror(path);
        return ;
    }
    while ((dent = readdir(dir)) != NULL)
    {
        name = dent->d_name;
        if (option[1] == 'a')
            ft_put_d_name(name);
        else if (option[1] == 'A')
        {
            if (!((name[0] == '.' && name[1] == '\0') ||
                    (name[0] == '.' && name[1] == '.' && name[2] == '\0')))
                ft_put_d_name(name);
        }
    }
    closedir(dir);
}

void    ft_ls_default(char *path)
{
    DIR             *dir;
    struct dirent   *dent;
    char            *name;

    dir = opendir(path);
    if (dir == NULL)
    {
        perror(path);
        return ;
    }
    while ((dent = readdir(dir)) != NULL)
    {
        name = dent->d_name;
        if (name[0] != '.')
            ft_put_d_name(name);
    }
    closedir(dir);
}

void    ft_mini_ls(int argc, char **argv)
{
    char            *path;

    path = (char *)malloc(3);
    path[0] = '.';
    path[1] = '/';
    path[2] = '\0';
    if (argc == 1)
        ft_ls_default(path);
    else if (argc == 2)
    {
        if (argv[1][0] != '-')
        {
            free(path);
            path = ft_strdup(argv[1]);
            ft_ls_default(path);
        }
        else if (argv[1][0] == '-' && (argv[1][1] == 'a' || argv[1][1] == 'A') && argv[1][2] == '\0')
            ft_ls_option_aorlargea(path, argv[1]);
    }
    free(path);
}

int     main(int argc, char **argv)
{
    ft_mini_ls(argc, argv);
    //while (1);
    return (0);
}