# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fde-capu <fde-capu@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/23 11:44:36 by fde-capu          #+#    #+#              #
#    Updated: 2022/02/24 19:09:12 by fde-capu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef OUTPUT
.SILENT:
endif

ifdef DAEMON
POST_ARGS =	&
endif

NAME	=	api_server
ARGS	=	8001 $(POST_ARGS)
SRCS	=	api_server.c
HEAD	=	Makefile api_server.h
SHELL	=	/bin/sh
CC		=	cc
CCFLAGS	=	-Wall -Werror -Wextra -g
CCLINKS	=	-L../libft -lft # -Qunused-arguments
OBJS	=	$(SRCS:.c=.o)
VAL		=	valgrind
VALFLAG	=	--tool=memcheck \
			--leak-check=full \
			--show-leak-kinds=all \
			--track-origins=yes \
			--show-reachable=yes
all:		libft $(NAME)
libft:
	cd ../libft && $(MAKE) && cd -
$(NAME):	$(OBJS)
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
	echo "# $(VAL) $(VALFLAG) ./$(NAME) $(ARGS)"
	$(VAL) $(VALFLAG) ./$(NAME) $(ARGS)
t:			all
	echo "# $(NAME) $(ARGS)"
	./$(NAME) $(ARGS)
v:			all
	echo "# $(VAL) ./$(NAME) $(ARGS)"
	$(VAL) ./$(NAME) $(ARGS)
start:		stop all
	echo "# $(NAME) $(ARGS)"
	./$(NAME) $(ARGS)
stop:
	-pkill api_server
