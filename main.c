#include "minilibc.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	free_split(char **parts)
{
	size_t	token_idx;

	if (!parts)
		return;
	token_idx = 0;
	while (parts[token_idx])
		free(parts[token_idx++]);
	free(parts);
}

static void	test_basics(void)
{
	char	left_part[] = "mini";
	char	right_part[] = "libc";
	char	*joined_str;

	printf("ft_strlen(\"%s\") = %zu\n", left_part, ft_strlen(left_part));
	joined_str = ft_strjoin(left_part, right_part);
	if (!joined_str)
	{
		fprintf(stderr, "ft_strjoin failed\n");
		return;
	}
	printf("ft_strjoin(\"%s\",\"%s\") = \"%s\"\n",
		left_part, right_part, joined_str);
	free(joined_str);
}

static void	test_split(void)
{
	char	input_str[] = "a,b;cc  d";
	char	delimiters[] = ",; ";
	char	**tokens;
	size_t	token_idx;

	tokens = ft_split(input_str, delimiters);
	if (!tokens)
	{
		fprintf(stderr, "ft_split failed\n");
		return;
	}
	printf("ft_split(\"%s\", \"%s\"):\n", input_str, delimiters);
	token_idx = 0;
	while (tokens[token_idx])
	{
		printf("  [%zu] \"%s\"\n", token_idx, tokens[token_idx]);
		token_idx++;
	}
	free_split(tokens);
}

static void	del_str(void *ptr)
{
	free(ptr);
}

static void	*dup_content(void *content_ptr)
{
	return (ft_strdup((char *)content_ptr));
}

static void	test_list_bonus(void)
{
	t_list	*list_head;
	t_list	*mapped_list;

	list_head = NULL;
	ft_lstadd_back(&list_head, ft_lstnew(ft_strdup("one")));
	ft_lstadd_back(&list_head, ft_lstnew(ft_strdup("two")));
	ft_lstadd_back(&list_head, ft_lstnew(ft_strdup("three")));
	printf("ft_lstsize = %d\n", ft_lstsize(list_head));
	mapped_list = ft_lstmap(list_head, dup_content, del_str);
	printf("ft_lstsize(mapped) = %d\n", ft_lstsize(mapped_list));
	ft_lstclear(&list_head, del_str);
	ft_lstclear(&mapped_list, del_str);
}

static void	test_gnl(int fd)
{
	char	*line_str;
	int		line_number;

	line_number = 1;
	while (1)
	{
		line_str = get_next_line(fd);
		if (!line_str)
			break;
		printf("GNL %d: %s", line_number++, line_str);
		if (ft_strchr(line_str, '\n') == NULL)
			printf("\n");
		free(line_str);
	}
}

int	main(int argc, char **argv)
{
	int	input_fd;

	test_basics();
	test_split();
	test_list_bonus();

	input_fd = 0;
	if (argc >= 2)
	{
		input_fd = open(argv[1], O_RDONLY);
		if (input_fd < 0)
		{
			perror("open");
			return (1);
		}
	}
	printf("\n--- get_next_line (%s) ---\n", (argc >= 2) ? argv[1] : "stdin");
	test_gnl(input_fd);
	if (argc >= 2)
		close(input_fd);
	return (0);
}
