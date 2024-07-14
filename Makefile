# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/18 17:44:12 by marvin            #+#    #+#              #
#    Updated: 2024/07/14 22:30:59 by tibarbos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name && Utilities
NAME= minishell
RM= rm -rf

# Compiler && Flags
CC= cc
CFLAGS= -Wall -Wextra -Werror

# Source && Object Files
SRC_P= ./src/parser/p_1.c ./src/parser/p_1a.c \
	./src/parser/p_2.c ./src/parser/p_2a.c ./src/parser/p_2b.c \
	./src/parser/p_2c.c ./src/parser/p_2d.c \
	./src/parser/p_2_utils.c \
	./src/parser/p_3.c ./src/parser/p_3a.c ./src/parser/p_3b.c \
	./src/parser/p_3_utils.c \
	./src/parser/p_4.c \
	./src/parser/p_5.c ./src/parser/p_5a.c \
	./src/parser/p_6.c ./src/parser/p_6a.c ./src/parser/p_6b.c
OBJ_P= ${SRC_P:.c=.o}

SRC_E= ./src/executor/e_main.c ./src/executor/e_loop.c \
	./src/executor/e_action.c ./src/executor/e_close.c \
	./src/executor/e_envs.c ./src/executor/e_redirs.c \
	./src/executor/e_utils.c ./src/executor/e_launch.c
OBJ_E= ${SRC_E:.c=.o}

SRC_B= ./src/builtin/blt_central.c ./src/builtin/cd.c \
	./src/builtin/echo.c ./src/builtin/env.c \
	./src/builtin/export.c \
	./src/builtin/pwd.c ./src/builtin/unset.c \
	./src/builtin/export_sup.c

OBJ_B= ${SRC_B:.c=.o}

SRC_M= ./src/free.c ./src/signals.c ./src/main.c \
	./src/prints.c ./src/exit_mini.c ./src/sighandlers.c \
	./src/main_sup.c
OBJ_M= ${SRC_M:.c=.o}

OBJ= $(OBJ_P) $(OBJ_E) $(OBJ_B) $(OBJ_M)

# Include Libraries
LIB_FT= -L./mylib -lft
LIB_READ= -lreadline
LIBS= $(LIB_FT) $(LIB_READ)

# Rules
$(NAME): $(OBJ)
	@cd ./mylib && make
	@$(CC) -g -v $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

all: $(NAME)
	@cd ./mylib && make all

clean:
	@cd ./mylib && make clean
	@$(RM) $(OBJ)

fclean:	clean
	@cd ./mylib && make fclean
	@$(RM) $(NAME)

re: fclean all
	@cd ./mylib && make re

test: re
	@make clean
	@clear
	@./$(NAME)

#testing leaks
leaks: leaks.supp
	valgrind --suppressions=leaks.supp --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes --track-origins=yes ./minishell

leaks.supp:
	@echo "{" > leaks.supp
	@echo "    leak leaks" >> leaks.supp
	@echo "    Memcheck:Leak" >> leaks.supp
	@echo "    ..." >> leaks.supp
	@echo "    fun:leaks" >> leaks.supp
	@echo "}" >> leaks.supp
	@echo "{" >> leaks.supp
	@echo "    leak add_history" >> leaks.supp
	@echo "    Memcheck:Leak" >> leaks.supp
	@echo "    ..." >> leaks.supp
	@echo "    fun:add_history" >> leaks.supp
	@echo "}" >> leaks.supp
# readline
	@echo "{" >> leaks.supp
	@echo "		leak malloc_readline" >> leaks.supp
	@echo "		Memcheck:Leak" >> leaks.supp
	@echo "		fun:malloc" >> leaks.supp
	@echo "		..." >> leaks.supp
	@echo "		fun:readline" >> leaks.supp
	@echo "}" >> leaks.supp
	@echo "{" >> leaks.supp
	@echo "		leak calloc_readline" >> leaks.supp
	@echo "		Memcheck:Leak" >> leaks.supp
	@echo "		fun:calloc" >> leaks.supp
	@echo "		..." >> leaks.supp
	@echo "		fun:readline" >> leaks.supp
	@echo "}" >> leaks.supp
	@echo "{" >> leaks.supp
	@echo "		leak realloc_readline" >> leaks.supp
	@echo "		Memcheck:Leak" >> leaks.supp
	@echo "		fun:realloc" >> leaks.supp
	@echo "		..." >> leaks.supp
	@echo "		fun:readline" >> leaks.supp
	@echo "}" >> leaks.supp
