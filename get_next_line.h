#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

int		gnl_has_newline(char *stash);
char	*gnl_get_line(char *stash);
char	*gnl_update_stash(char *stash);
char	*gnl_read(int fd, char *stash);

char	*get_next_line(int fd);

#endif
