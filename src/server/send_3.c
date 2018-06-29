/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 13:45:04 by pribault          #+#    #+#             */
/*   Updated: 2018/06/29 18:01:23 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

typedef struct	s_data
{
	void		*client;
	void		*ptr;
	uint64_t	size;
	char		nickname[NICK_MAX_LEN];
	char		*username;
	char		*hostname;
	uint8_t		permissions;
}				t_data;

void	send_first_welcome(t_env *env, t_data *data)
{
	send_welcome(env, data);
	send_motdstart(env, data);
	send_motd(env, data);
	send_motdend(env, data);
}

void	send_quit(t_env *env, t_data *data, t_data *to, char *reason)
{
	char	*s;

	if (!(s = ft_joinf(":%s!%s~%s %s :%s%s", data->nickname, data->username,
		data->hostname, QUIT, reason, CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(env->socket, to->client, s, ft_strlen(s));
}
