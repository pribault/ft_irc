/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 10:46:50 by pribault          #+#    #+#             */
/*   Updated: 2018/04/10 13:41:38 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	send_welcome(t_env *env, t_data *data)
{
	char	*s;

	if (!(s = ft_joinf(":%s %s :Welcome to %s %s!%s@%s%s", env->name,
		RPL_WELCOME, env->name, &data->nickname, data->username,
		data->hostname, CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(env->server, data->client, s, ft_strlen(s));
}

void	send_error(t_env *env, t_data *data, char *error, char *comment)
{
	char	*s;

	if (!(s = ft_joinf(":%s %s :%s%s", env->name,
		error, comment, CRLF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	enqueue_write(env->server, data->client, s, ft_strlen(s));
}
