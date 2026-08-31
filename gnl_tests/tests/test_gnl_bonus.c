#include "../gnl/get_next_line_bonus.h"
#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

static void	expect_line(int fd, const char *expected)
{
	char	*line;

	line = get_next_line(fd);
	if (!expected)
		assert(line == NULL);
	else
	{
		assert(line != NULL);
		assert(strcmp(line, expected) == 0);
		free(line);
	}
}

static void	write_file(const char *path, const char *content)
{
	int	fd;

	fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	assert(fd >= 0);
	assert(write(fd, content, strlen(content)) == (ssize_t)strlen(content));
	close(fd);
}

int	main(void)
{
	int	fd1;
	int	fd2;
	int	fd3;

	write_file("/home/ubuntu/GNL_work/tests/b1.txt", "a1\na2\na3");
	write_file("/home/ubuntu/GNL_work/tests/b2.txt", "b1\nb2");
	write_file("/home/ubuntu/GNL_work/tests/b3.txt", "c1\nc2\nc3\nc4");
	fd1 = open("/home/ubuntu/GNL_work/tests/b1.txt", O_RDONLY);
	fd2 = open("/home/ubuntu/GNL_work/tests/b2.txt", O_RDONLY);
	fd3 = open("/home/ubuntu/GNL_work/tests/b3.txt", O_RDONLY);
	assert(fd1 >= 0 && fd2 >= 0 && fd3 >= 0);
	expect_line(fd1, "a1\n");
	expect_line(fd2, "b1\n");
	expect_line(fd3, "c1\n");
	expect_line(fd1, "a2\n");
	expect_line(fd2, "b2");
	expect_line(fd3, "c2\n");
	expect_line(fd1, "a3");
	expect_line(fd2, NULL);
	expect_line(fd3, "c3\n");
	expect_line(fd1, NULL);
	expect_line(fd3, "c4");
	expect_line(fd3, NULL);
	close(fd1);
	close(fd2);
	close(fd3);
	puts("BONUS TESTS PASSED");
	return (0);
}
