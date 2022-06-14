# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabid <mabid@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/01 13:46:38 by morikumo          #+#    #+#              #
#    Updated: 2022/06/14 15:44:56 by mabid            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS 	= srcs/pipex.c srcs/utils.c srcs/error.c libft/ft_strchr.c \
		  libft/ft_putstr_fd.c libft/ft_split.c libft/ft_putendl_fd.c \
		  libft/ft_strjoin.c libft/ft_strnstr.c libft/ft_strlen.c	\

OBJS			= $(SRCS:.c=.o)

NAME			= pipex

CFLAGS			= -Wall -Wextra -Werror

RM				= rm -f

CC				= gcc

AR				= ar rcs

.c.o:
				@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) 

$(NAME):		$(OBJS)
				@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L.
				@echo -ne '\033[32m                            (0%)\r'
				@sleep 0.2
				@echo -ne '#####                      (33%)\r'
				@sleep 0.2
				@echo -ne '#############              (66%)\r'
				@sleep 0.2
				@echo -ne '#######################   (100%)\r'
				@echo -ne '\n'
				@echo "\033[33mC'est compilé !"

all:			$(NAME)

clean:
				@$(RM) $(OBJS)
				@echo -ne '\033[36m#######################   (100%)\r'
				@sleep 0.2
				@echo -ne '#############              (66%)\r'
				@sleep 0.2
				@echo -ne '#####                      (33%)\r'
				@sleep 0.2
				@echo -ne '                            (0%)\r'
				@echo -ne '\n'
				@echo "\033[33mC'est clean !"

fclean:			clean
				@$(RM) $(NAME) 
				@echo -ne '\033[34m#######################   (100%)\r'
				@sleep 0.2
				@echo -ne '#############              (66%)\r'
				@sleep 0.2
				@echo -ne '#####                      (33%)\r'
				@sleep 0.2
				@echo -ne '                            (0%)\r'
				@echo -ne '\n'
				@echo "\033[33mC'est fclean !"

re:				fclean all

normin:			
	norminette	./srcs ./libft pipex.h

wnormin: 		
	watch norminette	./srcs ./libft pipex.h

.PHONY:	all clean fclean c.o re
