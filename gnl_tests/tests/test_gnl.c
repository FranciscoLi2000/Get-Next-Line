#include "../gnl/get_next_line.h"
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

static void	test_regular(void)
{
	int	fd;

	write_file("/home/ubuntu/GNL_work/tests/data1.txt", "one\ntwo\nthree");
	fd = open("/home/ubuntu/GNL_work/tests/data1.txt", O_RDONLY);
	assert(fd >= 0);
	expect_line(fd, "one\n");
	expect_line(fd, "two\n");
	expect_line(fd, "three");
	expect_line(fd, NULL);
	close(fd);
}

static void	test_edges(void)
{
	int	fd;

	write_file("/home/ubuntu/GNL_work/tests/empty.txt", "");
	fd = open("/home/ubuntu/GNL_work/tests/empty.txt", O_RDONLY);
	assert(fd >= 0);
	expect_line(fd, NULL);
	close(fd);
	write_file("/home/ubuntu/GNL_work/tests/newlines.txt", "\n\n\n");
	fd = open("/home/ubuntu/GNL_work/tests/newlines.txt", O_RDONLY);
	assert(fd >= 0);
	expect_line(fd, "\n");
	expect_line(fd, "\n");
	expect_line(fd, "\n");
	expect_line(fd, NULL);
	close(fd);
	write_file("/home/ubuntu/GNL_work/tests/nonl.txt", "abc");
	fd = open("/home/ubuntu/GNL_work/tests/nonl.txt", O_RDONLY);
	assert(fd >= 0);
	expect_line(fd, "abc");
	expect_line(fd, NULL);
	close(fd);
}

static void	test_long_line(void)
{
	char	long_line[10001];
	int		fd;
	char	*line;

	memset(long_line, 'x', 10000);
	long_line[10000] = '\0';
	write_file("/home/ubuntu/GNL_work/tests/long.txt", long_line);
	fd = open("/home/ubuntu/GNL_work/tests/long.txt", O_RDONLY);
	assert(fd >= 0);
	line = get_next_line(fd);
	assert(line && strlen(line) == 10000);
	free(line);
	expect_line(fd, NULL);
	close(fd);
}

int	main(void)
{
	expect_line(-1, NULL);
	test_regular();
	test_edges();
	test_long_line();
	puts("MANDATORY TESTS PASSED");
	return (0);
}
