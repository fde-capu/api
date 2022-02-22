# ********************************************* #
#                                               #
#                      :|:||||||:|||:|:||:||::  #
#  Makefile            |:|:|::|::||||::||:|:::  #
#                      |::::|||:::||::::::|:||  #
#                                               #
#                                               #
#  C20220222153348 :::::|                       #
#  U20220222162136 ||::::                       #
#                                               #
# ********************************************* #

all:	stop libft api_server api_client
libft:
	cd libft && make
api_server:
	cd server && make
api_client:
	cd client && make
start:	all
	cd server && make start && cd ..
stop:
	cd server && make stop && cd ..
c-test:
	cd client && make t && cd ..
t:	start c-test
clean:
	cd server && make clean
	cd client && make clean
	cd libft && make clean
fclean:
	cd server && make fclean
	cd client && make fclean
	cd libft && make fclean
re:
	cd server && make re
	cd client && make re
	cd libft && make re
