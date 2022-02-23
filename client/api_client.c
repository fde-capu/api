/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   api_client.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-capu <fde-capu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:45:14 by fde-capu          #+#    #+#             */
/*   Updated: 2022/02/23 14:08:21 by fde-capu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h> // to convert network address
#include "../libft/libft.h"
#include "api_client.h"

int main(int argc, char *argv[])
{
	char *valid_arguments_regex_pipesv = "\\d\\d?\\d?\\.\\d\\d?\\d?\\.\\d\\d?\\d?\\.\\d\\d?\\d?:\\d+";
	if (!validate_args_regex(argc, argv, 2, 2, valid_arguments_regex_pipesv))
		return ft_print2_and_return_int(ERROR, INVALID_ARGUMENTS, 42);

	char **addr_and_port = ft_split(argv[1], ':');
	char *address = addr_and_port[0];
	int port = ft_atoi(addr_and_port[1]);

	int client_socket;
	client_socket = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in remote_address;
	remote_address.sin_family = AF_INET;
	remote_address.sin_port = htons(port);
	inet_aton(address, (struct in_addr *)&remote_address.sin_addr.s_addr);

	connect(client_socket, (struct sockaddr *)&remote_address, sizeof(remote_address));
	char request[] = "GET / HTTP/1.1\n\n";
	char response[4096];

	send(client_socket, request, sizeof(request), 0);
	recv(client_socket, &response, sizeof(response), 0);
	printf("Got from server: %s\n", response);
	close(client_socket);

	ft_strfree2d(addr_and_port);
	return 0;
}
