#include "minilibc.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void	die(const char *msg)
{
	write(2, msg, strlen(msg));
	write(2, "\n", 1);
	exit(1);
}

static void	assert_str_eq(const char *got, const char *expected, const char *ctx)
{
	if (!got && !expected)
		return;
	if (!got || !expected || strcmp(got, expected) != 0)
	{
		fprintf(stderr, "FAIL: %s\n  got:      %s\n  expected: %s\n",
			ctx, got ? got : "(null)", expected ? expected : "(null)");
		exit(1);
	}
}

static void	free_split(char **parts)
{
	size_t	i;

	if (!parts)
		return;
	i = 0;
	while (parts[i])
		free(parts[i++]);
	free(parts);
}

static int	make_tmpfile(const char *content, char *out_path, size_t out_sz)
{
	int		fd;
	char	tmpl[] = "/tmp/minilibc_testXXXXXX";

	fd = mkstemp(tmpl);
	if (fd < 0)
		return (-1);
	if (strlen(tmpl) + 1 > out_sz)
	{
		close(fd);
		unlink(tmpl);
		return (-1);
	}
	ft_strlcpy(out_path, tmpl, out_sz);
	if (write(fd, content, strlen(content)) < 0)
	{
		close(fd);
		unlink(tmpl);
		return (-1);
	}
	if (lseek(fd, 0, SEEK_SET) < 0)
	{
		close(fd);
		unlink(tmpl);
		return (-1);
	}
	return (fd);
}

static void	test_strjoin(void)
{
	char	a[] = "abc";
	char	b[] = "def";
	char	*c;

	c = ft_strjoin(a, b);
	if (!c)
		die("FAIL: ft_strjoin returned NULL");
	assert_str_eq(c, "abcdef", "ft_strjoin(\"abc\",\"def\")");
	free(c);
}

static void	test_split_multi_delims(void)
{
	char	s[] = "a,b;cc  d";
	char	delims[] = ",; ";
	char	**p;

	p = ft_split(s, delims);
	if (!p)
		die("FAIL: ft_split returned NULL");
	assert_str_eq(p[0], "a", "ft_split token 0");
	assert_str_eq(p[1], "b", "ft_split token 1");
	assert_str_eq(p[2], "cc", "ft_split token 2");
	assert_str_eq(p[3], "d", "ft_split token 3");
	if (p[4] != NULL)
		die("FAIL: ft_split token count (expected 4 tokens)");
	free_split(p);
}

static void	test_get_next_line_basic(void)
{
	char	path[128];
	int		fd;
	char	*line;

	fd = make_tmpfile("line1\nline2\nlast", path, sizeof(path));
	if (fd < 0)
		die("FAIL: could not create tmp file");
	line = get_next_line(fd);
	assert_str_eq(line, "line1\n", "gnl line1");
	free(line);
	line = get_next_line(fd);
	assert_str_eq(line, "line2\n", "gnl line2");
	free(line);
	line = get_next_line(fd);
	assert_str_eq(line, "last", "gnl last (no newline)");
	free(line);
	line = get_next_line(fd);
	if (line != NULL)
		die("FAIL: gnl expected NULL at EOF");
	close(fd);
	unlink(path);
}

static void	test_get_next_line_two_fds(void)
{
	char	path_a[128];
	char	path_b[128];
	int		fd_a;
	int		fd_b;
	char	*line;

	fd_a = make_tmpfile("A1\nA2\n", path_a, sizeof(path_a));
	fd_b = make_tmpfile("B1\nB2\n", path_b, sizeof(path_b));
	if (fd_a < 0 || fd_b < 0)
		die("FAIL: could not create tmp files");

	line = get_next_line(fd_a);
	assert_str_eq(line, "A1\n", "gnl fdA A1");
	free(line);
	line = get_next_line(fd_b);
	assert_str_eq(line, "B1\n", "gnl fdB B1");
	free(line);
	line = get_next_line(fd_a);
	assert_str_eq(line, "A2\n", "gnl fdA A2");
	free(line);
	line = get_next_line(fd_b);
	assert_str_eq(line, "B2\n", "gnl fdB B2");
	free(line);

	close(fd_a);
	close(fd_b);
	unlink(path_a);
	unlink(path_b);
}

int	main(void)
{
	test_strjoin();
	test_split_multi_delims();
	test_get_next_line_basic();
	test_get_next_line_two_fds();
	printf("OK: all tests passed\n");
	return (0);
}


