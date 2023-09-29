#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>

// function to log test results.
void	log_test_result(const char *test_name, bool passed, size_t expected, size_t result)
{
	FILE	*log_file = fopen("libft_test_results.log", "a");
	if (log_file) 
	{
		fclose(log_file);
	}
	printf("%s: %s -> expected: %zu; result: %zu\n", test_name, passed ? "OK" : "FAIL", expected, result);
}

// ft_strlcat.
void	test_ft_strlcat()
{
	char	dest[20];
	ft_strlcpy(dest, "Hello, ", sizeof(dest));
	const char	*src = "world!";
	size_t	result = ft_strlcat(dest, src, sizeof(dest));
	size_t	expected = strlen("Hello, world!");
	
	if (result == expected && strncmp(dest, "Hello, world!", sizeof(dest)) == 0)
	{
		log_test_result("ft_strlcat", true, expected, result);
	}
	else
	{
		log_test_result("ft_strlcat", false, expected, result);
	}
}

// ft_strlen.
void	test_ft_strlen()
{
	const char	*str = "Hello, world!";
	size_t	result = ft_strlen(str);
	size_t	expected = strlen(str);

	if (result == expected)
	{
		log_test_result("ft_strlen", true, expected, result);
	}
	else
	{
		log_test_result("ft_strlen", false, expected, result);
	}
}

// ft_strlcpy.
void	test_ft_strlcpy()
{
	char	dest[20];
	const char	*src = "Hello, world!";
	size_t	result = ft_strlcpy(dest, src, sizeof(dest));
	size_t	expected = strlen(src);
	
	if (result == expected && strncmp(dest, src, sizeof(dest)) == 0) 
	{
		log_test_result("ft_strlcpy", true, expected, result);
	}
	else
	{
		log_test_result("ft_strlcpy", false, expected, result);
	}
}

// ft_isalpha.
void	test_ft_isalpha()
{
	int	c = 'A'; // Try also with: "a" " " "\t" "\n" "12" "" "A1B2C3" " Hello "
	int	result = ft_isalpha(c);
	int	expected = isalpha(c);
	
	if (result == expected)
	{
		log_test_result("ft_isalpha", true, expected, result);
	}
	else
	{
		log_test_result("ft_isalpha", false, expected, result);
	}
}

// ft_isalnum.
void	test_ft_isalnum()
{
	int	c = 'A'; // Try also with: "a" " " "\t" "\n" "12345" "" "%" "H3ll0!W0rld" " Hello "
	int	result = ft_isalnum(c);
	int	expected = isalnum(c);

	if (result == expected)
	{
		log_test_result("ft_isalnum", true, expected, result);
	}
	else
	{
		log_test_result("ft_isalnum", false, expected, result);
	}
}

// ft_isdigit.
void	test_ft_isdigit()
{
	int	c = '9'; // Try also with: "a" " " "\t" "\n" "12345" "" "%" "H3ll0!W0rld" " Hello "
	int	result = ft_isdigit(c);
	int	expected = isdigit(c);

	if (result == expected)
	{
		log_test_result("ft_isdigit", true, expected, result);
	}
	else
	{
		log_test_result("ft_isdigit", false, expected, result);
	}
}

// ft_isascii.
void	test_ft_isascii()
{
	int	c = 65; // Try also with: "a" " " "\t" "\n" "12345" "" "%" "H3ll0!W0rld" " Hello "
	int	result = ft_isascii(c);
	int	expected = isascii(c);
	
	if (result == expected)
	{
		log_test_result("ft_isascii", true, expected, result);
	}
	else
	{
		log_test_result("ft_isascii", false, expected, result);
	}
}

// ft_isprint.
void	test_ft_isprint()
{
	int	c = 65; // Try also with: "a" " " "\t" "\n" "12345" "" "%" "H3ll0!W0rld" " Hello "
	int	result = ft_isprint(c);
	int	expected = isprint(c);
	
	if (result == expected)
	{
		log_test_result("ft_isprint", true, expected, result);
	}
	else
	{
		log_test_result("ft_isprint", false, expected, result);
	}
}

