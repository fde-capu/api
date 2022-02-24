/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   api_server.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-capu <fde-capu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:45:15 by fde-capu          #+#    #+#             */
/*   Updated: 2022/02/23 18:24:54 by fde-capu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "api_server.h"

int die(char *message, int return_code)
{
	printf("%s\n", message);
	return return_code;
}

int main(int argc, char **argv)
{
	char *reg = "\\d+";
	if (!validate_args_regex(argc, argv, 0, 3, reg))
		return die(ERROR INVALID_ARGUMENTS, 1);

//	FILE *html_data;
//	html_data = fopen("json-sample.json", "r");
//	char response_data[MAX_RESPONSE];
//	fgets(response_data, 1024, html_data);

	char *response_data = ft_str("Hello, world!");
	char *http_header = ft_str("HTTP/1.1 200 OK\nConnection: close\nContent-Length: 13\n\n");

	http_header = ft_strcatx(http_header, response_data);

	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(ft_atoi(argv[1]));
	server_address.sin_addr.s_addr = INADDR_ANY;
	bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
	listen(server_socket, 1);
	int client_socket;
	while (1)
	{
		client_socket = accept(server_socket, NULL, NULL);
		printf(SERVER_SIGN "--> %s <--\n", http_header); fflush(stdout);
		send(client_socket, http_header, strlen(http_header), 0);
		close(client_socket);
	}
	return 0;
}
