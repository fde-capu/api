#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{
	int max_connections = 1;

	char server_message[256] = "You have reached the server!\n\n";

	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY; // would be external.

	int bind_status = bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));

	listen(server_socket, max_connections);

	int client_socket;

	client_socket = accept(server_socket, NULL, NULL); // NULL is info about client.

	send(client_socket, server_message, sizeof(server_message), 0);
	close(server_socket);

	return 0;
}
