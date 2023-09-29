# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aricalle <aricalle@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/28 16:04:35 by aricalle          #+#    #+#              #
#    Updated: 2023/09/14 12:01:22 by aricalle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rc
RM = rm -f

SRCS_C += ft_strlen.c \
		 ft_strlcat.c \
		 ft_strlcpy.c \
		 ft_isalpha.c \
		 ft_isalnum.c \
		 ft_isdigit.c \
		 ft_isascii.c \
		 ft_isprint.c \
		 ft_strncmp.c \
		 ft_memset.c \
		 ft_bzero.c \
		 ft_memcpy.c \
		 ft_memmove.c \
		 ft_toupper.c \
		 ft_tolower.c \
		 ft_strchr.c \
		 ft_strrchr.c \
		 ft_strnstr.c \
		 ft_memchr.c \
		 ft_memcmp.c \
		 ft_atoi.c \
		 ft_calloc.c \
		 ft_strdup.c \
		 ft_substr.c \
		 ft_strjoin.c \
		 ft_strtrim.c \
		 ft_putendl_fd.c \
		 ft_putchar_fd.c \
		 ft_putnbr_fd.c \
		 ft_putstr_fd.c \
		 ft_striteri.c \
		 ft_strmapi.c \
		 ft_itoa.c \
		 ft_split.c

BONUS_SRCS_C += ft_lstnew_bonus.c \
			   ft_lstadd_front_bonus.c \
			   ft_lstsize_bonus.c \
			   ft_lstlast_bonus.c \
			   ft_lstadd_back_bonus.c \
			   ft_lstdelone_bonus.c \
			   ft_lstclear_bonus.c \
			   ft_lstiter_bonus.c \
			   ft_lstmap_bonus.c

OBJS = $(SRCS_C:.c=.o)

BONUS_OBJ = $(BONUS_SRCS_C:.c=.o)

DEPS = $(SRCS_C:.c=.d)

BONUS_DEPS = $(BONUS_SRCS_C:.c=.d)

.PHONY: all 

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@   

-include $(DEPS)

.PHONY: clean

clean:
	$(RM) $(OBJS) $(BONUS_OBJ) $(DEPS) $(BONUS_DEPS)
	#rm .bonus

.PHONY: fclean

fclean: clean
	$(RM) $(NAME)

.PHONY: re

re: fclean all

.PHONY: bonus

bonus:
	$(MAKE) SRCS_C="$(SRCS_C) $(BONUS_SRCS_C)"
	
//bonus: .bonus
	
//.bonus: $(BONUS_OBJ) $(OBJS)
	#$(AR) $(NAME) $(BONUS_OBJ)
	#touch .bonus

.PHONY: rebonus

rebonus: fclean bonus
