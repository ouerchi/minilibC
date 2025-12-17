

#ifndef MINILIBC_H
# define MINILIBC_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

/*
** Public types
*/
/**
 * @brief Simple linked list node structure.
 */
typedef struct s_list
{
	void			*content; /**< The content of the node. */
	struct s_list	*next;    /**< The next node in the list. */
}	t_list;

/*
** get_next_line configuration (can be overridden at compile time)
*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

/*
** Character checks / case
*/
/**
 * @brief Checks if the character is alphanumeric.
 * @param c The character to check.
 * @return Non-zero if true, 0 if false.
 */
int		ft_isalnum(int c);

/**
 * @brief Checks if the character is an alphabetic letter.
 * @param c The character to check.
 * @return Non-zero if true, 0 if false.
 */
int		ft_isalpha(int c);

/**
 * @brief Checks if the character is a digit.
 * @param c The character to check.
 * @return Non-zero if true, 0 if false.
 */
int		ft_isdigit(int c);

/**
 * @brief Checks if the character is a 7-bit ASCII character.
 * @param c The character to check.
 * @return Non-zero if true, 0 if false.
 */
int		ft_isascii(int c);

/**
 * @brief Checks if the character is printable (including space).
 * @param c The character to check.
 * @return Non-zero if true, 0 if false.
 */
int		ft_isprint(int c);

/**
 * @brief Converts a character to uppercase.
 * @param c The character to convert.
 * @return The converted character, or c if not convertible.
 */
int		ft_toupper(int c);

/**
 * @brief Converts a character to lowercase.
 * @param c The character to convert.
 * @return The converted character, or c if not convertible.
 */
int		ft_tolower(int c);

/*
** Numbers
*/
/**
 * @brief Converts a string to an integer.
 * @param str The string to convert.
 * @return The integer value.
 */
int		ft_atoi(const char *str);

/**
 * @brief Converts an integer to a string.
 * @param n The integer to convert.
 * @return A newly allocated string representing the integer.
 */
char	*ft_itoa(int n);

/*
** Strings
*/
/**
 * @brief Computes the length of a string.
 * @param str The string to measure.
 * @return The length of the string.
 */
size_t	ft_strlen(const char *str);

/**
 * @brief Duplicates a string.
 * @param src The string to duplicate.
 * @return A newly allocated copy of the string.
 */
char	*ft_strdup(const char *src);

/**
 * @brief Locates the first occurrence of a character in a string.
 * @param str The string to search.
 * @param c The character to find.
 * @return A pointer to the character, or NULL if not found.
 */
char	*ft_strchr(const char *str, int c);

/**
 * @brief Locates the last occurrence of a character in a string.
 * @param str The string to search.
 * @param c The character to find.
 * @return A pointer to the character, or NULL if not found.
 */
char	*ft_strrchr(const char *str, int c);

/**
 * @brief Compares two strings up to n characters.
 * @param s1 The first string.
 * @param s2 The second string.
 * @param n The maximum number of characters to compare.
 * @return 0 if equal, otherwise difference between first differing chars.
 */
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 * @brief Locates a substring in a string.
 * @param big The string to search in.
 * @param little The substring to search for.
 * @param len The maximum number of characters to search.
 * @return A pointer to the beginning of the substring, or NULL if not found.
 */
char	*ft_strnstr(const char *big, const char *little, size_t len);

/**
 * @brief Copies a string to a buffer with size limitation.
 * @param dst The destination buffer.
 * @param src The source string.
 * @param dstsize The size of the destination buffer.
 * @return The length of the source string.
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

/**
 * @brief Appends a string to a buffer with size limitation.
 * @param dst The destination buffer.
 * @param src The source string.
 * @param dstsize The size of the destination buffer.
 * @return The total length of the string that would have been created.
 */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

/**
 * @brief Joins two strings into a new string.
 * @param s1 The first string.
 * @param s2 The second string.
 * @return A newly allocated string containing s1 + s2.
 */
char	*ft_strjoin(char *s1, char *s2);

/**
 * @brief Creates a substring from a string.
 * @param s The source string.
 * @param start The start index.
 * @param len The maximum length of the substring.
 * @return A newly allocated substring.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len);

/**
 * @brief Trims characters from the beginning and end of a string.
 * @param s1 The source string.
 * @param set The set of characters to trim.
 * @return A newly allocated trimmed string.
 */
char	*ft_strtrim(char const *s1, char const *set);

/**
 * @brief Applies a function to each character of a string to create a new string.
 * @param s The source string.
 * @param f The function to apply.
 * @return A newly allocated string.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/**
 * @brief Applies a function to each character of a string in place.
 * @param s The string to modify.
 * @param f The function to apply.
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

/*
** Split (multi-delimiter)
*/
/**
 * @brief Splits a string using any character from a set of delimiters.
 * @param s The string to split.
 * @param delims The set of delimiter characters.
 * @return A NULL-terminated array of strings.
 */
