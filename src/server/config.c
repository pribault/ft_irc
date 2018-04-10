/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 11:08:38 by pribault          #+#    #+#             */
/*   Updated: 2018/04/10 16:04:54 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static t_config_cb	g_callbacks[] =
{
	{SERVNAME, DEFAULT_SERVNAME, &servname_callback},
	{PORT, DEFAULT_PORT, &port_callback},
	{NULL, NULL, NULL}
};

void	servname_callback(t_env *env, char **array, uint32_t n)
{
	char	*s;

	if (n != 2)
		return (ft_error(2, ERROR_SERVNAME_PARAMS, (void*)(uint64_t)n));
	if (!(s = ft_implode(&array[1], ' ')))
		ft_error(2, ERROR_ALLOCATION, NULL);
	env->name = s;
}

void	port_callback(t_env *env, char **array, uint32_t n)
{
	if (n != 2)
		return (ft_error(2, ERROR_PORT_PARAMS, (void*)(uint64_t)n));
	env->port = ft_strdup(array[1]);
}

int		create_config(t_env *env)
{
	char		**array;
	uint32_t	i;
	char		*s;
	int			fd;

	if ((fd = open(CONFIG_FILE, O_WRONLY | O_TRUNC | O_CREAT, 0644)) == -1)
		return (0);
	i = (uint32_t)-1;
	while (g_callbacks[++i].name)
	{
		if (!(s = ft_joinf("%s %s", g_callbacks[i].name,
			g_callbacks[i].value)) ||
			!(array = ft_multisplit(s, CONFIG_SEPARATORS)))
			ft_error(2, ERROR_ALLOCATION, NULL);
		g_callbacks[i].function(env, array, ft_arraylen(array));
		ft_free_array((void**)array, ft_arraylen(array) + 1);
		ft_putendl_fd(s, fd);
		free(s);
	}
	close(fd);
	return (1);
}

int		load_config(t_env *env)
{
	t_bool		found;
	uint32_t	i;
	char		**array;
	char		*s;
	int			fd;

	if ((fd = open(CONFIG_FILE, O_RDONLY)) == -1)
		return (create_config(env));
	while (ft_get_next_line(fd, &s) == 1)
	{
		if (!(array = ft_multisplit(s, CONFIG_SEPARATORS)))
			ft_error(2, ERROR_ALLOCATION, NULL);
		i = (uint32_t)-1;
		found = FT_FALSE;
		while (found == FT_FALSE && g_callbacks[++i].name)
			if (!ft_strcmp(g_callbacks[i].name, array[0]))
			{
				g_callbacks[i].function(env, array, ft_arraylen(array));
				found = FT_TRUE;
			}
		ft_free_array((void**)array, ft_arraylen(array) + 1);
		free(s);
	}
	close(fd);
	return (1);
}
