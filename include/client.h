/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 18:59:09 by pribault          #+#    #+#             */
/*   Updated: 2018/04/02 10:00:27 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

/*
****************
**	includes  **
****************
*/

# include "libft.h"
# include "libsocket.h"

/*
***************
**	defines  **
***************
*/

# define COLOR_BOLD			"\e[1m"
# define COLOR_HALF			"\e[2m"
# define COLOR_ITALIC		"\e[3m"
# define COLOR_UNDERLINED	"\e[4m"
# define COLOR_CLEAR		"\e[0m"

/*
*************
**	enums  **
*************
*/

typedef enum	e_client_error
{
	ERROR_SETTING_DEFAULT
}				t_client_error;

/*
******************
**	structures  **
******************
*/

typedef struct	s_env
{
	t_server	*server;
	char		*address;
	char		*port;
}				t_env;

/*
******************
**	prototypes  **
******************
*/

void			print_usage(void);
void			get_default(char *s, t_env *env);

#endif
