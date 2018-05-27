/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 17:00:47 by pribault          #+#    #+#             */
/*   Updated: 2018/05/27 11:31:37 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_bool	is_nickname_valid(char *nick)
{
	uint32_t	i;

	if (!ft_isof(nick[0], PARAM_LETTERS) &&
		!ft_isof(nick[0], PARAM_SPECIAL))
		return (FT_FALSE);
	i = 0;
	while (++i < NICK_MAX_LEN && nick[i])
		if (!ft_isof(nick[i], PARAM_LETTERS) &&
			!ft_isof(nick[i], PARAM_SPECIAL) &&
			!ft_isof(nick[i], PARAM_NUMBER) &&
			nick[i] != '-')
			return (FT_FALSE);
	if (nick[i])
		return (FT_FALSE);
	return (FT_TRUE);
}
