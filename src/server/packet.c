/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 11:18:20 by pribault          #+#    #+#             */
/*   Updated: 2018/07/03 00:15:27 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_cmd	g_recv[] =
{
	{NICK, &recv_nick},
	{USER, &recv_user},
	{LIST, &recv_list},
	{JOIN, &recv_join},
	{QUIT, &recv_quit},
	{WHO, &recv_who},
	{PING, &recv_ping},
	{PRIVMSG, &recv_privmsg},
	{TOPIC, &recv_topic},
	{NULL, NULL}
};

t_bool	get_message(t_message *msg, char *s)
{
	msg->prefix = PREFIX_DEFAULT;
	if (s[0] == ':')
		if (!(s = get_prefix(&msg->prefix, s + 1)))
			return (FT_FALSE);
	if (!(s = get_command((char*)&msg->command, s)))
		return (FT_FALSE);
	msg->n_params = 0;
	while (msg->n_params < PARAMS_MAX - 1 &&
		(s = get_param((char*)&msg->params[msg->n_params], s)) &&
		msg->params[msg->n_params][0])
		msg->n_params++;
	msg->params[msg->n_params][0] = '\0';
	if (!s || ft_strlen(s) >= COMMENT_LEN - 2)
		return (FT_FALSE);
	ft_memcpy(&msg->end, s, ft_strlen(s) + 1);
	return (FT_TRUE);
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
	uint32_t	i;

	(void)data;
	enqueue_str_by_fd(env, 1,
		ft_joinf("[%sDEBUG%s] name=%s user=%s host=%s\n",
			COLOR_VERBOSE, COLOR_CLEAR, &msg->prefix.name, &msg->prefix.user,
			&msg->prefix.host));
	enqueue_str_by_fd(env, 1, ft_joinf("[%sDEBUG%s] command=%s\n",
		COLOR_VERBOSE, COLOR_CLEAR, &msg->command));
	enqueue_str_by_fd(env, 1, ft_joinf("[%sDEBUG%s] args(%u):\n",
		COLOR_VERBOSE, COLOR_CLEAR, msg->n_params));
	i = (uint32_t)-1;
	while (++i < msg->n_params)
		enqueue_str_by_fd(env, 1, ft_joinf("[%sDEBUG%s] \t%s\n",
			COLOR_VERBOSE, COLOR_CLEAR, &msg->params[i]));
}

void	treat_packet(t_socket *socket, void *client, void *ptr, size_t size)
{
	t_message	msg;
	t_env		*env;
	t_data		*data;
	char		*s;

	ft_bzero(&msg, sizeof(t_message));
	env = socket_get_data(socket);
	data = client_get_data(client);
	if (!(s = malloc(size + 1)))
		return (ft_error(2, ERROR_ALLOCATION, NULL));
	ft_memcpy(s, ptr, size);
	s[size] = '\0';
	if (env->opt & OPT_VERBOSE)
		enqueue_str_by_fd(env, 1, ft_joinf("[%sDEBUG%s] \"%s\"\n",
			COLOR_VERBOSE, COLOR_CLEAR, s));
	if (get_message(&msg, s) == FT_TRUE)
	{
		if (env->opt & OPT_VERBOSE)
			debug_message(env, data, &msg);
		search_function(env, data, &msg);
	}
	else if (env->opt & OPT_VERBOSE)
		enqueue_str_by_fd(env, 1, ft_joinf("[%sERROR%s] %s\n",
			COLOR_ERROR, COLOR_CLEAR, s));
	free(s);
}
