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

int say(char *message, int return_code)
{
	printf(SERVER_SIGN " %s\n", message);
	return return_code;
}

int hints(char *port)
{
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
	int s = getaddrinfo(NULL, port, &hints, &result);
	if (s != 0)
		return say(ERROR FAILEDADDRINGO, 0);
	for(i = result; i != NULL; i = i->ai_next)
	{
		char str[INET6_ADDRSTRLEN];
		if (i->ai_addr->sa_family == AF_INET)
		{
			struct sockaddr_in *p = (struct sockaddr_in *)i->ai_addr;
			printf(SERVER_SIGN " Connection from: %s\n", inet_ntop(AF_INET, &p->sin_addr, str, sizeof(str)));
		}
		else if (i->ai_addr->sa_family == AF_INET6)
		{
			struct sockaddr_in6 *p = (struct sockaddr_in6 *)i->ai_addr;
			printf(SERVER_SIGN " Connection from: %s\n", inet_ntop(AF_INET6, &p->sin6_addr, str, sizeof(str)));
		}
	}
	return 0;
}

void parse(str command)
{
	char **com = ft_split(command, ' ');
	for (char **h = com; *h; h++)
	{
		say(*h, 0);
	}
	return ;
}

int main(int argc, char **argv)
{
	str peer_call = calloc(MAX_RESPONSE, 1);
	char *reg = "\\d+";
	if (!validate_args_regex(argc, argv, 2, 2, reg))
		return say(ERROR INVALID_ARGUMENTS, 1);

//	FILE *html_data;
//	html_data = fopen("json-sample.json", "r");
//	char response_data[MAX_RESPONSE];
//	fgets(response_data, 1024, html_data);

	str http_header = ft_str("HTTP/1.1 200 OK\nConnection: close\nContent-Length: 13\n\n");
	str response_data = ft_str("Hello, world!");
	str packet = ft_strcatx(http_header, response_data);

	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(ft_atoi(argv[1]));
	server_address.sin_addr.s_addr = INADDR_ANY;

	if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
		return say(ERROR COULD_NOT_BIND, 1);
	if (listen(server_socket, 1) == -1)
		return say(ERROR COULD_NOT_LISTEN, 1);
	say(SERVER_UP, 0);

	int client_socket;
	while (1)
	{
		memset(peer_call, 0, MAX_RESPONSE);
		struct sockaddr_in *in_layer = calloc(1, sizeof(struct sockaddr_in));

		client_socket = accept(server_socket, (struct sockaddr*)&in_layer, (socklen_t *)&in_layer->sin_addr.s_addr);
		if (client_socket == -1)
		{ say(SERVER_SIGN " " COULD_NOT_ACCEPT, 0); continue ; }
		if (recv(client_socket, peer_call, MAX_RESPONSE, 0) == -1)
		{ say(ERROR RECV_FAILED, 0); continue ; }
		say(RECEIVED, 0);
		printf(CLIENT_IN "%s", peer_call);
		parse(peer_call);

		hints(argv[1]);
		printf(SERVER_SIGN " Family: %d\n", in_layer->sin_family);
		printf(SERVER_SIGN " Port: %d\n", ntohs(in_layer->sin_port));
		printf(SERVER_SIGN " in_addr: %d\n", in_layer->sin_addr.s_addr);
		send(client_socket, packet, strlen(packet), 0);
		close(client_socket);
		free(in_layer);
	}

	return 0;
}
