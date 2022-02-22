# ********************************************* #
#                                               #
#                      :|:||||||:|||:|:||:||::  #
#  Makefile            |:|:|::|::||||::||:|:::  #
#                      |::::|||:::||::::::|:||  #
#                                               #
#                                               #
#  C20220222151745 |:|:::                       #
#  U20220222162437 :::|||                       #
#                                               #
# ********************************************* #

NAME	=	api_server
SRCS	=	api_server.c
HEAD	=	Makefile
SHELL	=	/bin/sh
CC		=	cc -L../libft
CCFLAGS	=	-Wall -Werror -Wextra -g
CCLINKS	=	-L../libft -lft
OBJS	=	$(SRCS:.c=.o)
VAL		=	valgrind
VALFLAG	=	--tool=memcheck \
			--leak-check=full \
			--show-leak-kinds=all \
			--track-origins=yes \
			--show-reachable=yes
all:		libft $(NAME)
libft:
	cd ../libft && make && cd -
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
	$(VAL) $(VALFLAG) ./$(NAME)
t:			all
	./$(NAME)
v:			all
	$(VAL) ./$(NAME)
start:		all
	./$(NAME) &
stop:
	-pkill api_server
