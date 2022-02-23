# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fde-capu <fde-capu@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/23 11:45:09 by fde-capu          #+#    #+#              #
#    Updated: 2022/02/23 16:33:53 by fde-capu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef OUTPUT
.SILENT:
endif

all:	libft api_server api_client
libft:
	cd libft && make
api_server:
	cd server && make
api_client:
	cd client && make
start:	stop all
	cd server && make start && cd ..
stop:
	cd server && make stop && cd ..
t:	t-server t-client
t-server:	start
t-client:	c-test
c-test:
	cd client && make t && cd ..
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
