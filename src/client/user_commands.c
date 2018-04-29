/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 23:50:53 by pribault          #+#    #+#             */
/*   Updated: 2018/04/29 11:59:05 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	cmd_nick(t_env *env, char *s)
{
	if (!env->client)
		return (ft_error(2, ERROR_DISCONNECTED, NULL));
	send_nick(env->socket, env->client, s);
}

void	cmd_list(t_env *env, char *s)
{
	if (!env->client)
		return (ft_error(2, ERROR_DISCONNECTED, NULL));
	(void)s;
	send_list(env->socket, env->client);
}

void	cmd_join(t_env *env, char *s)
{
	if (!env->client)
		return (ft_error(2, ERROR_DISCONNECTED, NULL));
	(void)s;
	send_join(env->socket, env->client, s);
}

void	cmd_quit(t_env *env, char *s)
{
	size_t	len;

	if (!env->client)
		return (ft_error(2, ERROR_DISCONNECTED, NULL));
	len = ft_strlen(s);
	if (len && s[len - 1] == '\n')
		s[len - 1] = '\0';
	send_quit(env->socket, env->client, s);
}

void	cmd_who(t_env *env, char *s)
{
	size_t	len;
	size_t	i;

	if (!env->client)
		return (ft_error(2, ERROR_DISCONNECTED, NULL));
	len = ft_strlen(s);
	if (len && s[len - 1] == '\n')
		s[len - 1] = '\0';
	i = 0;
	while (s[i] && !ft_isof(s[i], WHITESPACES))
		i++;
	if (s[i])
		s[i++] = '\0';
	send_who(env->socket, env->client, s, &s[i]);
}
