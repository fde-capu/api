/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   api_client.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-capu <fde-capu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:45:14 by fde-capu          #+#    #+#             */
/*   Updated: 2022/02/27 22:45:12 by fde-capu         ###   ########.fr       */
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

int shell_error(char *message, char **response)
{
	printf("%s\n", message);
	free(*response);
	return 1;
}

int call_server(char *line, char *address, int port)
{
	struct sockaddr_in remote_address;
	char *response = malloc(MAX_RESPONSE);
	int client_socket;

	printf(CLIENT_SIGN " " CLIENT_OUT "%s\n", line);
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket == -1)
		return shell_error(ERROR SOCKET_CREATION_FAIL, &response);
	remote_address.sin_family = AF_INET;
	remote_address.sin_port = htons(port);
	if (inet_aton(address, (struct in_addr *)&remote_address.sin_addr.s_addr) == 0)
		return shell_error(ERROR INVALID_ADDRESS, &response);
	if (connect(client_socket, (struct sockaddr *)&remote_address, sizeof(remote_address)) == -1)
		return shell_error(ERROR CONNECTION_FAILED, &response);
	if (send(client_socket, line, strlen(line), 0) == -1)
		return shell_error(ERROR SEND_FAILED, &response);
	if (recv(client_socket, response, MAX_RESPONSE, 0) == -1)
		return shell_error(ERROR RECV_FAILED, &response);
	if (close(client_socket) == -1)
		return shell_error(ERROR CLOSE_SOCKET_FAILED, &response);
	printf(CLIENT_SIGN " " SERVER_IN "%s\n", response);
	free(response);
	return 0;
}

void shell(char *address, int port)
{
	FILE *stream;
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	printf(CLIENT_SIGN " " SHELL_MODE "\n");
	stream = fdopen(0, "r");
	if (stream == NULL)
		exit(EXIT_FAILURE);
	while ((nread = getline(&line, &len, stream)) != -1)
	{
		if (call_server(line, address, port) != 0)
			break ;
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
	if (call_server("Hi!", address, port) == 0)
		shell(address, port);
	free(address);
	return 0;
}
