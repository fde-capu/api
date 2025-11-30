#ifndef API_SERVER_H
# define API_SERVER_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <unistd.h>
# include <netdb.h>
# include <arpa/inet.h>
# include "../libft/libft.h"

# define MAX_RESPONSE 4096
# define ERROR "Error: "
# define INVALID_ARGUMENTS "Invalid arguments."
# define SERVER_SIGN "(api)"
# define FAILEDADDRINGO "Could not get information about the client."
# define COULD_NOT_ACCEPT "Something wrong when accepting socket."
# define CLIENT_IN ">"
# define RECEIVED "Received from client:"
# define SERVER_UP "Server is up."
# define COULD_NOT_BIND "Binding did not occur as expected."
# define COULD_NOT_LISTEN "Could not listen."
# define SYNTAX_ERROR "Syntas error."
# define DID_NOT_UNDERSTAND "They did not understand."

# define MAX_RESPONSE 4096
# define RECV_FAILED "Failed to receive packet."

#endif
