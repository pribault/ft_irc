/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 22:14:50 by pribault          #+#    #+#             */
/*   Updated: 2018/04/29 11:17:47 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	send_listend(t_env *env, t_data *data)
{
	char	*s;

	if (!(s = ft_joinf(":%s %s :%s%s", &data->nickname,
		RPL_LISTEND, "end of channel list", CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(env->socket, data->client, s, ft_strlen(s));
}

void	send_pong(t_env *env, t_data *data)
{
	char	*s;

	if (!(s = ft_joinf("%s%s", PONG, CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(env->socket, data->client, s, ft_strlen(s));
}

void	send_motdstart(t_env *env, t_data *data)
{
	char	*s;

	if (!(s = ft_joinf(":%s %s %s :- %s Message of the day - %s",
		&data->nickname, RPL_MOTDSTART, &data->nickname, env->name, CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(env->socket, data->client, s, ft_strlen(s));
}

void	send_motd(t_env *env, t_data *data)
{
	char	*s;
	size_t	i;

	i = (size_t)-1;
	if (!env->motd || !env->motd[0])
	{
		if (!(s = ft_joinf(":%s %s %s :- %s%s", env->name, RPL_MOTD,
			&data->nickname, "no motd", CRLF)))
			ft_error(2, ERROR_ALLOCATION, NULL);
		enqueue_write(env->socket, data->client, s, ft_strlen(s));
	}
	else
		while (env->motd[++i])
		{
			if (!(s = ft_joinf(":%s %s %s :- %s%s", env->name, RPL_MOTD,
				&data->nickname, env->motd[i], CRLF)))
				ft_error(2, ERROR_ALLOCATION, NULL);
			enqueue_write(env->socket, data->client, s, ft_strlen(s));
		}
}

void	send_motdend(t_env *env, t_data *data)
{
	char	*s;

	if (!(s = ft_joinf(":%s %s %s :End of MOTD command%s", &data->nickname,
		RPL_ENDOFMOTD, &data->nickname, CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(env->socket, data->client, s, ft_strlen(s));
}
