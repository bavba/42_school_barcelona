# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aricalle <aricalle@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/31 16:10:16 by aricalle          #+#    #+#              #
#    Updated: 2023/11/28 22:38:14 by aricalle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
NAME = libftprintf.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar -rcs
RM = rm -f
MKDIR = mkdir -p

# Sources
SRCS = ft_printf.c \
       ft_conversion_csdi.c \
	   ft_conversion_puxX.c

# Temporary directories
OBJS_DIR = obj
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
DEPS_DIR = dep
DEPS = $(addprefix $(DEPS_DIR)/, $(SRCS:.c=.d))

# Test source file
TEST_SRC = test.c

# Test target
TEST_TARGET = test

# Make rules
.PHONY: all clean fclean re test

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR) $(DEPS_DIR)
	$(CC) $(CFLAGS) -MMD -c $< -o $@

-include $(DEPS)

$(OBJS_DIR) $(DEPS_DIR):
	$(MKDIR) $@

test: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_SRC) $(NAME)
	$(CC) $(CFLAGS) $^ -o $@ -L. -lftprintf

clean:
	$(RM) $(OBJS)
	$(RM) -r $(OBJS_DIR) $(DEPS_DIR)
	$(RM) $(TEST_TARGET)

fclean: clean
	$(RM) $(NAME)

re: fclean all