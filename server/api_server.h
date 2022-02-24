/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   api_server.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-capu <fde-capu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:50:25 by fde-capu          #+#    #+#             */
/*   Updated: 2022/02/23 18:16:26 by fde-capu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

#endif
