/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 18:36:05 by pribault          #+#    #+#             */
/*   Updated: 2018/04/08 18:36:44 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_bool	is_host_name_valid(char *s)
{
	uint32_t	i;

	i = 0;
	while (s[i] && i < 25)
	{
		if (!ft_isof(s[i], PARAM_LETTERS) && !ft_isof(s[i], PARAM_NUMBER) &&
			s[i] != '-' && s[i] != '.')
			return (FT_FALSE);
		i++;
	}
	return ((i < 25) ? FT_TRUE : FT_FALSE);
}

t_bool	is_pseudo_valid(char *s)
{
	uint32_t	i;

	if (s[0] && !ft_isof(s[0], PARAM_LETTERS))
		return (FT_FALSE);
	i = 1;
	while (s[i])
	{
		if (!ft_isof(s[i], PARAM_LETTERS) && !ft_isof(s[i], PARAM_NUMBER) &&
			!ft_isof(s[i], PARAM_SPECIAL))
			return (FT_FALSE);
		i++;
	}
	return (FT_TRUE);
}

char	*get_prefix(t_prefix *prefix, char *s)
{
	int			i;

	i = 0;
	while (s[i] && s[i] != ' ')
		i++;
	if (s[i - 1] == '!')
		prefix->type = PREFIX_USER;
	else if (s[i - 1] == '@')
		prefix->type = PREFIX_HOST;
	else
		prefix->type = PREFIX_SERVER;
	if (!s[i] || i >= PREFIX_MAX)
		return (NULL);
	ft_memcpy(&prefix->name, s, i);
	prefix->name[i] = '\0';
	if ((prefix->type == PREFIX_SERVER &&
		is_host_name_valid((char*)&prefix->name) == FT_FALSE) ||
		((prefix->type == PREFIX_USER || prefix->type == PREFIX_HOST) &&
			is_pseudo_valid((char*)&prefix->name) == FT_FALSE))
		return (NULL);
	return (&s[i + 1]);
}
