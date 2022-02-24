/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   api_client.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-capu <fde-capu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:42:33 by fde-capu          #+#    #+#             */
/*   Updated: 2022/02/24 19:15:27 by fde-capu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef API_CLIENT_H
# define API_CLIENT_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <unistd.h>
# include <arpa/inet.h> // to convert network address
# include "../libft/libft.h"

# define ERROR "Error: "
# define INVALID_ARGUMENTS "Invalid arguments."
# define CONNECTION_FAILED "Connection failed."
# define SEND_FAILED "Failed sending message."
# define RECV_FAILED "Failed to receive packet."
# define CLOSE_SOCKET_FAILED "Could not close the socket!"
# define INVALID_ADDRESS "Invalid address."
# define SOCKET_CREATION_FAIL "Socket creation failed."
# define SHELL_MODE "Entering shell mode:"
# define SERVER_IN ">"
# define CLIENT_OUT "<"
# define CLIENT_SIGN "(cli)"

# define MAX_RESPONSE 4096

#endif
