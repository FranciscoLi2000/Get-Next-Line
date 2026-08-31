#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_fdlist
{
	int				fd;
	char			*stash;
	struct s_fdlist	*next;
}	t_fdlist;

char	*get_next_line(int fd);
size_t	gnl_strlen(const char *s);
char	*gnl_strchr(const char *s, int c);
char	*gnl_strjoin(char *s1, char const *s2, size_t n);
void	gnl_memcpy(void *dst, const void *src, size_t n);
void	gnl_remove_fd(t_fdlist **fds, int fd);
char	*gnl_extract_line(char *stash);
char	*gnl_update_stash(char *stash);

#endif
