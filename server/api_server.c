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
		struct sockaddr_in *communication_layer = calloc(1, sizeof(struct sockaddr_in));
		client_socket = accept(server_socket, (struct sockaddr*)&communication_layer, (socklen_t *)&communication_layer->sin_addr.s_addr);
		struct addrinfo hints;
		memset(&hints, 0, sizeof(struct addrinfo));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_DGRAM;
		hints.ai_flags = AI_PASSIVE;
		hints.ai_protocol = 0;
		hints.ai_canonname = NULL;
		hints.ai_addr = NULL;
		hints.ai_next = NULL;
		struct addrinfo *result;
		struct addrinfo *i;
		int s = getaddrinfo(NULL, argv[1], &hints, &result);
		if (s != 0)
		{
			printf(SERVER_SIGN " " ERROR FAILEDADDRINGO);
			return -1; //
			continue ;
		}
		for(i = result; i != NULL; i = i->ai_next)
		{
			char str[INET6_ADDRSTRLEN];
			if (i->ai_addr->sa_family == AF_INET)
			{
				struct sockaddr_in *p = (struct sockaddr_in *)i->ai_addr;
				printf("Connection from: %s\n", inet_ntop(AF_INET, &p->sin_addr, str, sizeof(str)));
			}
			else if (i->ai_addr->sa_family == AF_INET6)
			{
				struct sockaddr_in6 *p = (struct sockaddr_in6 *)i->ai_addr;
				printf("Connection from: %s\n", inet_ntop(AF_INET6, &p->sin6_addr, str, sizeof(str)));
			}
		}

		printf(SERVER_SIGN " Family: %d\n", communication_layer->sin_family);
		printf(SERVER_SIGN " Port: %d\n", ntohs(communication_layer->sin_port));
		printf(SERVER_SIGN " in_addr: %d\n", communication_layer->sin_addr.s_addr);
		printf(SERVER_SIGN "--> %s <--\n", http_header); fflush(stdout);
		send(client_socket, http_header, strlen(http_header), 0);
		close(client_socket);
		free(communication_layer);
	}
	return 0;
}