// ft_strncmp.
void	test_ft_strncmp()
{
	const char	*s1 = "Hello, world!";
	const char	*s2 = "Hello!"; // Try also with: "Hello, world!" "Hello, universe!"
	size_t	n = 6;
	int	result = ft_strncmp(s1, s2, n);
	int	expected = strncmp(s1, s2, n);
	
	if (result == expected)
	{
		log_test_result("ft_strncmp", true, expected, result);
	}
	else
	{
		log_test_result("ft_strncmp", false, expected, result);
	}	
}

// ft_memset.
void	test_ft_memset()
{
	char	str[20] = "Hello, world!";
	char	*result = ft_memset(str, 'A', 5);
	char	*expected = memset(str, 'A', 5);
	
	if (memcmp(result, expected, 5) == 0)
	{
		log_test_result("ft_memset", true, 5, 5);
	}
	else
	{
		log_test_result("ft_memset", false, 5, 5);
	}
}

// ft_bzero.
void	test_ft_bzero() 
{
	char	buffer[10] = "Hello!";
	ft_bzero(buffer, 5);
	bool	passed = true;

	for (int i = 0; i < 5; i++)
	{
		if (buffer[i] != 0)
		{
			passed = false;
			break;
		}
	}
	if (passed)
	{
		log_test_result("ft_bzero", true, 0, 0);
	}
	else
	{
		log_test_result("ft_bzero", false, 0, 0);
	}
}

// ft_memcpy.
void	test_ft_memcpy()
{
	char	src[] = "Hello, world!";
	char	dest[20] = "";
	char	*result = ft_memcpy(dest, src, sizeof(src));
	char	*expected = memcpy(dest, src, sizeof(src));

	if (result == expected && strcmp(dest, src) == 0) 
	{
		log_test_result("ft_memcpy", true, 0, 0);
	}
	else
	{
		log_test_result("ft_memcpy", false, 0, 0);
	}
}

// ft_memmove.
void	test_ft_memmove()
{
	char	str[] = "this is a test string.......";
	char	expected[] = "this is a test string again";
	
	ft_memmove(str + 20, str + 15, 11);
	size_t	expected_len = strlen(expected);
	size_t	str_len = strlen(str);
	if (strcmp(str, expected) == 0)
	{
		log_test_result("ft_memmove", true, expected_len, str_len);
	}
	else
	{
		log_test_result("ft_memmove", false, expected_len, str_len);
	}
}

// ft_toupper.
void	test_ft_toupper()
{
	int	c = 'a';
	int	result = ft_toupper(c);
	int	expected = toupper(c);

	if (result == expected)
	{
		log_test_result("ft_toupper", true, expected, result);
	}
	else
	{
		log_test_result("ft_toupper", false, expected, result);
	}
}

// ft_tolower.
void	test_ft_tolower()
{
	int	c = 'A';
	int	result = ft_tolower(c);
	int	expected = tolower(c);

	if (result == expected)
	{
		log_test_result("ft_tolower", true, expected, result);
	}
	else
	{
		log_test_result("ft_tolower", false, expected, result);
	}
}

// ft_strchr.
void	test_ft_strchr()
{
	const char	*s = "Hello, world!";
	int	c = 'w';
	char	*result = ft_strchr(s, c);
	char	*expected = strchr(s, c);
	
	if (result == expected)
	{
		log_test_result("ft_strchr", true, (size_t)expected, (size_t)result);
	}
	else
	{
		log_test_result("ft_strchr", false, (size_t)expected, (size_t)result);
	}
}

