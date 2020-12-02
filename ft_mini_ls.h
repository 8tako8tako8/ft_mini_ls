#ifndef FT_MINI_LS_H
# define FT_MINI_LS_H

# include <dirent.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct          s_list
{
    struct s_list       *next;
    char                *name;
    long                time;
}                       t_list;

#endif