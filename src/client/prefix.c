/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 18:36:05 by pribault          #+#    #+#             */
/*   Updated: 2018/04/09 00:21:59 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_bool		is_host_name_valid(char *s)
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

t_bool		is_pseudo_valid(char *s)
{
	uint32_t	i;

	if (!ft_isof(s[0], PARAM_LETTERS))
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

t_bool	is_username_valid(char *s)
{
	if (!ft_isof(*s, PARAM_WHITE))
	{
		while (*(++s))
			if (ft_isof(*s, PARAM_WHITE))
				return (FT_FALSE);
		return (FT_TRUE);
	}
	return (FT_FALSE);
}

static char	*prefix_getter(char *prefix, char *s)
{
	uint32_t	i;

	i = 0;
	while (s[i] && s[i] != ' ' && s[i] != '@' && s[i] != '!')
		i++;
	if (i >= PREFIX_MAX)
		return (NULL);
	ft_memcpy(prefix, s, i);
	prefix[i] = '\0';
	return (s + i);
}

char		*get_prefix(t_prefix *prefix, char *s)
{
	ft_bzero(prefix, sizeof(t_prefix));
	if (!(s = prefix_getter((char*)&prefix->name, s)) ||
		(is_host_name_valid((char*)&prefix->name) == FT_FALSE &&
		is_pseudo_valid((char*)&prefix->name) == FT_FALSE))
		return (NULL);
	if (*s == '!')
	{
		if (!(s = prefix_getter((char*)&prefix->user, s + 1)) ||
			is_username_valid((char*)&prefix->user) == FT_FALSE)
			return (NULL);
	}
	if (*s == '@')
	{
		if (!(s = prefix_getter((char*)&prefix->host, s + 1)) ||
			is_host_name_valid((char*)&prefix->host) == FT_FALSE)
			return (NULL);
	}
	return ((*s == ' ') ? s + 1 : NULL);
}
