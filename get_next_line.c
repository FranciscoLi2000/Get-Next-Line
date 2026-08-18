#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = gnl_read(fd, stash);
	if (!stash)
		return (NULL);
	line = gnl_get_line(stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = gnl_update_stash(stash);
	return (line);
}
