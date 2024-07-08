# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tibarbos <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/07 16:57:08 by tibarbos          #+#    #+#              #
#    Updated: 2023/05/23 17:17:40 by tibarbos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar -rcs
RM = rm -rf
SRC = central.c death_star.c \
      n_utils_1.c n_utils_2.c n_utils_3.c \
      n_specs_1.c n_specs_2.c n_hex.c n_flag.c \
      pain_exist.c pain_size.c pain_checks.c p_flag.c \
      ip_specs_1.c ip_specs_2.c ip_specs_u.c\
      p_specs_r1.c p_specs_r2.c p_specs_l1.c p_specs_l2.c \
      ft_itoa.c ft_long_itoa.c ft_hbx_itoa.c ft_hx_itoa.c ft_lhx_itoa.c
OBJS = ${SRC:.c=.o}

#BONUS = ft_printf.c ft_utils_1.c ft_utils_2.c \
#	ft_specs_1.c ft_specs_2.c ft_hex.c ft_flag.c;
#B_OBJS = ${BONUS:.c=.o}

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

all: $(NAME)

bonus: $(OBJS)
	$(AR) $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
