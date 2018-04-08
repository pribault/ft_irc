/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 14:48:20 by pribault          #+#    #+#             */
/*   Updated: 2018/04/08 22:19:36 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

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

void	treat_packet(t_server *server, void *client, void *ptr, size_t size)
{
	t_message	message;
	t_env		*env;
	t_data		*data;
	char		*s;
	// uint32_t	i;

	env = server_get_data(server);
	data = server_client_get_data(client);
	if (!(s = malloc(size + 1)))
		return (ft_error(env->err, ERROR_ALLOCATION, NULL));
	ft_memcpy(s, ptr, size);
	s[size] = '\0';
	if (get_message(&message, s) == FT_TRUE)
	{
		// ft_printf("name=%s user=%s host=%s\n",
		// 	&message.prefix.name, &message.prefix.user, &message.prefix.host);
		// ft_printf("command=%s\n", &message.command);
		// i = (uint32_t)-1;
		// while (message.params[++i][0])
		// 	ft_printf("\t%u: %s\n", i, &message.params[i]);
		// ft_printf("end=%s\n", message.end);
		ft_printf("[OK] %s\n", s);
	}
	else
		ft_printf("[ERROR] %s\n", s);
	free(s);
}
