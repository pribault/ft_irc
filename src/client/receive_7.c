/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_7.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 16:40:04 by pribault          #+#    #+#             */
/*   Updated: 2018/08/25 16:27:05 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	recv_msg(t_env *env, t_data *data, t_message *msg)
{
	char	*s;
	size_t	i;

	(void)data;
	if (!(s = ft_joinf("[%s%s%s to %s%s%s (%s%s%s)] %s", COLOR_NAME,
		msg->prefix.name, COLOR_CLEAR, COLOR_NAME, msg->params[0], COLOR_CLEAR,
		COLOR_MESSAGE, "Msg", COLOR_CLEAR, COLOR_HALF)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	i = 0;
	while (++i < msg->n_params)
	{
		if (!(s = realloc(s, ft_strlen(s) +
			ft_strlen(msg->params[i]) + 2)))
			return (ft_error(2, ERROR_ALLOCATION, NULL));
		ft_memcpy(s + ft_strlen(s) + 1, msg->params[i],
			ft_strlen(msg->params[i]) + 1);
		s[ft_strlen(s)] = ' ';
	}
	if (!(s = realloc(s, ft_strlen(s) + ft_strlen(msg->end) +
		ft_strlen(COLOR_CLEAR) + 2)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	ft_memcpy(s + ft_strlen(s), msg->end, ft_strlen(msg->end) + 1);
	ft_memcpy(s + ft_strlen(s), COLOR_CLEAR, sizeof(COLOR_CLEAR) + 1);
	ft_memcpy(s + ft_strlen(s), "\n", 2);
	enqueue_str_by_fd(env, 1, s);
}

void	recv_topic(t_env *env, t_data *data, t_message *msg)
{
	(void)data;
	enqueue_str_by_fd(env, 1, ft_joinf("[%s%s%s (%s%s%s)] %s%s%s\n",
		COLOR_NAME, &msg->prefix.name[0], COLOR_CLEAR, COLOR_INFO,
		"Topic", COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
}

void	recv_name_reply(t_env *env, t_data *data, t_message *msg)
{
	(void)data;
	enqueue_str_by_fd(env, 1, ft_joinf("[%s%s%s (%s%s%s)] %s%s%s\n",
		COLOR_NAME, &msg->prefix.name[0], COLOR_CLEAR, COLOR_INFO,
		"Names", COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
}

void	recv_part(t_env *env, t_data *data, t_message *msg)
{
	(void)data;
	enqueue_str_by_fd(env, 1, ft_joinf("[%s%s%s (%s%s%s)] %s%s%s\n",
			COLOR_NAME, &msg->prefix.name[0], COLOR_CLEAR, COLOR_MESSAGE,
			"Leave", COLOR_CLEAR, COLOR_HALF, msg->params[0], COLOR_CLEAR));
}
