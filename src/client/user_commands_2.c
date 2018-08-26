/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_commands_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 11:26:40 by pribault          #+#    #+#             */
/*   Updated: 2018/08/25 15:46:32 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	cmd_msg(t_env *env, char *s)
{
	char	target[PARAMS_LEN];
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i] && ft_isof(s[i], WHITESPACES))
		i++;
	j = i;
	while (s[j] && !ft_isof(s[j], WHITESPACES))
	{
		target[j - i] = s[j];
		j++;
	}
	target[j - i] = '\0';
	while (s[j] && ft_isof(s[j], WHITESPACES))
		j++;
	send_msg(env->socket, env->client, target, &s[j]);
}

void	cmd_topic(t_env *env, char *s)
{
	char	topic[PARAMS_LEN];
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i] && ft_isof(s[i], WHITESPACES))
		i++;
	j = i;
	while (s[j] && !ft_isof(s[j], WHITESPACES))
	{
		topic[j - i] = s[j];
		j++;
	}
	topic[j - i] = '\0';
	while (s[j] && ft_isof(s[j], WHITESPACES))
		j++;
	send_topic(env->socket, env->client, topic, &s[j]);
}

void	cmd_connect(t_env *env, char *s)
{
	char	**array;

	if (env->client)
		return (ft_error(2, ERROR_ALREADY_CONNECTED, env->address));
	if (!(array = ft_multisplit(s, WHITESPACES)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	if (ft_arraylen(array) != 2)
		ft_error(2, ERROR_INVALID_PARAMETERS, "/connect <address> <port>");
	else if (!(socket_connect(env->socket,
		(t_method){env->protocol, env->domain}, array[0],
		array[1])))
		return (ft_error(2, ERROR_CANNOT_CONNECT, array[0]));
	ft_free_array((void**)array, ft_arraylen(array) + 1);
}

void	cmd_leave(t_env *env, char *s)
{
	if (!env->client)
		return (ft_error(2, ERROR_DISCONNECTED, NULL));
	(void)s;
	send_leave(env->socket, env->client, s);
}

void	cmd_help(t_env *env, char *s)
{
	size_t	i;

	i = 0;
	while (ft_isof(s[i], WHITESPACES))
		i++;
	if (s[i])
		return (ft_error(2, ERROR_INVALID_PARAMETERS, "/help"));
	enqueue_str_by_fd(env, 1, ft_strdup("list of commands:\n"));
	enqueue_str_by_fd(env, 1, ft_strdup("  /help\n"));
	enqueue_str_by_fd(env, 1, ft_strdup("  /connect <address> <port>\n"));
	enqueue_str_by_fd(env, 1, ft_strdup("  /quit <reason>\n"));
	enqueue_str_by_fd(env, 1, ft_strdup("  /list\n"));
	enqueue_str_by_fd(env, 1, ft_strdup("  /join <channels>\n"));
	enqueue_str_by_fd(env, 1, ft_strdup("  /leave <channels>\n"));
	enqueue_str_by_fd(env, 1, ft_strdup("  /who <channels>\n"));
	enqueue_str_by_fd(env, 1, ft_strdup("  /nick <nickname>\n"));
	enqueue_str_by_fd(env, 1, ft_strdup("  /topic <channel> <topic>\n"));
	enqueue_str_by_fd(env, 1, ft_strdup(
		"  /msg <channel | nickname> <message>\n"));
}
