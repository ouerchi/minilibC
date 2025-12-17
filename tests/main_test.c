#include "test_framework.h"

// Global stats definition
t_test_stats g_stats = {0, 0, 0};

// -- Helpers from old test --
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

// -- Tests --

static void	test_strjoin_func(void)
{
	char	a[] = "abc";
	char	b[] = "def";
	char	*c;

	c = ft_strjoin(a, b);
	ASSERT_TRUE(c != NULL, "ft_strjoin returned NULL");
	ASSERT_STR_EQ(c, "abcdef", "ft_strjoin(\"abc\",\"def\")");
	free(c);
}

static void	test_split_multi_delims_func(void)
{
	char	s[] = "a,b;cc  d";
	char	delims[] = ",; ";
	char	**p;

	p = ft_split(s, delims);
	ASSERT_TRUE(p != NULL, "ft_split returned NULL");
	ASSERT_STR_EQ(p[0], "a", "ft_split token 0");
	ASSERT_STR_EQ(p[1], "b", "ft_split token 1");
	ASSERT_STR_EQ(p[2], "cc", "ft_split token 2");
	ASSERT_STR_EQ(p[3], "d", "ft_split token 3");
	ASSERT_TRUE(p[4] == NULL, "ft_split token count (expected 4 tokens)");
	free_split(p);
}

static void	test_get_next_line_basic_func(void)
{
	char	path[128];
	int		fd;
	char	*line;

	fd = make_tmpfile("line1\nline2\nlast", path, sizeof(path));
	ASSERT_TRUE(fd >= 0, "could not create tmp file");
	
	line = get_next_line(fd);
	ASSERT_STR_EQ(line, "line1\n", "gnl line1");
	free(line);
	
	line = get_next_line(fd);
	ASSERT_STR_EQ(line, "line2\n", "gnl line2");
	free(line);
	
	line = get_next_line(fd);
	ASSERT_STR_EQ(line, "last", "gnl last (no newline)");
	free(line);
	
	line = get_next_line(fd);
	ASSERT_TRUE(line == NULL, "gnl expected NULL at EOF");
	
	close(fd);
	unlink(path);
}

static void	test_get_next_line_two_fds_func(void)
{
	char	path_a[128];
	char	path_b[128];
	int		fd_a;
	int		fd_b;
	char	*line;

	fd_a = make_tmpfile("A1\nA2\n", path_a, sizeof(path_a));
	fd_b = make_tmpfile("B1\nB2\n", path_b, sizeof(path_b));
	ASSERT_TRUE(fd_a >= 0 && fd_b >= 0, "could not create tmp files");

	line = get_next_line(fd_a);
	ASSERT_STR_EQ(line, "A1\n", "gnl fdA A1");
	free(line);
	
	line = get_next_line(fd_b);
	ASSERT_STR_EQ(line, "B1\n", "gnl fdB B1");
	free(line);
	
	line = get_next_line(fd_a);
	ASSERT_STR_EQ(line, "A2\n", "gnl fdA A2");
	free(line);
	
	line = get_next_line(fd_b);
	ASSERT_STR_EQ(line, "B2\n", "gnl fdB B2");
	free(line);

	close(fd_a);
	close(fd_b);
	unlink(path_a);
	unlink(path_b);
}

// -- ft_printf tests --
#define TEST_BUFFER_SIZE 2048

// Simple macro to reduce boilerplate in test_ft_printf_func
// Note: This expects to be inside a function variable scope
#define CHECK_PRINTF(expect_str, expect_ret, call) \
	do { \
		int pipefd[2]; \
		int orig_out = dup(1); \
		pipe(pipefd); \
		dup2(pipefd[1], 1); \
		close(pipefd[1]); \
		int ret = (call); \
		fflush(stdout); \
		dup2(orig_out, 1); \
		close(orig_out); \
		char buf[TEST_BUFFER_SIZE]; \
		memset(buf, 0, TEST_BUFFER_SIZE); \
		read(pipefd[0], buf, TEST_BUFFER_SIZE - 1); \
		close(pipefd[0]); \
		ASSERT_EQ(ret, expect_ret, "%d", "return value mismatch"); \
		ASSERT_STR_EQ(buf, expect_str, "output mismatch"); \
	} while (0)

static void	test_ft_printf_func(void)
{
	CHECK_PRINTF("hello", 5, ft_printf("hello"));
	CHECK_PRINTF("c=A", 3, ft_printf("c=%c", 'A'));
	CHECK_PRINTF("s=foo", 5, ft_printf("s=%s", "foo"));
	CHECK_PRINTF("d=123", 5, ft_printf("d=%d", 123));
	CHECK_PRINTF("d=-42", 5, ft_printf("d=%d", -42));
	CHECK_PRINTF("x=ff", 4, ft_printf("x=%x", 255));
	CHECK_PRINTF("X=FF", 4, ft_printf("X=%X", 255));
	// Note: (nil) is 5 chars.
	CHECK_PRINTF("(nil)", 5, ft_printf("%p", NULL));
    
    // Test mixing
    CHECK_PRINTF("10 + 20 = 30", 12, ft_printf("%d + %d = %d", 10, 20, 30));
}

int	main(void)
{
	printf("\n" COLOR_YELLOW "=== MINILIBC TEST SUITE ===" COLOR_RESET "\n\n");

	run_test(test_strjoin_func, "ft_strjoin");
	run_test(test_split_multi_delims_func, "ft_split multi-delims");
	run_test(test_get_next_line_basic_func, "get_next_line basic");
	run_test(test_get_next_line_two_fds_func, "get_next_line two fds");
	run_test(test_ft_printf_func, "ft_printf");

	printf("\n" COLOR_YELLOW "=== SUMMARY ===" COLOR_RESET "\n");
	printf("Total:  %d\n", g_stats.total_tests);
	printf("Passed: " COLOR_GREEN "%d" COLOR_RESET "\n", g_stats.passed_tests);
	printf("Failed: " COLOR_RED "%d" COLOR_RESET "\n", g_stats.failed_tests);

	if (g_stats.failed_tests > 0)
		return (1);
	return (0);
}