char	**ft_split(char const *s, char *delims);

/*
** Memory
*/
/**
 * @brief Writes zeroes to a byte string.
 * @param str The string to write to.
 * @param n The number of bytes to write.
 */
void	ft_bzero(void *str, size_t n);

/**
 * @brief Allocates memory and initializes it to zero.
 * @param count The number of elements.
 * @param size The size of each element.
 * @return A pointer to the allocated memory.
 */
void	*ft_calloc(size_t count, size_t size);

/**
 * @brief Fills a byte string with a byte value.
 * @param str The string to fill.
 * @param value The value to fill with.
 * @param len The number of bytes to fill.
 * @return A pointer to the string.
 */
void	*ft_memset(void *str, int value, size_t len);

/**
 * @brief Locates the first occurrence of a byte in a byte string.
 * @param str The string to search.
 * @param c The byte to find.
 * @param n The number of bytes to search.
 * @return A pointer to the byte, or NULL if not found.
 */
void	*ft_memchr(const void *str, int c, size_t n);

/**
 * @brief Compares two byte strings.
 * @param s1 The first string.
 * @param s2 The second string.
 * @param n The number of bytes to compare.
 * @return 0 if equal, otherwise difference between first differing bytes.
 */
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/**
 * @brief Copies memory area.
 * @param dst The destination memory.
 * @param src The source memory.
 * @param n The number of bytes to copy.
 * @return A pointer to the destination.
 */
void	*ft_memcpy(void *dst, const void *src, size_t n);

/**
 * @brief Copies memory area, handling overlap.
 * @param dst The destination memory.
 * @param src The source memory.
 * @param len The number of bytes to copy.
 * @return A pointer to the destination.
 */
void	*ft_memmove(void *dst, const void *src, size_t len);

/*
** FD output
*/
/**
 * @brief Outputs a character to the given file descriptor.
 * @param c The character to output.
 * @param fd The file descriptor.
 */
void	ft_putchar_fd(char c, int fd);

/**
 * @brief Outputs a string to the given file descriptor.
 * @param s The string to output.
 * @param fd The file descriptor.
 */
void	ft_putstr_fd(char *s, int fd);

/**
 * @brief Outputs a string followed by a newline to the given file descriptor.
 * @param s The string to output.
 * @param fd The file descriptor.
 */
void	ft_putendl_fd(char *s, int fd);

/**
 * @brief Outputs an integer to the given file descriptor.
 * @param n The integer to output.
 * @param fd The file descriptor.
 */
void	ft_putnbr_fd(int n, int fd);

/*
** Line reader
*/
/**
 * @brief Reads the next line from a file descriptor.
 * @param fd The file descriptor to read from.
 * @return The line read (including newline), or NULL on EOF/error.
 */
char	*get_next_line(int fd);

/*
** Printf
*/
/**
 * @brief Custom printf implementation.
 * @param format The format string.
 * @return The number of characters printed.
 */
int		ft_printf(const char *format, ...);

/*
** Linked list
*/
/**
 * @brief Creates a new list node.
 * @param content The content to put in the node.
 * @return The new node.
 */
t_list	*ft_lstnew(void *content);

/**
 * @brief Counts the number of elements in a list.
 * @param lst The list.
 * @return The number of elements.
 */
int		ft_lstsize(t_list *lst);

/**
 * @brief Returns the last element of the list.
 * @param lst The list.
 * @return The last element.
 */
t_list	*ft_lstlast(t_list *lst);

/**
 * @brief Adds a new element at the beginning of the list.
 * @param lst The address of a pointer to the first link of a list.
 * @param new The element to add.
 */
void	ft_lstadd_front(t_list **lst, t_list *new);

/**
 * @brief Adds a new element at the end of the list.
 * @param lst The address of a pointer to the first link of a list.
 * @param new The element to add.
 */
void	ft_lstadd_back(t_list **lst, t_list *new);

/**
 * @brief Deletes a node and frees its content.
 * @param lst The node to delete.
 * @param del The function to delete the content.
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *));

/**
 * @brief Deletes and frees the given element and every successor of that element.
 * @param lst The address of a pointer to a node.
 * @param del The function to delete the content.
 */
void	ft_lstclear(t_list **lst, void (*del)(void *));

/**
 * @brief Iterates the list and applies the function f to the content of each element.
 * @param lst The list.
 * @param f The function to apply.
 */
void	ft_lstiter(t_list *lst, void (*f)(void *));

/**
 * @brief Iterates the list and applies f to the content of each element to create a new list.
 * @param lst The list.
 * @param f The function to apply.
 * @param del The function to delete the content if needed.
 * @return The new list.
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif


