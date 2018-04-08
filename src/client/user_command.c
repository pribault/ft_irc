/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 11:09:20 by pribault          #+#    #+#             */
/*   Updated: 2018/04/08 18:39:58 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	treat_command(t_env *env, char *s)
{
	static uint8_t	state = 0;

	if (!state)
	{
		state++;
		env->username = ft_strdup(s);
		enqueue_str_by_fd(env, env->out, ft_strdup("Enter your real name:\n"));
	}
	else if (state == 1)
	{
		state++;
		env->real_name = ft_strdup(s);
		if (env->address && env->port)
		{
			if (!(server_connect(env->server,
				(t_method){env->protocol, env->domain}, env->address,
				env->port)))
				return (ft_error(2, ERROR_CANNOT_CONNECT, env->address));
			send_nick(env->server, env->client, env->username);
			send_user(env->server, env->client, env->username, env->real_name);
		}
	}
	else
	{
	}
}

void	get_user_command(t_env *env, char *ptr, size_t size)
{
	char	*s;

	if (ptr[size - 1] == '\n')
	{
		s = ptr;
		s[size - 1] = '\0';
		treat_command(env, s);
	}
	else
	{
		if (!(s = malloc(size + 1)))
			ft_error(2, ERROR_ALLOCATION, NULL);
		ft_memcpy(s, ptr, size);
		s[size] = '\0';
		treat_command(env, s);
		free(s);
	}
}
