# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 14:55:08 by tibarbos          #+#    #+#              #
#    Updated: 2024/08/28 12:34:37 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= libft.a

# Compilation && Tools
CC= cc -c
AR= ar -rcs
CFLAGS= -Wall -Wextra -Werror
RM= rm -rf

# Output colors
RED= \e[31m
GREEN= \e[32m
BLUE= \e[34m
WHITE= \e[37m

# Source && Object Files
SRCL= ./lib/ft_atoi.c ./lib/ft_bzero.c ./lib/ft_calloc.c \
	./lib/ft_isalnum.c ./lib/ft_isalpha.c ./lib/ft_isascii.c \
	./lib/ft_isdigit.c ./lib/ft_isprint.c ./lib/ft_itoa.c \
	./lib/ft_memchr.c ./lib/ft_memcmp.c ./lib/ft_memcpy.c \
	./lib/ft_memmove.c ./lib/ft_memset.c ./lib/ft_putchar_fd.c \
	./lib/ft_putendl_fd.c ./lib/ft_putnbr_fd.c ./lib/ft_putstr_fd.c \
	./lib/ft_split.c ./lib/ft_strchr.c ./lib/ft_strdup.c \
	./lib/ft_striteri.c ./lib/ft_strjoin.c ./lib/ft_strlcat.c \
	./lib/ft_strlcpy.c ./lib/ft_strlen.c ./lib/ft_strmapi.c \
	./lib/ft_strncmp.c ./lib/ft_strnstr.c ./lib/ft_strrchr.c \
	./lib/ft_strtrim.c ./lib/ft_substr.c ./lib/ft_tolower.c \
	./lib/ft_toupper.c ./lib/ft_lstnew.c ./lib/ft_lstadd_front.c \
	./lib/ft_lstsize.c ./lib/ft_lstlast.c ./lib/ft_lstadd_back.c \
	./lib/ft_lstdelone.c ./lib/ft_lstclear.c ./lib/ft_lstiter.c \
	./lib/ft_lstmap.c

SRCG= ./getnext/get_next_line_bonus.c \
	./getnext/get_next_line_utils_bonus.c

SRCP= ./print/central.c ./print/death_star.c \
	./print/n_utils_1.c ./print/n_utils_2.c ./print/n_utils_3.c \
	./print/n_specs_1.c ./print/n_specs_2.c \
	./print/n_hex.c ./print/n_flag.c \
	./print/pain_exist.c ./print/pain_size.c \
	./print/pain_checks.c ./print/p_flag.c \
	./print/ip_specs_1.c ./print/ip_specs_2.c ./print/ip_specs_u.c \
	./print/p_specs_r1.c ./print/p_specs_r2.c \
	./print/p_specs_l1.c ./print/p_specs_l2.c \
	./print/ft_itoa.c ./print/ft_long_itoa.c ./print/ft_hbx_itoa.c \
	./print/ft_hx_itoa.c ./print/ft_lhx_itoa.c

OBJDIR= ./obj
OBJL= $(SRCL:%.c=$(OBJDIR)/%.o)
OBJG= $(SRCG:%.c=$(OBJDIR)/%.o)
OBJP= $(SRCP:%.c=$(OBJDIR)/%.o)
AOBJ= $(OBJL) $(OBJG) $(OBJP)

# Rules
.PHONY: all clean fclean re

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(AOBJ)
	@$(AR) $(NAME) $(AOBJ)

all: $(NAME)

clean:
	@$(RM) $(OBJDIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all