// ft_strrchr.
void	test_ft_strrchr()
{
	const char	*s = "Hello, world!";
	int	c = 'o';
	char	*result = ft_strrchr(s, c);
	char	*expected = strrchr(s, c);
	
	if (result == expected)
	{
		log_test_result("ft_strrchr", true, (size_t)expected, (size_t)result);
	}
	else
	{
		log_test_result("ft_strrchr", false, (size_t)expected, (size_t)result);
	}
}

// ft_strnstr.
void	test_ft_strnstr()
{
	const char	*big_str = "Hello, world!";
	const char	*small_str = "world";
	size_t	len = 13;
	char	*result = ft_strnstr(big_str, small_str, len);
	char	*expected = strnstr(big_str, small_str, len);

	if (result == expected)
	{
		log_test_result("ft_strnstr", true, (size_t)expected, (size_t)result);
	}
	else
	{
		log_test_result("ft_strnstr", false, (size_t)expected, (size_t)result);
	}
}

// ft_memchr.
void	test_ft_memchr()
{
	const char	*s = "Hello, world!";
	int	c = 'w';
	void	*result = ft_memchr(s, c, strlen(s));
	void	*expected = memchr(s, c, strlen(s));
	
	if (result == expected)
	{
		log_test_result("ft_memchr", true, (size_t)expected, (size_t)result);
	}
	else
	{
		log_test_result("ft_memchr", false, (size_t)expected, (size_t)result);
	}
}

// ft_memcmp.
void	test_ft_memcmp()
{
	const char	*s1 = "Hello";
	const char 	*s2 = "World";
	size_t	len = 6;
	int	result = ft_memcmp(s1, s2, len);
	int	expected = memcmp(s1, s2, len);

	if (result == expected)
	{
		log_test_result("ft_memcmp", true, expected, result);
	}
	else
	{
		log_test_result("ft_memcmp", false, expected, result);
	}
}

// ft_atoi.
void	test_ft_atoi() 
{
	const char *str = "12345"; // Try also with: "12345" "-6789" "\t\n 12" "\t\n -12" "\t\n +12"
	int result = ft_atoi(str);
	int expected = atoi(str);
	
	if (result == expected)
	{
		log_test_result("ft_atoi", true, expected, result);
	}
	else
	{
		log_test_result("ft_atoi", false, expected, result);
	}
}

// ft_calloc.
void	test_ft_calloc()
{
	size_t	count = 5;
	size_t	size = sizeof(int);
	int	*result = ft_calloc(count, size);
	int	*expected = calloc(count, size);

	if ((!result && !expected) || memcmp(result, expected, count * size) == 0)
	{
		log_test_result("ft_calloc", true, count * size, count * size); // sizes, not pointers
	}
	else
	{
		log_test_result("ft_calloc", false, count * size, count * size); // sizes, not pointers
	}
	free(result);
	free(expected);
}

// ft_strdup.
void	test_ft_strdup()
{
	const char	*s = "Hello, world!";
	char	*result = ft_strdup(s);
	char	*expected = strdup(s);
	
	if ((result && expected && strcmp(result, expected) == 0) || (!result && !expected))
	{
		log_test_result("ft_strdup", true, strlen(s) + 1, strlen(s) + 1); //include null terminator
	}
	else
	{
	log_test_result("ft_strdup", false, strlen(s) + 1, strlen(s) + 1); //include null terminator
	}
	free(result);
}

// ft_substr.
void	test_ft_substr()
{
	const char	*s = "Hello, world!";
	unsigned int	start = 7;
	size_t	len = 5;
	char	*result = ft_substr(s, start, len);
	char	*expected = "world";

	if (strcmp(result, expected) == 0)
	{
		log_test_result("ft_substr", true, 0, 0);
	}
	else
	{
		log_test_result("ft_substr", false, 0, 0);
	}
	free(result);
}

