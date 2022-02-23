/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   api_client.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-capu <fde-capu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:45:14 by fde-capu          #+#    #+#             */
/*   Updated: 2022/02/23 15:49:01 by fde-capu         ###   ########.fr       */
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

int die(char *message, int return_code, char **to_free)
{
	printf("%s\n", message);
	free(*to_free);
	return return_code;
}

bool validate(int argc, char **argv, char **address, int *port)
{
	char *valid_arguments_regex_pipesv = "\\d\\d?\\d?\\.\\d\\d?\\d?\\.\\d\\d?\\d?\\.\\d\\d?\\d?:\\d+";
	if (!validate_args_regex(argc, argv, 2, 2, valid_arguments_regex_pipesv))
		return false;

	char **addr_and_port = ft_split(argv[1], ':');
	*address = ft_str(addr_and_port[0]);
	*port = ft_atoi(addr_and_port[1]);
	ft_strfree2d(addr_and_port);
	(void)address;
	(void)port;
	return true;
}

int main(int argc, char **argv)
{
	char *address;
	int port;

	if (!validate(argc, argv, &address, &port))
		return die(ERROR INVALID_ARGUMENTS, 42, &address);

	printf("address: %s, port: %i\n", address, port);

	int client_socket;
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket == -1)
		return die(ERROR SOCKET_CREATION_FAIL, 42, &address);

	struct sockaddr_in remote_address;
	remote_address.sin_family = AF_INET;
	remote_address.sin_port = htons(port);

	if (inet_aton(address, (struct in_addr *)&remote_address.sin_addr.s_addr) == 0)
		return die(ERROR INVALID_ADDRESS, 42, &address);

	if (connect(client_socket, (struct sockaddr *)&remote_address, sizeof(remote_address)) == -1)
		return die(ERROR CONNECTION_FAILED, 42, &address);

	char request[] = "GET / HTTP/1.1\n\n";
	char response[4096];

	if (send(client_socket, request, sizeof(request), 0) == -1)
		return die(ERROR SEND_FAILED, 42, &address);

	if (recv(client_socket, &response, sizeof(response), 0) == -1)
		return die(ERROR RECV_FAILED, 42, &address);

	printf("Got from server:\n%s", response);

	if (close(client_socket) == -1)
		return die(ERROR CLOSE_SOCKET_FAILED, 42, &address);

	return 0;
}
