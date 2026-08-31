#include "get_next_line_bonus.h"

size_t	gnl_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s && s[len])
		len++;
	return (len);
}

char	*gnl_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

void	gnl_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	while (n > 0)
	{
		*d++ = *s++;
		n--;
	}
}

char	*gnl_strjoin(char *s1, char const *s2, size_t n)
{
	char	*joined;
	size_t	len1;

	len1 = gnl_strlen(s1);
	joined = malloc(len1 + n + 1);
	if (!joined)
		return (NULL);
	gnl_memcpy(joined, s1, len1);
	gnl_memcpy(joined + len1, s2, n);
	joined[len1 + n] = '\0';
	return (joined);
}

void	gnl_remove_fd(t_fdlist **fds, int fd)
{
	t_fdlist	*node;
	t_fdlist	*prev;

	node = *fds;
	prev = NULL;
	while (node && node->fd != fd)
	{
		prev = node;
		node = node->next;
	}
	if (!node)
		return ;
	if (prev)
		prev->next = node->next;
	else
		*fds = node->next;
	free(node->stash);
	free(node);
}
