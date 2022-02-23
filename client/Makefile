# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fde-capu <fde-capu@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/23 11:38:52 by fde-capu          #+#    #+#              #
#    Updated: 2022/02/23 14:20:48 by fde-capu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef OUTPUT
.SILENT:
endif

NAME	=	api_client
ARGS	=	0.0.0.0:8001
SRCS	=	api_client.c
HEAD	=	Makefile api_client.h
SHELL	=	/bin/sh
CC		=	cc
CCFLAGS	=	-Wall -Werror -Wextra -g
CCLINKS	=	-L../libft -lft
OBJS	=	$(SRCS:.c=.o)
VAL		=	valgrind
VALFLAG	=	--tool=memcheck \
			--leak-check=full \
			--show-leak-kinds=all \
			--track-origins=yes \
			--show-reachable=yes
all:		$(NAME)
libft:
	cd ../libft && $(MAKE) && cd -
$(NAME):	libft $(OBJS)
	$(CC) $(CCFLAGS) $(OBJS) -o $(NAME) $(CCLINKS)
$(OBJS):	%.o : %.c $(HEAD)
	$(CC) $(CCFLAGS) -o $@ -c $< $(CCLINKS)
clean:
	-rm -f $(OBJS)
fclean:		clean
	-rm -f $(NAME)
re:			fclean all
rt:			re t
vf:			all
	$(VAL) $(VALFLAG) ./$(NAME) $(ARGS)
t:			all
	echo "$(NAME) $(ARGS)"
	./$(NAME) $(ARGS)
v:			all
	$(VAL) ./$(NAME) $(ARGS)