// ft_strjoin.
void	test_ft_strjoin()
{
	const char	*s1 = "Hello, ";
	const char	*s2 = "world!";
	char	*result = ft_strjoin(s1, s2);
	const char	*expected = "Hello, world!";
	size_t	result_len = strlen(result);
	size_t	expected_len = strlen(expected);
	
	if (result_len == expected_len && strcmp(result, expected) == 0)
	{
		log_test_result("ft_strjoin", true, expected_len, result_len);
	}
	else
	{
		log_test_result("ft_strjoin", false, expected_len, result_len);
	}
	free(result);
}

// ft_strtrim.
void	test_ft_strtrim()
{
	const char	*s = "   Hello, world!   ";
	const char	*set = " ";
	char	*result = ft_strtrim(s, set);
	const char	*expected = "Hello, world!";

	if (strcmp(result, expected) == 0)
	{
		log_test_result("ft_strtrim", true, strlen(expected), strlen(result));
	}
	else
	{
		log_test_result("ft_strtrim", false, strlen(expected), strlen(result));
	}
	free(result);
}

// ft_putendl_fd.
void	test_ft_putendl_fd()
{	
	int	fd = open("ft_putendl_fd_test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	char	*s = "Hello, world!";
	ft_putendl_fd(s, fd);
	close(fd);
	fd = open("ft_putendl_fd_test.txt", O_RDONLY);
	char	buffer[100];
	ssize_t	bytes_read = read(fd, buffer, sizeof(buffer));
	close(fd);
	if (bytes_read == (ssize_t)strlen(s) + 1 && strcmp(buffer, s) == 0)
	{
		log_test_result("ft_putendl_fd", true, 0, 0);
	}
	else
	{
		log_test_result("ft_putendl_fd", false, 0, 0);
	}
	remove("ft_putendl_fd_test.txt");
}

// ft_putchar_fd.
void	test_ft_putchar_fd()
{
	int	fd = open("ft_putchar_fd_test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	char	c = 'A';
	ft_putchar_fd(c, fd);
	close(fd);
	fd = open("ft_putchar_fd_test.txt", O_RDONLY);
	char	buffer[100];
	ssize_t	bytes_read = read(fd, buffer, sizeof(buffer));
	close(fd);
	if (bytes_read == 1 && buffer[0] == c)
	{
		log_test_result("ft_putchar_fd", true, 0, 0);
	}
	else
	{
		log_test_result("ft_putchar_fd", false, 0, 0);
	}
	remove("ft_putchar_fd_test.txt");
}

// ft_putnbr_fd.
void	test_ft_putnbr_fd()
{	
	int	fd = open("ft_putnbr_fd_test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	int	n = 12345;
	ft_putnbr_fd(n, fd);
	close(fd);
	fd = open("ft_putnbr_fd_test.txt", O_RDONLY);
	char	buffer[100];
	ssize_t	bytes_read = read(fd, buffer, sizeof(buffer));
	close(fd);
	char	expected_output[] = "12345";
	if (bytes_read == (ssize_t)strlen(expected_output) && strcmp(buffer, expected_output) == 0)
	{
		log_test_result("ft_putnbr_fd", true, 0, 0);
	}
	else
	{
		log_test_result("ft_putnbr_fd", false, 0, 0);
	}
	remove("ft_putnbr_fd_test.txt");
}

// ft_putstr_fd.
void	test_ft_putstr_fd()
{
	int	fd = open("ft_putstr_fd_test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	char	*s = "Hello, world!";
	ft_putstr_fd(s, fd);
	close(fd);
	fd = open("ft_putstr_fd_test.txt", O_RDONLY);
	char	buffer[100];
	ssize_t	bytes_read = read(fd, buffer, sizeof(buffer));
	close(fd);
	if (bytes_read == (ssize_t)strlen(s) && strcmp(buffer, s) == 0)
	{
		log_test_result("ft_putstr_fd", true, 0, 0);
	}
	else
	{
		log_test_result("ft_putstr_fd", false, 0, 0);
	}
	remove("ft_putstr_fd_test.txt");
}

// ft_striteri.
void	test_striteri_aux(unsigned int index, char *c)
{
	*c = *c + index;
}

void	test_ft_striteri()
{
	char	s[] = "Hello";
	void (*aux)(unsigned int, char*) = &test_striteri_aux;
	
	ft_striteri(s, aux);
	if (strcmp(s, "Hfnos") == 0)
	{
		 log_test_result("ft_striteri", true, 0, 0);
	}
	else
	{	
		log_test_result("ft_striteri", false, 0, 0);
	}
}

// ft_strmapi.
char	uppercase_map(unsigned int index, char c)
{
	(void)index; 

	if (ft_isalpha(c))
	{
		return (ft_toupper(c));
	}
	return (c);
}

void	test_ft_strmapi()
{
	const char	*s = "Hello, world!";
	char (*map_function)(unsigned int, char) = &uppercase_map;
	char	*result = ft_strmapi(s, map_function);
	char	expected[] = "HELLO, WORLD!";
	
	if (strcmp(result, expected) == 0)
	{
		log_test_result("ft_strmapi", true, strlen(expected), strlen(result));
	}
	else
	{
		log_test_result("ft_strmapi", false, strlen(expected), strlen(result));
	}
	free(result);
}

// ft_itoa.
void	test_ft_itoa()
{
	int	n = -12345;
	char	*result = ft_itoa(n);
	char	*expected = "-12345";

	if (strcmp(result, expected) == 0)
	{
		log_test_result("ft_itoa", true, 0, 0);
	}
	else
	{
		log_test_result("ft_itoa", false, 0, 0);
	}
	free(result);
}

// ft_split.
void	test_ft_split()
{
	const char	*s = "This is a test string";
	char	**result = ft_split(s, ' ');
	char	*expected[] = {"This", "is", "a", "test", "string", NULL};
	int	i = 0;

	while (result[i] != NULL || expected[i] != NULL)
	{
		if (strcmp(result[i], expected[i]) != 0)
		{
			log_test_result("ft_split", false, 0, 0);
			free(result[i]);
			break;
		}
		i++;
	}
	if (result[i] == NULL && expected[i] == NULL)
	{
		log_test_result("ft_split", true, 0, 0);
	}
	for (int j = 0; result[j] != NULL; j++)
	{
		free(result[j]);
	}
	free(result);
}

// Bonus functions.
/*
// ft_lstnew.
void	test_ft_lstnew()
{
	int	data1 = 42;
	t_list	*node1 = ft_lstnew(&data1);
	int	data2 = 123;
	t_list	*node2 = ft_lstnew(&data2);
	char	*data3 = "Hello, World!";
	t_list	*node3 = ft_lstnew(data3);
	
	if (node1 != NULL && *(int *)(node1->content) == data1 &&
        node2 != NULL && *(int *)(node2->content) == data2 &&
        node3 != NULL && strcmp((char *)(node3->content), data3) == 0)
	{
		log_test_result("ft_lstnew", true, 0, 0);
	}
	else
	{
		log_test_result("ft_lstnew", false, 0, 0);
	}
}


// ft_lstadd_front.
void	test_ft_lstadd_front()
{
	t_list	*list = NULL;
	t_list	*node1 = ft_lstnew(strdup("First"));
	t_list	*node2 = ft_lstnew(strdup("Second"));
	
	ft_lstadd_front(&list, node2);
	ft_lstadd_front(&list, node1);
	t_list	*current = list;
	while (current)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	const char	*expected[] = {"First", "Second"};
	const char	*result[] = {list->content, list->next->content};
	bool	test_passed = true;
	for (int i = 0; i < 2; i++)
	{
		if (strcmp(expected[i], result[i]) != 0)
		{
			test_passed = false;
			break;
		}
	}
	log_test_result("ft_lstadd_front", test_passed, expected, result);
	ft_lstclear(&list, free);
}

// ft_lstsize.
void	test_ft_lstsize()
{
	t_list	*list = NULL;
	ft_lstadd_front(&list, ft_lstnew("First"));
	ft_lstadd_front(&list, ft_lstnew("Second"));
	ft_lstadd_front(&list, ft_lstnew("Third"));
	int	size = ft_lstsize(list);
	int	expected = 3;
	int	result = size;
	bool	test_passed = (size == expected);
	const char	*expected_str = test_passed ? "Size is correct." : "Size is incorrect.";
	const char	*result_str = test_passed ? "Size is correct." : "Size is incorrect.";

	log_test_result("ft_lstsize", test_passed, expected_str, result_str);
	ft_lstclear(&list, NULL);
}

// ft_lstlast.
void	test_ft_lstlast()
{
	t_list	*list = NULL;
	ft_lstadd_back(&list, ft_lstnew("First"));
	ft_lstadd_back(&list, ft_lstnew("Second"));
	ft_lstadd_back(&list, ft_lstnew("Third"));
	t_list	*last_node = ft_lstlast(list);
	const char	*expected = "Third";
	const char	*result = NULL;
	bool	test_passed = false;
	
	if (last_node)
	{
		result = (char *)last_node->content;
		if (strcmp(expected, result) == 0)
		{
			test_passed = true;
		}
	}
	else
	{
		printf("List is empty.\n");
	}
	const char	*expected_str = test_passed ? expected : "List is empty.";
	const char	*result_str = result ? result : "List is empty.";
	log_test_result("ft_lstlast", test_passed, expected_str, result_str);
	ft_lstclear(&list, NULL);
}

// ft_lstadd_back.
void    test_ft_lstadd_back()
{
        t_list  *list = NULL;
        t_list  *node1 = ft_lstnew(strdup("First"));
        t_list  *node2 = ft_lstnew(strdup("Second"));

        ft_lstadd_back(&list, node1);
        ft_lstadd_back(&list, node2);
         t_list *current = list;
        while (current)
        {
                printf("%s\n", (char *)current->content);
                current = current->next;
        }
        const char    *expected[] = {"First", "Second"};
        const char    *result[] = {list->content, list->next->content};
        bool    test_passed = true;
        for (int i = 0; i < 2; i++)
        {
                if (strcmp(expected[i], result[i]) != 0)
                {
                        test_passed = false;
                        break;
                }
        }
        log_test_result("ft_lstadd_back", test_passed, sizeexpected, result);
        ft_lstclear(&list, free);
}

// ft_lstdelone.
void	test_ft_lstdelone()
{
	t_list	*node = ft_lstnew(strdup("Hello, World!"));
	const char	*expected[] = { "Node Content Before Deletion: \"Hello, World!\"", "Node Deleted." };
	const char	*result[2];
	bool	test_passed = false;

	if (node)
	{
		result[0] = (char *)malloc(strlen((char *)node->content) + 1);
		strcpy(result[0], (char *)node->content);
		printf("%s\n", expected[0]);
		ft_lstdelone(node, delete_string);
		if (node == NULL)
		{
			result[1] = "Node Deleted.";
			test_passed = true;
		}
		else
		{
			result[1] = "Node Not Deleted.";
		}
	}
	else
	{
		result[0] = "Failed to create a linked list node.";
		result[1] = "Node Not Deleted.";
	}
	log_test_result("ft_lstdelone", test_passed, expected, result);
}

// ft_lstclear.
void	test_ft_lstclear()
{
	t_list	*list = NULL;

	ft_lstadd_back(&list, ft_lstnew(strdup("First")));
	ft_lstadd_back(&list, ft_lstnew(strdup("Second")));
	ft_lstadd_back(&list, ft_lstnew(strdup("Third")));
	t_list	*current = list;
	while (current)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	ft_lstclear(&list, delete_string);
	bool	list_cleared = (list == NULL);
	const char	*expected[] = { "List Cleared." };
	const char	*result[] = { list_cleared ? "List Cleared." : "List Not Cleared." };
	bool	test_passed = list_cleared;
	log_test_result("ft_lstclear", test_passed, expected, result);
}

// ft_lstiter.
void	test_ft_lstiter()
{
	t_list	*list = NULL;
	ft_lstadd_back(&list, ft_lstnew("First"));
	ft_lstadd_back(&list, ft_lstnew("Second"));
	ft_lstadd_back(&list, ft_lstnew("Third"));
	const char	*expected[] = { "First", "Second", "Third" };
	const char	*result[3];
	bool	test_passed = true;
	
	void	capture_content(void *content)
	{
		static int	index = 0;
		result[index++] = (char *)content;
	}
	ft_lstiter(list, capture_content);
	for (int i = 0; i < 3; i++)
	{
		if (strcmp(expected[i], result[i]) != 0)
		{
			test_passed = false;
			break;
		}
	}
	log_test_result("ft_lstiter", test_passed, expected, result);
	ft_lstclear(&list, NULL);
}

// ft_lstmap.
void	test_ft_lstmap()
{
	t_list	*list = NULL;
	for (int i = 1; i <= 5; i++)
	{
		int	*num = (int *)malloc(sizeof(int));
		if (num)
		{
			*num = i;
			ft_lstadd_back(&list, ft_lstnew(num));
		}
	}
	t_list	*new_list = ft_lstmap(list, double_int, delete_int);
	int	expected[] = { 2, 4, 6, 8, 10 };
	int	result[5];
	bool	test_passed = true;
	t_list	*current = list;
	int	index = 0;
	while (current)
	{
		int	*num = (int *)current->content;
		printf("%d ", *num);
		result[index++] = *num;
		current = current->next;
	}
	printf("\n");
	printf("New List (Doubled): ");
	current = new_list;
	index = 0;
	while (current)
	{
		int	*num = (int *)current->content;
		printf("%d ", *num);
		(*num != expected[index])
		{
			test_passed = false;
		}
		index++;
		current = current->next;
		}
		printf("\n");
	const char	*expected_str = test_passed ? "All elements doubled correctly." : "Some elements not doubled correctly.";
	const char	*result_str = test_passed ? "All elements doubled correctly." : "Some elements not doubled correctly.";
	log_test_result("ft_lstmap", test_passed, expected_str, result_str);
	ft_lstclear(&list, delete_int);
	ft_lstclear(&new_list, delete_int);
}
*/

int     main()
{
	test_ft_strlcat();
	test_ft_strlen();
	test_ft_strlcpy();
	test_ft_isalpha();
	test_ft_isalnum();
	test_ft_isdigit();
	test_ft_isascii();
	test_ft_isprint();
	test_ft_strncmp();
	test_ft_memset();
	test_ft_bzero();
	test_ft_memcpy();
	test_ft_memmove();
	test_ft_toupper();
	test_ft_tolower();
	test_ft_strchr();
	test_ft_strrchr();
	test_ft_strnstr();
	test_ft_memchr();
	test_ft_memcmp();
	test_ft_atoi();
	test_ft_calloc();
	test_ft_strdup();
	test_ft_substr();
	test_ft_strjoin();
	test_ft_strtrim();
	test_ft_putendl_fd();
	test_ft_strlen();
	test_ft_strlcpy();
	test_ft_putchar_fd();
	test_ft_putnbr_fd();
	test_ft_putstr_fd();
	test_ft_striteri();
	test_ft_strmapi();
	test_ft_itoa();
	test_ft_split();
	//test_ft_lstnew();
	//test_ft_lstadd_front();
	//test_ft_lstsize();
	//test_ft_lstlast();
	//test_ft_lstadd_back();
	//test_ft_lstdelone();
	//test_ft_lstclear();
	//test_ft_lstiter();
	//test_ft_lstmap();
	return 0;
}
