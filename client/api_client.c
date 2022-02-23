/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   api_client.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-capu <fde-capu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:45:14 by fde-capu          #+#    #+#             */
/*   Updated: 2022/02/23 18:00:01 by fde-capu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void shell_error(char *message)
{
	printf("%s\n", message);
	return ;
}

void call_server(char *line, char *address, int port)
{
	struct sockaddr_in remote_address;
	char response[MAX_RESPONSE];
	int client_socket;

	printf(CLIENT_OUT "%s\n", line);
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket == -1)
		return shell_error(ERROR SOCKET_CREATION_FAIL);
	remote_address.sin_family = AF_INET;
	remote_address.sin_port = htons(port);
	if (inet_aton(address, (struct in_addr *)&remote_address.sin_addr.s_addr) == 0)
		return shell_error(ERROR INVALID_ADDRESS);
	if (connect(client_socket, (struct sockaddr *)&remote_address, sizeof(remote_address)) == -1)
		return shell_error(ERROR CONNECTION_FAILED);
	if (send(client_socket, line, strlen(line), 0) == -1)
		return shell_error(ERROR SEND_FAILED);
	if (recv(client_socket, &response, sizeof(response), 0) == -1)
		return shell_error(ERROR RECV_FAILED);
	if (close(client_socket) == -1)
		return shell_error(ERROR CLOSE_SOCKET_FAILED);
	printf(SERVER_IN "%s\n", response);
	return ;
}

void shell(char *address, int port)
{
	FILE *stream;
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	printf(SHELL_MODE "\n");
	stream = fdopen(0, "r");
	if (stream == NULL)
		exit(EXIT_FAILURE);
	while ((nread = getline(&line, &len, stream)) != -1)
	{
		call_server(line, address, port);
		//		fwrite(line, nread, 1, stdout);
	}
	free(line);
	fclose(stream);
	return ;
}

int main(int argc, char **argv)
{
	char *address;
	int port;

	if (!validate(argc, argv, &address, &port))
		return die(ERROR INVALID_ARGUMENTS, 42, &address);

	call_server("HI", address, port);

	shell(address, port);

	return 0;
}
