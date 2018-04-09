/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 14:48:20 by pribault          #+#    #+#             */
/*   Updated: 2018/04/09 17:40:11 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_cmd	g_recv[] =
{
	{RPL_WELCOME, &recv_welcome},
	{RPL_YOURHOST, &recv_yourhost},
	{RPL_CREATED, &recv_created},
	{RPL_MYINFO, &recv_myinfo},
	{RPL_BOUNCE, &recv_bounce},
	{NOTICE, &recv_notice},
	{RPL_LUSERCLIENT, &recv_lusers},
	{RPL_LUSEROP, &recv_lops},
	{RPL_MOTDSTART, &recv_motdstart},
	{RPL_MOTD, &recv_motd},
	{RPL_ENDOFMOTD, &recv_motdend},
	{RPL_LUSERCHANNELS, &recv_lchannels},
	{RPL_LUSERME, &recv_lme},
	{NULL, NULL}
};

void	recv_unknown(t_env *env, t_data *data, t_message *msg)
{
	(void)data;
	enqueue_str_by_fd(env, env->out,
		ft_joinf("[%s%s%s (%s??? %s%s)] %s%s%s\n", COLOR_NAME,
			&msg->prefix.name[0], COLOR_CLEAR, COLOR_ERROR, &msg->command,
			COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
}

t_bool	get_message(t_message *msg, char *s)
{
	uint32_t	i;

	msg->prefix = PREFIX_DEFAULT;
	if (s[0] == ':')
		if (!(s = get_prefix(&msg->prefix, s + 1)))
			return (FT_FALSE);
	if (!(s = get_command((char*)&msg->command, s)))
		return (FT_FALSE);
	i = 0;
	while (i < 15 && (s = get_param((char*)&msg->params[i], s)) &&
		msg->params[i][0])
		i++;
	msg->end = s;
	return ((s) ? FT_TRUE : FT_FALSE);
}

void	search_function(t_env *env, t_data *data, t_message *msg)
{
	t_bool		found;
	uint32_t	i;

	i = (uint32_t)-1;
	found = FT_FALSE;
	while (found == FT_FALSE && g_recv[++i].name)
		if (!ft_strcmp(g_recv[i].name, &msg->command[0]) &&
			g_recv[i].function)
		{
			g_recv[i].function(env, data, msg);
			found = FT_TRUE;
		}
	if (found == FT_FALSE)
		recv_unknown(env, data, msg);
}

void	debug_message(t_env *env, t_data *data, t_message *msg)
{
	uint8_t	i;

	(void)data;
	enqueue_str_by_fd(env, env->out,
		ft_joinf("[%sDEBUG%s] name=%s user=%s host=%s\n",
			COLOR_VERBOSE, COLOR_CLEAR, &msg->prefix.name, &msg->prefix.user,
			&msg->prefix.host));
	enqueue_str_by_fd(env, env->out, ft_joinf("[%sDEBUG%s] command=%s\n",
		COLOR_VERBOSE, COLOR_CLEAR, &msg->command));
	enqueue_str_by_fd(env, env->out, ft_joinf("[%sDEBUG%s] args:\n",
		COLOR_VERBOSE, COLOR_CLEAR));
	i = (uint8_t)-1;
	while (msg->params[++i][0])
		enqueue_str_by_fd(env, env->out, ft_joinf("[%sDEBUG%s] \t%s\n",
			COLOR_VERBOSE, COLOR_CLEAR, &msg->params[i]));
}

void	treat_packet(t_server *server, void *client, void *ptr, size_t size)
{
	t_message	message;
	t_env		*env;
	t_data		*data;
	char		*s;

	env = server_get_data(server);
	data = server_client_get_data(client);
	if (!(s = malloc(size + 1)))
		return (ft_error(env->err, ERROR_ALLOCATION, NULL));
	ft_memcpy(s, ptr, size);
	s[size] = '\0';
	if (get_message(&message, s) == FT_TRUE)
	{
		if (env->opt & OPT_VERBOSE)
			debug_message(env, data, &message);
		search_function(env, data, &message);
	}
	free(s);
}
