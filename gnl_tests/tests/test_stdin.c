#include "../gnl/get_next_line.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*line;

	line = get_next_line(0);
	assert(line && strcmp(line, "stdin one\n") == 0);
	free(line);
	line = get_next_line(0);
	assert(line && strcmp(line, "stdin two") == 0);
	free(line);
	line = get_next_line(0);
	assert(line == NULL);
	puts("STDIN TEST PASSED");
	return (0);
}
