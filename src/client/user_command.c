/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 11:09:20 by pribault          #+#    #+#             */
/*   Updated: 2018/08/25 15:39:50 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static t_user_cmd	g_cmds[] =
{
	{"/nick", &cmd_nick},
	{"/list", &cmd_list},
	{"/join", &cmd_join},
	{"/leave", &cmd_leave},
	{"/quit", &cmd_quit},
	{"/who", &cmd_who},
	{"/msg", &cmd_msg},
	{"/connect", &cmd_connect},
	{"/topic", &cmd_topic},
	{"/help", &cmd_help},
	{NULL, NULL}
};

static void			treat_command_2(t_env *env, char *s)
{
	t_bool		found;
	uint32_t	i;
	uint32_t	j;

	i = (uint32_t)-1;
	while (s[++i] && s[i] != ' ')
		;
	if (s[i] == ' ')
		s[i++] = '\0';
	j = (uint32_t)-1;
	found = FT_FALSE;
	while (g_cmds[++j].name && found == FT_FALSE)
		if (!ft_strcmp(s, g_cmds[j].name))
		{
			g_cmds[j].function(env, &s[i]);
			found = FT_TRUE;
		}
	if (found == FT_FALSE)
		ft_error(2, ERROR_UNKNOWN_COMMAND, s);
}

void				treat_command(t_env *env, char *s)
{
	static uint8_t	state = 0;

	if (!state)
	{
		state++;
		if (!(env->username = ft_strdup(s)))
			ft_error(2, ERROR_ALLOCATION, NULL);
		enqueue_str_by_fd(env, 1, ft_strdup("Enter your real name:\n"));
	}
	else if (state == 1)
	{
		state++;
		if (!(env->real_name = ft_strdup(s)))
			ft_error(2, ERROR_ALLOCATION, NULL);
		if (env->address && env->port)
			if (!(socket_connect(env->socket,
				(t_method){env->protocol, env->domain}, env->address,
				env->port)))
				return (ft_error(2, ERROR_CANNOT_CONNECT, env->address));
	}
	else
		treat_command_2(env, s);
}

void				get_user_command(t_env *env, char *ptr, size_t size)
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
