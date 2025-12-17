#ifndef TEST_FRAMEWORK_H
# define TEST_FRAMEWORK_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include "../include/minilibc.h"

// Colors
# define COLOR_RESET	"\033[0m"
# define COLOR_RED		"\033[31m"
# define COLOR_GREEN	"\033[32m"
# define COLOR_BLUE		"\033[34m"
# define COLOR_YELLOW	"\033[33m"

// Global stats
typedef struct s_test_stats {
	int	total_tests;
	int	passed_tests;
	int	failed_tests;
}	t_test_stats;

extern t_test_stats g_stats;

// Assertions
# define ASSERT_EQ(got, expected, fmt, msg) \
	do { \
		if ((got) != (expected)) { \
			fprintf(stderr, COLOR_RED "FAIL: %s\n" COLOR_RESET, msg); \
			fprintf(stderr, "  got:      " fmt "\n", got); \
			fprintf(stderr, "  expected: " fmt "\n", expected); \
			exit(1); \
		} \
	} while (0)

# define ASSERT_STR_EQ(got, expected, msg) \
	do { \
		const char *g = (got); \
		const char *e = (expected); \
		if ((g == NULL) != (e == NULL) || (g && strcmp(g, e) != 0)) { \
			fprintf(stderr, COLOR_RED "FAIL: %s\n" COLOR_RESET, msg); \
			fprintf(stderr, "  got:      \"%s\"\n", g ? g : "(null)"); \
			fprintf(stderr, "  expected: \"%s\"\n", e ? e : "(null)"); \
			exit(1); \
		} \
	} while (0)

# define ASSERT_TRUE(condition, msg) \
	do { \
		if (!(condition)) { \
			fprintf(stderr, COLOR_RED "FAIL: %s\n" COLOR_RESET, msg); \
			exit(1); \
		} \
	} while (0)

// Test runner helper
// Runs a test function in a child process to catch crashes
static void	run_test(void (*test_func)(void), const char *test_name)
{
	pid_t	pid;
	int		status;

	printf(COLOR_BLUE "[RUN] %s" COLOR_RESET, test_name);
	fflush(stdout);

	pid = fork();
	if (pid == 0)
	{
		// Child
		test_func();
		exit(0);
	}
	else if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
	else
	{
		// Parent
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		{
			printf("\r" COLOR_GREEN "[PASS] %s" COLOR_RESET "\n", test_name);
			g_stats.passed_tests++;
		}
		else
		{
			printf("\r" COLOR_RED "[FAIL] %s" COLOR_RESET "\n", test_name);
			if (WIFSIGNALED(status))
			{
				fprintf(stderr, "  Process terminated by signal %d (e.g. Segfault)\n", WTERMSIG(status));
			}
			g_stats.failed_tests++;
		}
		g_stats.total_tests++;
	}
}

#endif