# ls
	@echo "{" >> leaks.supp
	@echo "		leak malloc_ls" >> leaks.supp
	@echo "		Memcheck:Leak" >> leaks.supp
	@echo "		fun:malloc" >> leaks.supp
	@echo "		..." >> leaks.supp
	@echo "		obj:/usr/bin/ls" >> leaks.supp 
	@echo "		..." >> leaks.supp
	@echo "		fun:(below main)" >> leaks.supp
	@echo "}" >> leaks.supp
	@echo "{" >> leaks.supp
	@echo "		leak realloc_ls" >> leaks.supp
	@echo "		Memcheck:Leak" >> leaks.supp
	@echo "		fun:realloc" >> leaks.supp
	@echo "		obj:/usr/bin/ls" >> leaks.supp 
	@echo "		..." >> leaks.supp
	@echo "		fun:(below main)" >> leaks.supp
	@echo "}" >> leaks.supp
# grep
	@echo "{" >> leaks.supp
	@echo "		leak malloc_grep" >> leaks.supp
	@echo "		Memcheck:Leak" >> leaks.supp
	@echo "		fun:malloc" >> leaks.supp
	@echo "		..." >> leaks.supp
	@echo "		obj:/usr/bin/grep" >> leaks.supp 
	@echo "		..." >> leaks.supp
	@echo "		fun:(below main)" >> leaks.supp
	@echo "}" >> leaks.supp
	@echo "{" >> leaks.supp
	@echo "		leak realloc_grep" >> leaks.supp
	@echo "		Memcheck:Leak" >> leaks.supp
	@echo "		fun:realloc" >> leaks.supp
	@echo "		obj:/usr/bin/grep" >> leaks.supp 
	@echo "		..." >> leaks.supp
	@echo "		fun:(below main)" >> leaks.supp
	@echo "}" >> leaks.supp
	@echo "{" >> leaks.supp
	@echo "		leak calloc_grep" >> leaks.supp
	@echo "		Memcheck:Leak" >> leaks.supp
	@echo "		fun:calloc" >> leaks.supp
	@echo "		..." >> leaks.supp
	@echo "		obj:/usr/bin/grep" >> leaks.supp 
	@echo "		..." >> leaks.supp
	@echo "		fun:(below main)" >> leaks.supp
	@echo "}" >> leaks.supp
# cat
	@echo "{" >> leaks.supp
	@echo "		leak memalign_cat" >> leaks.supp
	@echo "		Memcheck:Leak" >> leaks.supp
	@echo "		fun:memalign" >> leaks.supp
	@echo "		obj:/usr/bin/cat" >> leaks.supp
	@echo "		fun:(below main)" >> leaks.supp
	@echo "}" >> leaks.supp
	@echo "{" >> leaks.supp
	@echo "		leak malloc_cat" >> leaks.supp
	@echo "		Memcheck:Leak" >> leaks.supp
	@echo "		fun:malloc" >> leaks.supp
	@echo "		..." >> leaks.supp
	@echo "		obj:/usr/bin/cat" >> leaks.supp 
	@echo "		..." >> leaks.supp
	@echo "		fun:(below main)" >> leaks.supp
	@echo "}" >> leaks.supp
#clear
	@echo "{" >> leaks.supp
	@echo "		leak malloc_clear" >> leaks.supp
	@echo "		Memcheck:Leak" >> leaks.supp
	@echo "		fun:malloc" >> leaks.supp
	@echo "		..." >> leaks.supp
	@echo "		obj:/usr/bin/clear" >> leaks.supp 
	@echo "		fun:(below main)" >> leaks.supp
	@echo "}" >> leaks.supp
	@echo "{" >> leaks.supp
	@echo "		leak realloc_clear" >> leaks.supp
	@echo "		Memcheck:Leak" >> leaks.supp
	@echo "		fun:realloc" >> leaks.supp
	@echo "		..." >> leaks.supp
	@echo "		obj:/usr/bin/clear" >> leaks.supp 
	@echo "		fun:(below main)" >> leaks.supp
	@echo "}" >> leaks.supp
	@echo "{" >> leaks.supp
	@echo "		leak calloc_clear" >> leaks.supp
	@echo "		Memcheck:Leak" >> leaks.supp
	@echo "		fun:calloc" >> leaks.supp
	@echo "		..." >> leaks.supp
	@echo "		obj:/usr/bin/clear" >> leaks.supp 
	@echo "		fun:(below main)" >> leaks.supp
	@echo "}" >> leaks.supp
