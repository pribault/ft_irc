/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 11:32:57 by pribault          #+#    #+#             */
/*   Updated: 2018/06/30 16:39:14 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	recv_quit(t_env *env, t_data *data, t_message *msg)
{
	(void)data;
	enqueue_str_by_fd(env, 1, ft_joinf("[%s%s%s (%s%s%s)] %s%s%s\n",
		COLOR_NAME, &msg->prefix.name[0], COLOR_CLEAR, COLOR_MESSAGE,
		"Quit", COLOR_CLEAR, COLOR_HALF, msg->end, COLOR_CLEAR));
}

void	recv_who_reply(t_env *env, t_data *data, t_message *msg)
{
	(void)data;
	if (msg->n_params != 6)
		return ;
	enqueue_str_by_fd(env, 1, ft_joinf(
		"[%s%s%s (%s%s%s)] %s%s%s%s(%s%s%s%s%s)%s\n",
		COLOR_NAME, &msg->prefix.name[0], COLOR_CLEAR, COLOR_INFO,
		"WhoReply", COLOR_CLEAR, COLOR_MESSAGE, msg->params[1], COLOR_CLEAR,
		COLOR_HALF, COLOR_CLEAR, COLOR_MESSAGE, msg->params[4], COLOR_CLEAR,
		COLOR_HALF, COLOR_CLEAR));
}

void	recv_end_of_who(t_env *env, t_data *data, t_message *msg)
{
	(void)data;
	if (msg->n_params != 1)
		return ;
	enqueue_str_by_fd(env, 1, ft_joinf("[%s%s%s (%s%s%s)] %s%s (%s)%s\n",
		COLOR_NAME, &msg->prefix.name[0], COLOR_CLEAR, COLOR_INFO,
		"EndOfWho", COLOR_CLEAR, COLOR_HALF, msg->end, msg->params[0],
		COLOR_CLEAR));
}

void	recv_err_no_such_server(t_env *env, t_data *data, t_message *msg)
{
	(void)data;
	if (msg->n_params != 1)
		return ;
	enqueue_str_by_fd(env, 1, ft_joinf("[%s%s%s (%s%s%s)] %s%s (%s)%s\n",
		COLOR_NAME, &msg->prefix.name[0], COLOR_CLEAR, COLOR_ERROR,
		"NoSuchServer", COLOR_CLEAR, COLOR_HALF, msg->end, msg->params[0],
		COLOR_CLEAR));
}

void	recv_no_text_to_send(t_env *env, t_data *data, t_message *msg)
{
	(void)data;
	if (msg->n_params != 1)
		return ;
	enqueue_str_by_fd(env, 1, ft_joinf("[%s%s%s (%s%s%s)] %s\n",
		COLOR_NAME, &msg->prefix.name[0], COLOR_CLEAR, COLOR_ERROR,
		"NoTextToSend", COLOR_CLEAR, COLOR_CLEAR));
}
